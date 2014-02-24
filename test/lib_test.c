#include <i2libdash.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	i2ctx *context;
	byte *sps_data = NULL, *pps_data = NULL, *metadata = NULL, *metadata2 = NULL, *metadata3 = NULL;
	byte *destination_data = NULL, *source_data = NULL;
	uint32_t metadata_size = 0, metadata2_size = 0, metadata3_size = 0, init_video = 0, size_source_data = 0, initial_timestamp = 0;
	uint32_t sps_size = 0, pps_size = 0, duration_sample = 0, timestamp = 0, previous_timestamp = 0, i = 0, seg_size = 0;
	uint32_t nal_size = 0, hton_nal_size = 0, sample_count = 0, hton_size_source_data = 0;
	uint8_t i2error = 0, is_intra = 0, nal_type = 0, nri_type = 0, fbit = 0, start_bit = 0, end_bit = 0, nal_header = 0;
	uint8_t nal_unit_type = 0;
	struct sockaddr_in  sock_addr_input;
    socklen_t sockaddrlen = sizeof(struct sockaddr);
    int sock_origen;
    uint32_t c = 0, hton_timestamp = 0;
	byte buffer_in[3000];
	struct timeval to;
	fd_set ready;
	FILE *output_video_i;

	source_data = (byte *) malloc(MAX_MDAT_SAMPLE * 2);
    sock_origen = socket(AF_INET, SOCK_DGRAM, 0 );
    if(sock_origen == -1) {
		perror("Error socket\n");
		exit(-1);
	} //endif

    bzero((char *)&sock_addr_input, sizeof(sock_addr_input) );
    sock_addr_input.sin_family = AF_INET;
    sock_addr_input.sin_port = htons(10000);

	if (bind(sock_origen, (struct sockaddr *)&sock_addr_input, sizeof(sock_addr_input) ) == -1) {
		perror("Error bind\n");
		close(sock_origen);
		exit(-1);
	} //endif
	i2error= context_initializer(&context, VIDEO_TYPE);
	if (i2error == I2ERROR_MEDIA_TYPE) {
		printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
		exit(1);	
	}
	else
		printf("CONTEXT OK!\n");
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
			c = recvfrom (sock_origen, buffer_in, sizeof(buffer_in), 0, (struct sockaddr *)&sock_addr_input, &sockaddrlen);
			memcpy(&hton_timestamp, buffer_in+4, sizeof(hton_timestamp));
			nal_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NAL_TYPE;
			timestamp = htonl(hton_timestamp);
			printf("paquete %u %d\n", timestamp, c);
			if (nal_type == SPS_TYPE) {//SPS
				printf("SPS SPS SPS SPS SPS SPS\n");
				if (i == 0) {
					memcpy(sps_data, buffer_in+RTP_LENGTH_HEADER, (c-RTP_LENGTH_HEADER));
					sps_size = c-RTP_LENGTH_HEADER;
				}
			}
			if (nal_type == PPS_TYPE) {//PPS
				printf("PPS PPS PPS PPS PPS PPS\n");
				if (i == 1) {
					memcpy(pps_data, buffer_in + RTP_LENGTH_HEADER, (c-RTP_LENGTH_HEADER));
					pps_size = c-RTP_LENGTH_HEADER;
					init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
					if (init_video > I2ERROR_MAX) {
						printf("OK INIT VIDEO!\n");
						output_video_i = fopen("/tmp/pruebas/i2lib/i2libtest_480_video_init.m4v", "w");
						int i = 0;
						// int fputc(int c, FILE *stream);
						for(i = 0; i < init_video; i++) {
							fputc(destination_data[i], output_video_i);
						}
						fclose(output_video_i);
					}
					previous_timestamp = timestamp;
					initial_timestamp = timestamp;
					size_source_data = 0;
				}
			}
			if ((i > 1) && (nal_type != PPS_TYPE) && (nal_type != SPS_TYPE)) {

				if (previous_timestamp != timestamp) {
					duration_sample = (((timestamp - previous_timestamp) * SEC_TO_MSEC)/H264_FREQUENCY);
					//TODO: is intra
					if (initial_timestamp == previous_timestamp) {
						is_intra = 1;
						printf("IS INTRA\n");
					}
					else
						is_intra = 0;
					sample_count++;
					seg_size = add_sample(source_data, size_source_data, duration_sample, previous_timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
					printf("Packet number %u, seg_size %u, duration %u\n", i, seg_size, duration_sample);
					if (seg_size > I2ERROR_MAX) {
						printf("OK VIDEO SEGMENT! %d\n", seg_size);
						output_video_i = fopen("/tmp/pruebas/i2lib/i2libtest_480_video_0_1.m4v", "w");
						int j = 0;
						// int fputc(int c, FILE *stream);
						for(j = 0; j < seg_size; j++) {
							fputc(destination_data[j], output_video_i);
						}
						fclose(output_video_i);
					}
					if (nal_type == FUA_TYPE) {	//Fragmentation unit
						uint8_t raro;
						nal_unit_type = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & NAL_UNIT_TYPE;
						nri_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NRI_TYPE;
						fbit = (*(buffer_in + RTP_LENGTH_HEADER)) & FORBIDDEN_BIT;
						start_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & START_BIT;
						end_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & END_BIT;
						nal_header = fbit | nri_type | nal_unit_type;
						
						if (start_bit) {
							printf ("start bit %u\n", timestamp);
							memcpy(source_data + LENGTH_SIZE, &nal_header, 1);
							size_source_data = 1;
						}
						nal_size = c - RTP_LENGTH_HEADER - H264_LENGTH_HEADER;
						printf("NAL fragment %u %u %u %u %u %u\n", nal_type, nri_type, fbit, start_bit, end_bit, nal_size);
						memcpy(source_data + size_source_data + LENGTH_SIZE, buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER, nal_size);
						raro = (*(buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER + 1)) - 32;
						memcpy(source_data + size_source_data + LENGTH_SIZE + 1, &raro, 1);
						printf("el raro %x\n", raro);
						size_source_data += nal_size;
					} else {//Single NAL unit packet per H.264 
						nal_size = c - RTP_LENGTH_HEADER;
						hton_nal_size = htonl(nal_size);
						memcpy(source_data, &hton_nal_size, LENGTH_SIZE);
						size_source_data = LENGTH_SIZE;
						memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER, nal_size);
						size_source_data += nal_size;
					}
					previous_timestamp = timestamp;
				} else {
					if (nal_type == FUA_TYPE) {	//Fragmentation unit
						
						nri_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NRI_TYPE;
						fbit = (*(buffer_in + RTP_LENGTH_HEADER)) & FORBIDDEN_BIT;
						start_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & START_BIT;
						end_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & END_BIT;
						
						/*nal_header = fbit | nri_type | nal_type;
						if (start_bit) {
							memcpy(source_data + LENGTH_SIZE, &nal_header, 1);
							size_source_data = LENGTH_SIZE + 1;
						}*/
						nal_size = c - RTP_LENGTH_HEADER - H264_LENGTH_HEADER;
						printf("NAL fragment %u %u %u %u %u %u\n", nal_type, nri_type, fbit, start_bit, end_bit, nal_size);
						memcpy(source_data + size_source_data + LENGTH_SIZE, buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER, nal_size);
						size_source_data += nal_size;
						if (end_bit) {							
							hton_size_source_data = htonl(size_source_data);
							memcpy(source_data, &hton_size_source_data, LENGTH_SIZE);
							size_source_data += LENGTH_SIZE;
						}
						
					} else {//Single NAL unit packet per H.264 
						nal_size = c - RTP_LENGTH_HEADER;
						hton_nal_size = htonl(nal_size);
						memcpy(source_data + size_source_data, &hton_nal_size, 4);
						size_source_data += 4;
						memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER, nal_size);
						size_source_data += nal_size;
					}
					//printf("Packet number %u, size_source_data %u\n", i, size_source_data);
				}
			} 
			if (sample_count == 212) {
				printf("212 samples %u\n", context->ctxvideo->segment_data_size);
				seg_size = finish_segment(VIDEO_TYPE, destination_data, &context);
				if (seg_size > I2ERROR_MAX) {
					printf("OK VIDEO SEGMENT! %d\n", seg_size);
					output_video_i = fopen("/tmp/pruebas/i2lib/i2libtest_480_video_0_1.m4v", "w");
					int j = 0;
					// int fputc(int c, FILE *stream);
					for(j = 0; j < seg_size; j++) {
						fputc(destination_data[j], output_video_i);
					}
					fclose(output_video_i);
				}
				break;
			}
						
		} else {
			printf("5 sec %u\n", context->ctxvideo->segment_data_size);
			seg_size = finish_segment(VIDEO_TYPE, destination_data, &context);
			if (seg_size > I2ERROR_MAX) {
				printf("OK VIDEO SEGMENT! %d\n", seg_size);
				output_video_i = fopen("/tmp/pruebas/i2lib/i2libtest_480_video_0_1.m4v", "w");
				int j = 0;
				// int fputc(int c, FILE *stream);
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

