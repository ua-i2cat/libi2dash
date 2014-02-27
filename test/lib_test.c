#include <i2libdash.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

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
	FILE *output_video_i;
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
			uint16_t hton_seq_num = 0, seq_num;
			//printf("Entro %u\n", i);
			c = recvfrom (sock_origen, buffer_in, sizeof(buffer_in), 0, (struct sockaddr *)&sock_addr_input, &sockaddrlen);
			memcpy(&hton_timestamp, buffer_in+4, sizeof(hton_timestamp));
			memcpy(&hton_seq_num, buffer_in + 2, sizeof(hton_seq_num));
			seq_num = ntohs(hton_seq_num);
			//printf("Packet number %u seq_num %u\n", (i+1), seq_num);
			//printf ("Memcpy timestamp\n");
			nal_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NAL_TYPE;
			timestamp = htonl(hton_timestamp);
			if (i == 0) {
				previous_timestamp = timestamp;
				initial_timestamp = timestamp;
				decode_time = 0;
				size_source_data = 0;
			}
			if (nal_type == SPS_TYPE) {//SPS
				if (i < 2) {
					memcpy(sps_data, buffer_in+RTP_LENGTH_HEADER, (c-RTP_LENGTH_HEADER));
					sps_size = c-RTP_LENGTH_HEADER;
				}
			}
			if (nal_type == PPS_TYPE) {//PPS
				if (i < 3) {
					memcpy(pps_data, buffer_in + RTP_LENGTH_HEADER, (c-RTP_LENGTH_HEADER));
					pps_size = c-RTP_LENGTH_HEADER;
					init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
					if (init_video > I2ERROR_MAX) {
						char path[250];
						bzero(path, 250);
						printf("INIT i2libtest_%s_video_init.m4v done\n", representation);
						sprintf(path, "%s%s%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_video_init.m4v");
						//printf("OK INIT VIDEO!\n");
						output_video_i = fopen(path, "w");
						int i = 0;
						// int fputc(int c, FILE *stream);
						for(i = 0; i < init_video; i++) {
							fputc(destination_data[i], output_video_i);
						}
						fclose(output_video_i);
					}
				}
			}
			if ((nal_type != PPS_TYPE) && (nal_type != SPS_TYPE)) {
				//printf ("nal type %u\n", nal_type);
				if (previous_timestamp != timestamp) {
					duration_sample = ((timestamp - previous_timestamp) / H264_FREQUENCY_MS);
					//TODO: is intra
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
					//printf("initial time: %u previous time %u timestamp %u\ndecode time %u duration sample %u\n",  initial_timestamp, previous_timestamp, timestamp, (((previous_timestamp - initial_timestamp) * SEC_TO_MSEC)/H264_FREQUENCY), duration_sample);
					duration_sample_f+= (((float)(timestamp - previous_timestamp))/((float) (H264_FREQUENCY_MS)));
					duration_sample_f-= (float) duration_sample;
					if (duration_sample_f >= 1) {
						//printf("ES MAYOR QUE UNO!!!!!!!!!!!!!!!!!!!!!!!\n");
						duration_sample++;
						duration_sample_f--;
					}
					decode_time_f= (((float)(previous_timestamp - initial_timestamp))/((float) (H264_FREQUENCY_MS)));
					decode_time_f-= (float) decode_time;
					if ((decode_time_f >= 0.5) ) {
						//printf("INCREMENTO DECODE\n");
						decode_time++;
						//decode_time_f--;
					}
					//printf("before add samples\n");
					seg_size = add_sample(source_data, size_source_data, duration_sample, decode_time, VIDEO_TYPE, destination_data, is_intra, &context);
					//printf("after add samples\n");
					is_intra = 0;
					//printf("Packet number %u, seg_size %u, duration %u duration float %f\n ", i, seg_size, duration_sample, duration_sample_f);
					if (seg_size > I2ERROR_MAX) {
						//printf("initial time: %u previous time %u timestamp %u\ndecode time %u resta %u\n",  initial_timestamp, previous_timestamp, timestamp, decode_time, (previous_timestamp - initial_timestamp));
						char path[250];
						bzero(path, 250);
						printf("\nSEGMENT i2libtest_%s_video_%d_1.m4v done\n", representation, segment_count);
						sprintf(path, "%s%s%s%d%s","/tmp/pruebas/i2lib/i2libtest_", representation, "_video_", segment_count, "_1.m4v");
						//printf("After path: %s\n", path);
						segment_count++;
						sample_count = 0;
						duration_sample_f = 0.00;
						//printf("OK VIDEO SEGMENT! %d\ninitial time: %u previous time %u\ndecode time %u\n", seg_size,  initial_timestamp, previous_timestamp, (((previous_timestamp - initial_timestamp) )/H264_FREQUENCY_MS));
						//printf("Before fopen file\n");
						output_video_i = fopen(path, "w");
						//printf("After open file\n");
						int j = 0;
						// int fputc(int c, FILE *stream);
						//printf("Before write file\n");
						for(j = 0; j < seg_size; j++) {
							fputc(destination_data[j], output_video_i);
						}
						fclose(output_video_i);
						//printf("FILE CLOSE\n");
					}
					if (nal_type == FUA_TYPE) {	//Fragmentation unit
						//printf("FUA\n");
						nal_unit_type = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & NAL_UNIT_TYPE;
						nri_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NRI_TYPE;
						fbit = (*(buffer_in + RTP_LENGTH_HEADER)) & FORBIDDEN_BIT;
						start_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & START_BIT;
						end_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & END_BIT;
						
						
						if (start_bit) {
							nal_length = 0;
							nal_header = fbit | nri_type | nal_unit_type;
							size_source_data = LENGTH_SIZE;
							//printf ("start bit %u\n", i);
							memcpy(source_data + LENGTH_SIZE, &nal_header, 1);
							size_source_data += 1;
							sum_nal = 1;
						}
						nal_size = c - RTP_LENGTH_HEADER - H264_LENGTH_HEADER;
						//printf("NAL fragment nal_type %u, nri_type %x, fbit %x\nstart_bit %x, end_bit %x, nal_size %u, nal_unit_type %u\n", nal_type, nri_type, fbit, start_bit, end_bit, nal_size, nal_unit_type);
						//printf("before add samples\n");
						memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER, nal_size);
						//raro = (*(buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER + 1)) - 32;
						//memcpy(source_data + size_source_data + LENGTH_SIZE + 1, &raro, 1);
						//printf("el raro %x\n", raro);
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
					if (nal_type == FUA_TYPE) {	//Fragmentation unit
						nal_unit_type = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & NAL_UNIT_TYPE;
						nri_type = (*(buffer_in + RTP_LENGTH_HEADER)) & NRI_TYPE;
						fbit = (*(buffer_in + RTP_LENGTH_HEADER)) & FORBIDDEN_BIT;
						start_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & START_BIT;
						end_bit = (*(buffer_in + RTP_LENGTH_HEADER + 1)) & END_BIT;
						
						
						if (start_bit) {
							//printf ("start bit %u\n", i);
							nal_length = size_source_data;
							nal_header = fbit | nri_type | nal_type;
							size_source_data += LENGTH_SIZE;
							memcpy(source_data + size_source_data, &nal_header, 1);
							size_source_data += 1;
							sum_nal = 1;
						}
						if (nal_unit_type == INTRA_TYPE)
							is_intra = 1;
						nal_size = c - RTP_LENGTH_HEADER - H264_LENGTH_HEADER;
						//printf("NAL fragment nal_type %u, nri_type %x, fbit %x\nstart_bit %x, end_bit %x, nal_size %u, nal_unit_type %u\n", nal_type, nri_type, fbit, start_bit, end_bit, nal_size, nal_unit_type);
						memcpy(source_data + size_source_data, buffer_in + RTP_LENGTH_HEADER + H264_LENGTH_HEADER, nal_size);
						size_source_data += nal_size;
						sum_nal += nal_size;
						if (end_bit) {
							//printf ("end bit %u\n", (i+1));				
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
						//printf("Single NAL Packet number %u, size_source_data %u\n", (i+1), size_source_data);
					}
					//printf("Packet number %u, size_source_data %u\n", (i+1), size_source_data);
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

