#include <i2libdash.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	i2ctx *context;
	byte *metadata = NULL;
	byte *destination_data = NULL, *source_data = NULL;
	uint32_t metadata_size = 0, size_source_data = 0, initial_timestamp = 0;
	uint32_t duration_sample = 0, timestamp = 0, previous_timestamp = 0, i = 0, seg_size = 0;
	uint32_t sample_count = 0, segment_count = 0, init_audio = 0;
	uint8_t i2error = 0, is_intra = 1;
	struct sockaddr_in  sock_addr_input;
    socklen_t sockaddrlen = sizeof(struct sockaddr);
    int sock_origen;
    uint32_t c = 0, hton_timestamp = 0, decode_time = 0, aac_length = 0;
	byte buffer_in[3000];
	struct timeval to;
	fd_set ready;
	FILE *output_audio_i;
	float duration_sample_f = 0.00, decode_time_f = 0.00;
	char* representation = "480";
	if (argc == 2)
		representation = argv[argc - 1];

	source_data = (byte *) malloc(MAX_DAT);
    sock_origen = socket(AF_INET, SOCK_DGRAM, 0 );
    if(sock_origen == -1) {
		perror("Error socket\n");
		exit(-1);
	} //endif

    bzero((char *)&sock_addr_input, sizeof(sock_addr_input) );
    sock_addr_input.sin_family = AF_INET;
    sock_addr_input.sin_port = htons(10002);

if (bind(sock_origen, (struct sockaddr *)&sock_addr_input, sizeof(sock_addr_input) ) == -1) {
		perror("Error bind\n");
		close(sock_origen);
		exit(-1);
	} //endif
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


    while (1) {
		//int j=0;
		FD_ZERO(&ready); 
		FD_SET(sock_origen, &ready);
		to.tv_sec = 5;
		bzero(buffer_in, sizeof(buffer_in));
		if (select(sock_origen + 1, &ready, 0, 0, &to) < 0) {
			perror("select");
			exit(-1);
		}
		if (FD_ISSET(sock_origen, &ready)) {
			//uint16_t hton_seq_num = 0, seq_num;
			//printf("Entro %u\n", i);
			c = recvfrom (sock_origen, buffer_in, sizeof(buffer_in), 0, (struct sockaddr *)&sock_addr_input, &sockaddrlen);
			memcpy(&hton_timestamp, buffer_in+4, sizeof(hton_timestamp));
			//memcpy(&hton_seq_num, buffer_in + 2, sizeof(hton_seq_num));
			//seq_num = ntohs(hton_seq_num);
			//printf("Packet number %u seq_num %u\n", (i+1), seq_num);
			//printf ("Memcpy timestamp\n");
			timestamp = htonl(hton_timestamp);
			if (i == 0) {
				previous_timestamp = timestamp;
				initial_timestamp = timestamp;
				decode_time = 0;
				size_source_data = 0;
				init_audio = init_audio_handler(metadata, metadata_size, destination_data, &context);
					if (init_audio > I2ERROR_MAX) {
						char path[250];
						bzero(path, 250);
						sprintf(path, "%s%s%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_audio_init.m4a");
						output_audio_i = fopen(path, "w");
						int i = 0;
						// int fputc(int c, FILE *stream);
						for(i = 0; i < init_audio; i++) {
							fputc(destination_data[i], output_audio_i);
						}
						fclose(output_audio_i);
						printf("INIT i2libtest_%s_audio_init.m4a done\n", representation);
					}
			}
			if (previous_timestamp != timestamp) {
				sample_count++;
				duration_sample = ((timestamp - previous_timestamp) / AAC_48K_FREQUENCY_MS);
				decode_time = ((previous_timestamp - initial_timestamp) / AAC_48K_FREQUENCY_MS);
				duration_sample_f+= (((float)(timestamp - previous_timestamp))/((float) (AAC_48K_FREQUENCY_MS)));
				duration_sample_f-= (float) duration_sample;
				if (duration_sample_f >= 1) {
					//printf("ES MAYOR QUE UNO!!!!!!!!!!!!!!!!!!!!!!!\n");
					duration_sample++;
					duration_sample_f--;
				}
				decode_time_f= (((float)(previous_timestamp - initial_timestamp))/((float) (AAC_48K_FREQUENCY_MS)));
				decode_time_f-= (float) decode_time;
				if ((decode_time_f >= 0.5) ) {
					//printf("INCREMENTO DECODE\n");
					decode_time++;
					//decode_time_f--;
				}
				//printf("before add samples\n");
				seg_size = add_sample(source_data, size_source_data, duration_sample, decode_time, AUDIO_TYPE, destination_data, is_intra, &context);
				//printf("after add samples\n");
				//is_intra = 0;
				if (seg_size > I2ERROR_MAX) {
					//printf("initial time: %u previous time %u timestamp %u\ndecode time %u resta %u\n",  initial_timestamp, previous_timestamp, timestamp, decode_time, (previous_timestamp - initial_timestamp));
					char path[250];
					bzero(path, 250);
					printf("\nSEGMENT i2libtest_%s_audio_%d_1.m4a done\n", representation, segment_count);
					sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_audio_", segment_count, "_1.m4a");
					//printf("After path: %s\n", path);
					segment_count++;
					sample_count = 0;
					duration_sample_f = 0.00;
					//printf("OK VIDEO SEGMENT! %d\ninitial time: %u previous time %u\ndecode time %u\n", seg_size,  initial_timestamp, previous_timestamp, (((previous_timestamp - initial_timestamp) )/H264_FREQUENCY_MS));
					//printf("Before fopen file\n");
					output_audio_i = fopen(path, "w");
					//printf("After open file\n");
					int j = 0;
					// int fputc(int c, FILE *stream);
					//printf("Before write file\n");
					for(j = 0; j < seg_size; j++) {
						fputc(destination_data[j], output_audio_i);
					}
					fclose(output_audio_i);
					//printf("FILE CLOSE\n");
				}
				aac_length = c - RTP_LENGTH_HEADER - AAC_LENGTH_HEADER;
				memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER + AAC_LENGTH_HEADER, aac_length);
				size_source_data= aac_length;
			} else {//Same time
				aac_length = c - RTP_LENGTH_HEADER - AAC_LENGTH_HEADER;
				memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER + AAC_LENGTH_HEADER, aac_length);
				size_source_data+= aac_length;
			}
		} else {
			printf("5 sec %u\n", context->ctxaudio->segment_data_size);
			seg_size = finish_segment(AUDIO_TYPE, destination_data, &context);
			if (seg_size > I2ERROR_MAX) {
				char path[250];
				bzero(path, 250);
				printf("SEGMENT i2libtest_%s_audio_%d_1.m4a done\n", representation, segment_count);
				sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_audio_", segment_count, "_1.m4a");
				output_audio_i = fopen(path, "w");
				int j = 0;
				// int fputc(int c, FILE *stream);
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

