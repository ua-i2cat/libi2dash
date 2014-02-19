#include "i2libdash.h"
int main(){
	i2ctx *context;
	byte *sps_data, *pps_data, *metadata, *metadata2, *metadata3, *destination_data, *aac_data, *source_data;
	uint32_t metadata_size, metadata2_size, metadata3_size, init_video, init_audio, size_source_data;
	uint32_t sps_size, pps_size, aac_data_size, duration_sample, timestamp, seg_size, i;
	uint8_t is_intra, i2error;

	FILE *output_video_i,*output_audio_i;

	i2error= context_initializer(&context, NO_TYPE);
	if (i2error == I2OK)
		printf ("CONTEXT OK!\n");
	else {
		printf("CONTEXT NO OK!\n");
	}

	i2error= context_initializer(&context, AUDIOVIDEO_TYPE);
	if (i2error == I2OK)
		printf ("CONTEXT OK!\n");
	else {
		printf("CONTEXT NO OK!\n");
		exit(1);
	}
		
	// INIT CONTEXT TEST

	printf("CONTEXT:\n DURATION %u, REFERENCE SIZE %u, TRESHH %u\n", context->duration_ms, context->reference_size, context->threshold_ms);

	printf("CONTEXT AUDIO:\n AAC_DATA_LENGTH %u, SEG_SIZE %u, CHANNELS %u SAMPLE_RATE %u SAMPLE_SIZE %u SEQNUM %u EPT %u LPT %u\n", context->ctxaudio->aac_data_length, context->ctxaudio->segment_data_size, context->ctxaudio->channels, context->ctxaudio->sample_rate, context->ctxaudio->sample_size, context->ctxaudio->sequence_number, context->ctxaudio->earliest_presentation_time, context->ctxaudio->latest_presentation_time);

	printf("CONTEXT VIDEO:\n PPS_SPS_DATA_LENGTH %u, SEG_SIZE %u WIDTH %u HEIGHT %u FPS %u EPT %u LPT %u SEQNUM %u\n", context->ctxvideo->pps_sps_data_length, context->ctxvideo->segment_data_size, context->ctxvideo->width, context->ctxvideo->height, context->ctxvideo->frame_rate, context->ctxvideo->earliest_presentation_time, context->ctxvideo->latest_presentation_time, context->ctxvideo->sequence_number);

	printf("CONTEXT SAMPLE AUDIO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxaudio->ctxsample->box_flags, context->ctxaudio->ctxsample->mdat_sample_length, context->ctxaudio->ctxsample->mdat_total_size, context->ctxaudio->ctxsample->moof_pos);

	printf("CONTEXT SAMPLE VIDEO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxvideo->ctxsample->box_flags, context->ctxvideo->ctxsample->mdat_sample_length, context->ctxvideo->ctxsample->mdat_total_size, context->ctxvideo->ctxsample->moof_pos);

	// INIT VIDEO HANDLER TEST

	// SPS
	sps_data = (byte *) malloc (100);
	sps_data[0] = 0x67;
	sps_data[1] = 0x42;
	sps_data[2] = 0xC0;
	sps_data[3] = 0x1E;
	sps_data[4] = 0xD9;
	sps_data[5] = 0x00;
	sps_data[6] = 0xD8;
	sps_data[7] = 0x3D;
	sps_data[8] = 0xE6;
	sps_data[9] = 0xE1;
	sps_data[10] = 0x00;
	sps_data[11] = 0x00;
	sps_data[12] = 0x03;
	sps_data[13] = 0x00;
	sps_data[14] = 0x01;
	sps_data[15] = 0x00;
	sps_data[16] = 0x00;
	sps_data[17] = 0x03;
	sps_data[18] = 0x00;
	sps_data[19] = 0x30;
	sps_data[20] = 0x0F;
	sps_data[21] = 0x16;
	sps_data[22] = 0x2E;
	sps_data[23] = 0x48;
	sps_size = 24;

	// PPS
	pps_data = (byte *) malloc (100);
	pps_data[0] = 0x68;
	pps_data[1] = 0xCB;
	pps_data[2] = 0x81;
	pps_data[3] = 0x32;
	pps_data[4] = 0xC8;
	pps_size = 5;

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
	destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);

	// WIDTH AND HEIGHT TEST
	printf("sps_size: %u\n", sps_size);
	/*if(get_width_height(sps_data, &sps_size, &(context->ctxvideo)) != 0){
		printf("KO! get_width_height\n");
		return -1;
	}*/

	printf("WIDTH %u, HEIGHT %u\n", context->ctxvideo->width, context->ctxvideo->height);

	init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
	if(init_video != I2ERROR) {
		printf("OK INIT VIDEO!\n");
		output_video_i = fopen("/tmp/pruebas/i2dash/video_init2.m4v", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < init_video; i++) {
			fputc(destination_data[i], output_video_i);
		}
		fclose(output_video_i);
	}

	// INIT AUDIO HANDLER TEST

	// AAC METADATA
	aac_data = (byte *) malloc (100 * sizeof(byte*));
	aac_data[0] = 0xaf;
	aac_data[1] = 0x00;
	aac_data[2] = 0x11;
	aac_data[3] = 0x90;

	aac_data_size = 4;

	destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);

	init_audio = init_audio_handler(aac_data, aac_data_size, destination_data, &context);

	if(init_audio != I2ERROR) {
		printf("OK INIT AUDIO!\n");
		output_audio_i = fopen("/tmp/pruebas/i2dash/audio_init2.m4a", "w");
		int j = 0;
		// int fputc(int c, FILE *stream);
		for(j = 0; j < init_audio; j++) {
			fputc(destination_data[j], output_audio_i);
		}
		fclose(output_audio_i);
	}

printf("CONTEXT:\n DURATION %u, REFERENCE SIZE %u, TRESHH %u\n", context->duration_ms, context->reference_size, context->threshold_ms);
	//VIDEO DATA
	source_data = (byte *) malloc (100);
	source_data[0] = 0x0;
	source_data[1] = 0x0;
	source_data[2] = 0x02;
	source_data[3] = 0x6E;
	source_data[4] = 0x06;
	source_data[5] = 0x05;
	source_data[6] = 0xFF;
	source_data[7] = 0xFF;
	source_data[8] = 0x6A;
	source_data[9] = 0xDC;
	source_data[10] = 0x45;
	source_data[11] = 0xE9;
	source_data[12] = 0xBD;
	source_data[13] = 0xE6;
	source_data[14] = 0xD9;
	source_data[15] = 0x48;
	source_data[16] = 0xB7;
	source_data[17] = 0x96;
	source_data[18] = 0x2C;
	source_data[19] = 0xD8;
	source_data[20] = 0x20;
	source_data[21] = 0xD9;
	source_data[22] = 0x23;
	source_data[23] = 0xEE;
	source_data[24] = 0xEF;
	source_data[25] = 0x78;
	source_data[26] = 0x32;
	source_data[27] = 0x36;
	source_data[28] = 0x34;
	source_data[29] = 0x20;
	source_data[30] = 0x2D;
	source_data[31] = 0x20;
	source_data[32] = 0x43;
	source_data[33] = 0x6F;
	source_data[34] = 0x70;
	source_data[35] = 0x79;
	source_data[36] = 0x6C;
	source_data[37] = 0x65;
	source_data[38] = 0x66;
	source_data[39] = 0x75;

	size_source_data = 40;
	duration_sample = 10;
	timestamp = 0;
	is_intra = 1;
	destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);
	seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
	is_intra = 0;
	for (i=0; i<500; i++) {
		timestamp += 10;
		seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
	}
	is_intra = 1;
	timestamp += 10;
	seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
	printf("Segment size %d\n", seg_size);

	if(init_video != I2ERROR) {
		printf("OK VIDEO SEGMENT!\n");
		output_video_i = fopen("/tmp/pruebas/i2dash/video_seg.m4v", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < seg_size; i++) {
			fputc(destination_data[i], output_video_i);
		}
		fclose(output_video_i);
	}


	return 0;
}
