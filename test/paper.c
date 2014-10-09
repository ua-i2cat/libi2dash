#include <i2libdash.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    i2ctx *context;
    byte *sps_data = NULL, *pps_data = NULL, *metadata = NULL, *metadata2 = NULL, *metadata3 = NULL;
    byte *destination_data = NULL, *source_data = NULL;
    uint32_t metadata_size = 0, metadata2_size = 0, metadata3_size = 0, init_video = 0, size_source_data = 0, initial_timestamp = 0;
    uint32_t sps_size = 0, pps_size = 0, duration_sample = 0, timestamp = 0, previous_timestamp = 0, i = 0, seg_size = 0;
    uint32_t nal_size = 0, hton_nal_size = 0, sample_count = 0, hton_sum_nal = 0, segment_count = 0;
    uint8_t i2error = 0, is_intra = 0, nal_type = 0, nri_type = 0, fbit = 0, start_bit = 0, end_bit = 0, nal_header = 0;
    uint8_t nal_unit_type = 0;
    struct sockaddr_in  sock_addr_input;
    socklen_t sockaddrlen = sizeof(struct sockaddr);
    int sock_origen;
    uint32_t c = 0, hton_timestamp = 0, decode_time = 0, nal_length = 0, sum_nal = 0;
    byte buffer_in[3000];
    struct timeval to;
    fd_set ready;
    FILE *output_video_i, *output_paper;
    float duration_sample_f = 0.00, decode_time_f = 0.00;
    char* representation = new char(3);
	memcpy(representation, "480", 3);
	char *paper_name;
    if (argc >= 2)
        representation = argv[1];
	if (argc >= 3)
		paper_name = argv[2];
		
    source_data = (byte *) malloc(MAX_DAT);
    sock_origen = socket(AF_INET, SOCK_DGRAM, 0 );
    if(sock_origen == -1) {
        perror("Error socket\n");
        exit(-1);
    }

    bzero((char *)&sock_addr_input, sizeof(sock_addr_input) );
    sock_addr_input.sin_family = AF_INET;
    sock_addr_input.sin_port = htons(10000);

    if (bind(sock_origen, (struct sockaddr *)&sock_addr_input, sizeof(sock_addr_input) ) == -1) {
        perror("Error bind\n");
        close(sock_origen);
        exit(-1);
    }

    i2error= context_initializer(&context, VIDEO_TYPE);
    if (i2error == I2ERROR_MEDIA_TYPE) {
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
        exit(1);    
    }
    else
        printf("CONTEXT OK!\n");
    set_segment_duration(2, &context);
    sps_data = (byte *) malloc (100);
    pps_data = (byte *) malloc (100);
    
    // METADATA
    metadata = (byte *) malloc (100);
    metadata[0] = 0x01;
    metadata[1] = 0x42;
    metadata[2] = 0xC0;
    metadata[3] = 0x1E;
    metadata_size = 4;

    // METADATA2
    metadata2 = (byte *) malloc (100);
    metadata2[0] = 0xFF;
    metadata2[1] = 0xE1;
    metadata2_size = 2;

    // METADATA3
    metadata3 = (byte *) malloc (100);
    metadata3[0] = 0x01;
    metadata3_size = 1;

    // DESTINATION DATA
    destination_data = (byte *) malloc (MAX_DAT);

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
            c = recvfrom (sock_origen, buffer_in, sizeof(buffer_in), 0, (struct sockaddr *)&sock_addr_input, &sockaddrlen);
            memcpy(&hton_timestamp, buffer_in+4, sizeof(hton_timestamp));

            nal_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NAL_TYPE;
            timestamp = htonl(hton_timestamp);
            if (i == 0) {
                previous_timestamp = timestamp;
                initial_timestamp = timestamp;
                decode_time = 0;
                size_source_data = 0;
            }
            if (nal_type == SPS_TYPE) {
                if (i < 2) {
                    memcpy(sps_data, buffer_in+RTP_LENGTH_HEADER, (c-RTP_LENGTH_HEADER));
                    sps_size = c-RTP_LENGTH_HEADER;
                }
            }
            if (nal_type == PPS_TYPE) {
                if (i < 3) {
                    memcpy(pps_data, buffer_in + RTP_LENGTH_HEADER, (c-RTP_LENGTH_HEADER));
                    pps_size = c-RTP_LENGTH_HEADER;
                    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
                    if (init_video > I2ERROR_MAX) {
                        char path[250];
                        bzero(path, 250);
                        printf("INIT i2libtest_%s_video_init.m4v done\n", representation);
                        sprintf(path, "%s%s%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_video_init.m4v");
                        output_video_i = fopen(path, "w");
                        unsigned int k = 0;
                        for(k = 0; k < init_video; k++) {
                            fputc(destination_data[k], output_video_i);
                        }
                        fclose(output_video_i);
                    }
                }
            }
            if ((nal_type != PPS_TYPE) && (nal_type != SPS_TYPE)) {
                if (previous_timestamp != timestamp) {
                    duration_sample = ((timestamp - previous_timestamp) / H264_FREQUENCY_MS);
                    if ((initial_timestamp == previous_timestamp) || (is_intra)){
                        is_intra = 1;
                    }
                    else
                        is_intra = 0;
                    sample_count++;
                    if ((sample_count % 10) == 0) {
                        printf(".");
                        fflush(stdout);
                    }
                    decode_time = ((previous_timestamp - initial_timestamp) / H264_FREQUENCY_MS);
                    duration_sample_f+= (((float)(timestamp - previous_timestamp))/((float) (H264_FREQUENCY_MS)));
                    duration_sample_f-= (float) duration_sample;
                    if (duration_sample_f >= 1) {
                        duration_sample++;
                        duration_sample_f--;
                    }
                    decode_time_f= (((float)(previous_timestamp - initial_timestamp))/((float) (H264_FREQUENCY_MS)));
                    decode_time_f-= (float) decode_time;
                    if ((decode_time_f >= 0.5) ) {
                        decode_time++;
                    }
			printf ("SAMPLE DURATION %u\n", duration_sample);
			printf ("DECODE TIME %u\n", decode_time);
					struct timespec requestStart, requestEnd;
					/*time_t timer;
		   			struct tm * ptm;
		   			time(&timer);
		   			ptm = gmtime (&timer);
                    printf ( "Current local time and date: %s", asctime (ptm) ); CLOCK_REALTIME*/
					clock_gettime(CLOCK_MONOTONIC, &requestStart);					
					//printf("%u %u\n", requestStart.tv_sec, requestStart.tv_nsec); 
                    seg_size = add_sample(source_data, size_source_data, duration_sample, decode_time, VIDEO_TYPE, destination_data, is_intra, &context);
					clock_gettime(CLOCK_MONOTONIC, &requestEnd);
					//printf("%ld %ld\n", requestEnd.tv_nsec, requestStart.tv_nsec);
                    is_intra = 0;
                    if (seg_size > I2ERROR_MAX) {
                        char path[250];
                        bzero(path, 250);
						output_paper = fopen(paper_name, "a");
						fprintf(output_paper, "%d;%ld;%ld;%ld;%ld\n", segment_count, requestStart.tv_sec, requestStart.tv_nsec, requestEnd.tv_sec, requestEnd.tv_nsec);
						fclose(output_paper);
                        printf("\nSEGMENT i2libtest_%s_video_%d_1.m4v done\n", representation, segment_count);
                        sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_video_", segment_count, "_1.m4v");
                        segment_count++;
                        sample_count = 0;
                        duration_sample_f = 0.00;
                        output_video_i = fopen(path, "w");

                        unsigned int j = 0;
                        for(j = 0; j < seg_size; j++) {
                            fputc(destination_data[j], output_video_i);
                        }
                        fclose(output_video_i);
                    }
                    if (nal_type == FUA_TYPE) {
                        nal_unit_type = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & NAL_UNIT_TYPE;
                        nri_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NRI_TYPE;
                        fbit = (*(buffer_in + RTP_LENGTH_HEADER)) & FORBIDDEN_BIT;
                        start_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & START_BIT;
                        end_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & END_BIT;
                        
                        if (start_bit) {
                            nal_length = 0;
                            nal_header = fbit | nri_type | nal_unit_type;
                            size_source_data = LENGTH_SIZE;
                            memcpy(source_data + LENGTH_SIZE, &nal_header, 1);
                            size_source_data += 1;
                            sum_nal = 1;
                        }
                        nal_size = c - RTP_LENGTH_HEADER - H264_LENGTH_HEADER;
                        memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER, nal_size);
                        size_source_data += nal_size;
                        sum_nal += nal_size;
                    } else {//Single NAL unit packet per H.264 
                        nal_size = c - RTP_LENGTH_HEADER;
                        hton_nal_size = htonl(nal_size);
                        memcpy(source_data, &hton_nal_size, LENGTH_SIZE);
                        size_source_data = LENGTH_SIZE;
                        memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER, nal_size);
                        size_source_data += nal_size;
                    }
                    previous_timestamp = timestamp;
                } else { //Same timestamp
                    if (nal_type == FUA_TYPE) { //Fragmentation unit
                        nal_unit_type = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & NAL_UNIT_TYPE;
                        nri_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NRI_TYPE;
                        fbit = (*(buffer_in + RTP_LENGTH_HEADER)) & FORBIDDEN_BIT;
                        start_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & START_BIT;
                        end_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & END_BIT;
                        
                        
                        if (start_bit) {
                            nal_length = size_source_data;
                            nal_header = fbit | nri_type | nal_type;
                            size_source_data += LENGTH_SIZE;
                            memcpy(source_data + size_source_data, &nal_header, 1);
                            size_source_data += 1;
                            sum_nal = 1;
                        }
                        if ((nal_unit_type == INTRA_TYPE) || (nal_unit_type == 6)) {
                            
                            is_intra = 1;
                            }
                        nal_size = c - RTP_LENGTH_HEADER - H264_LENGTH_HEADER;
                        memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER, nal_size);
                        size_source_data += nal_size;
                        sum_nal += nal_size;
                        if (end_bit) {
                            hton_sum_nal = htonl(sum_nal);
                            memcpy(source_data + nal_length, &hton_sum_nal, LENGTH_SIZE);
                        }
                        
                    } else {//Single NAL unit packet per H.264
                        nal_size = c - RTP_LENGTH_HEADER;
                        hton_nal_size = htonl(nal_size);
                        memcpy(source_data + size_source_data, &hton_nal_size, LENGTH_SIZE);
                        size_source_data += LENGTH_SIZE;
                        memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER, nal_size);
                        size_source_data += nal_size;
                    }
                }
            }
        } else {
            printf("5 sec %u\n", context->ctxvideo->segment_data_size);
            seg_size = finish_segment(VIDEO_TYPE, destination_data, &context);
            if (seg_size > I2ERROR_MAX) {
                char path[250];
                bzero(path, 250);
                printf("SEGMENT i2libtest_%s_video_%d_1.m4v done\n", representation, segment_count);
                sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_video_", segment_count, "_1.m4v");
                output_video_i = fopen(path, "w");
                unsigned int j = 0;
                for(j = 0; j < seg_size; j++) {
                    fputc(destination_data[j], output_video_i);
                }
                fclose(output_video_i);
            }
            break;
        }
        i++;
    }
    printf("FINISH!\n");
    return 0;
}

