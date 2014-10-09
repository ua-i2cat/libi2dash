#include <i2libdash.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    i2ctx *context;
    byte *metadata = NULL;
    byte *destination_data = NULL;
    uint32_t metadata_size = 0, message_length = 0, sample_count = 0;
    uint32_t duration_sample = 0, timestamp = 0, previous_timestamp = 0, i = 0, seg_size = 0;
    uint32_t segment_count = 0, init_audio = 0;
    uint16_t segment_size = 0, sample_size_shifted = 0;
    uint16_t hton_aac_length = 0, hton_sample_size = 0;
    uint8_t i2error = 0;
    struct sockaddr_in  sock_addr_input;
    socklen_t sockaddrlen = sizeof(struct sockaddr);
    int sock_origen;
    uint32_t hton_timestamp = 0, decode_time = 0, aac_length = 0, sample_size = 0;
    uint32_t sample_pos = 0, au_num = 0;
    byte buffer_in[3000], previous_buffer[3000];
    struct timeval to;
    fd_set ready;
    FILE *output_audio_i;
    float duration_sample_f = 0.00;
    char* representation = new char(3);
	memcpy(representation, "480", 3);

    if (argc == 2)
        representation = argv[argc - 1];

    sock_origen = socket(AF_INET, SOCK_DGRAM, 0 );
    if(sock_origen == -1) {
        perror("Error socket\n");
        exit(-1);
    }

    bzero((char *)&sock_addr_input, sizeof(sock_addr_input) );
    sock_addr_input.sin_family = AF_INET;
    sock_addr_input.sin_port = htons(10002);

    if (bind(sock_origen, (struct sockaddr *)&sock_addr_input, sizeof(sock_addr_input) ) == -1) {
        perror("Error bind\n");
        close(sock_origen);
        exit(-1);
    }
    i2error= context_initializer(&context, AUDIO_TYPE);
    if (i2error == I2ERROR_MEDIA_TYPE) {
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
        exit(1);    
    }
    else
        printf("CONTEXT OK!\n");

    // METADATA HE AAC v2 Stereo 48kHz
    metadata = (byte *) malloc (100);
    metadata[0] = 0xEB;
    metadata[1] = 0x09;
    metadata[2] = 0x88;
    metadata[3] = 0x00;
    metadata_size = 4;

    // DESTINATION DATA
    destination_data = (byte *) malloc (MAX_DAT);
    decode_time = 0;

    while (1) {
        FD_ZERO(&ready); 
        FD_SET(sock_origen, &ready);
        to.tv_sec = 5;
        bzero(buffer_in, sizeof(buffer_in));
        if (select(sock_origen + 1, &ready, 0, 0, &to) < 0) {
            perror("select");
            exit(-1);
        }
        if (FD_ISSET(sock_origen, &ready)) {
            message_length = recvfrom (sock_origen, buffer_in, sizeof(buffer_in), 0, (struct sockaddr *)&sock_addr_input, &sockaddrlen);

            memcpy(&hton_timestamp, buffer_in+4, sizeof(hton_timestamp));
            timestamp = htonl(hton_timestamp);

            if(i == 0)  {
                decode_time = 0;
                previous_timestamp = timestamp;
                init_audio = init_audio_handler(metadata, metadata_size, destination_data, &context);
                if (init_audio > I2ERROR_MAX) {
                    char path[250];
                    bzero(path, 250);
                    sprintf(path, "%s%s%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_audio_init.m4a");
                    output_audio_i = fopen(path, "w");
                    unsigned int k = 0;
                    for(k = 0; k < init_audio; k++) {
                        fputc(destination_data[k], output_audio_i);
                    }
                    fclose(output_audio_i);
                    printf("INIT i2libtest_%s_audio_init.m4a done\n", representation);
                }
            }           
            

            if (previous_timestamp == timestamp) {
                memcpy(previous_buffer, buffer_in, message_length);
            }
            else {

                // Obtain AAC stuff
                memcpy(&hton_aac_length, previous_buffer+RTP_LENGTH_HEADER, sizeof(hton_aac_length));
                aac_length = ntohs(hton_aac_length);

                au_num = aac_length / (AU_LENGTH_HEADER * BYTE_SIZE);

                // Write samples
                sample_pos = RTP_LENGTH_HEADER + (AU_LENGTH_HEADER*(au_num+1));

                unsigned int j = 0;
                for(j = 0; j < au_num; j++)  {
                    memcpy(&hton_sample_size, previous_buffer+RTP_LENGTH_HEADER+(AU_LENGTH_HEADER + (AU_LENGTH_HEADER*j)), sizeof(hton_sample_size));
                    sample_size = ntohs(hton_sample_size);
                    sample_size_shifted = (sample_size>>3);
                    
                    duration_sample = ((timestamp - previous_timestamp) / (AAC_48K_FREQUENCY_MS * au_num));
					printf("duration %u %d\n", duration_sample, i);
                    duration_sample_f+= (((float)(timestamp - previous_timestamp))/((float) (AAC_48K_FREQUENCY_MS * au_num)));
                    duration_sample_f-= (float) duration_sample;

                    if (duration_sample_f >= 1) {
                        duration_sample++;
                        duration_sample_f--;
                    }
                    segment_size = add_sample(previous_buffer + sample_pos, sample_size_shifted, duration_sample, decode_time, AUDIO_TYPE, destination_data, 1, &context);
                    decode_time += duration_sample;
                    sample_pos += sample_size_shifted;
                    sample_count++;
                    if ((sample_count % 10) == 0) {
                        printf(".");
                        fflush(stdout);
                    }

                    if(segment_size > I2ERROR_MAX)  {
                        char path[250];
                        bzero(path, 250);
                        printf("\nSEGMENT i2libtest_%s_audio_%d_1.m4a done\n", representation, segment_count);
                        sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_audio_", segment_count, "_1.m4a");
                        segment_count++;
                        duration_sample_f = 0.00;
                        output_audio_i = fopen(path, "w");
                        unsigned int j = 0;
                        for(j = 0; j < segment_size; j++) {
                            fputc(destination_data[j], output_audio_i);
                        }
                        fclose(output_audio_i);
                        sample_count = 0;
                    }
                }
                previous_timestamp = timestamp;
                memcpy(previous_buffer, buffer_in, message_length);
            }
        } else {    // wait 5 seconds until finish segment
            printf("5 sec %u\n", context->ctxaudio->segment_data_size);
            seg_size = finish_segment(AUDIO_TYPE, destination_data, &context);
            if (seg_size > I2ERROR_MAX) {
                char path[250];
                bzero(path, 250);
                printf("SEGMENT i2libtest_%s_audio_%d_1.m4a done\n", representation, segment_count);
                sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_audio_", segment_count, "_1.m4a");
                output_audio_i = fopen(path, "w");
                unsigned int j = 0;
                for(j = 0; j < seg_size; j++) {
                    fputc(destination_data[j], output_audio_i);
                }
                fclose(output_audio_i);
            }
            break;
        }
        i++;
    }
    printf("FINISH!\n");
    return 0;
}

