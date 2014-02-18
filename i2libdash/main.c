#include "i2libdash.h"
int main(){
	i2ctx *context;
	byte *sps_data, *pps_data, *metadata, *metadata2, *metadata3, *destination_data, *aac_data;
	uint32_t metadata_size, metadata2_size, metadata3_size, init_video, init_audio;
	uint32_t sps_size, pps_size, aac_data_size;

	FILE *output_video_i,*output_audio_i;

	context_initializer(&context);

	// INIT CONTEXT TEST

	printf("CONTEXT:\n DURATION %u, REFERENCE SIZE %u, TRESHH %f\n", context->duration_ms, context->reference_size, context->threshold_ms);

	printf("CONTEXT AUDIO:\n AAC_DATA_LENGTH %u, SEG_SIZE %u, CHANNELS %u SAMPLE_RATE %u SAMPLE_SIZE %u SEQNUM %u EPT %u LPT %u\n", context->ctxaudio->aac_data_length, context->ctxaudio->segment_data_size, context->ctxaudio->channels, context->ctxaudio->sample_rate, context->ctxaudio->sample_size, context->ctxaudio->sequence_number, context->ctxaudio->earliest_presentation_time, context->ctxaudio->latest_presentation_time);

	printf("CONTEXT VIDEO:\n PPS_SPS_DATA_LENGTH %u, SEG_SIZE %u WIDTH %u HEIGHT %u FPS %u EPT %u LPT %u SEQNUM %u\n", context->ctxvideo->pps_sps_data_length, context->ctxvideo->segment_data_size, context->ctxvideo->width, context->ctxvideo->height, context->ctxvideo->frame_rate, context->ctxvideo->earliest_presentation_time, context->ctxvideo->latest_presentation_time, context->ctxvideo->sequence_number);

	printf("CONTEXT SAMPLE AUDIO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxaudio->ctxsample->box_flags, context->ctxaudio->ctxsample->mdat_sample_length, context->ctxaudio->ctxsample->mdat_total_size, context->ctxaudio->ctxsample->moof_pos);

	printf("CONTEXT SAMPLE VIDEO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxvideo->ctxsample->box_flags, context->ctxvideo->ctxsample->mdat_sample_length, context->ctxvideo->ctxsample->mdat_total_size, context->ctxvideo->ctxsample->moof_pos);

	// INIT VIDEO HANDLER TEST

	// SPS
	sps_data = (byte *) malloc (100 * sizeof(byte*));
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
	pps_data = (byte *) malloc (100 * sizeof(byte*));
	pps_data[0] = 0x68;
	pps_data[1] = 0xCB;
	pps_data[2] = 0x81;
	pps_data[3] = 0x32;
	pps_data[4] = 0xC8;
	pps_size = 5;

	// METADATA
	metadata = (byte *) malloc (100 * sizeof(byte*));
	metadata[0] = 0x01;
	metadata[1] = 0x42;
	metadata[2] = 0xC0;
	metadata[3] = 0x1E;
	metadata_size = 4;

	// METADATA2
	metadata2 = (byte *) malloc (100 * sizeof(byte*));
	metadata2[0] = 0xFF;
	metadata2[1] = 0xE1;
	metadata2_size = 2;

	// METADATA3
	metadata3 = (byte *) malloc (100 * sizeof(byte*));
	metadata3[0] = 0x01;
	metadata3_size = 1;

	// DESTINATION DATA
	destination_data = (byte *) malloc (MAX_MDAT_SAMPLE * sizeof(byte*));

	// WIDTH AND HEIGHT TEST
	printf("sps_size: %u\n", sps_size);
	/*if(get_width_height(sps_data, &sps_size, &(context->ctxvideo)) != 0){
		printf("KO! get_width_height\n");
		return -1;
	}*/

	printf("WIDTH %u, HEIGHT %u\n", context->ctxvideo->width, context->ctxvideo->height);

	init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
	if(init_video != I2ERROR) {
		printf("OK!\n");
		output_video_i = fopen("/home/dovahkiin/dash_rtmp_segments/video_init2.m4v", "w");
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

	destination_data = (byte *) malloc (MAX_MDAT_SAMPLE * sizeof(byte*));

	init_audio = init_audio_handler(aac_data, aac_data_size, destination_data, &context);

	if(init_audio != I2ERROR) {
		printf("OK!\n");
		output_audio_i = fopen("/home/dovahkiin/dash_rtmp_segments/audio_init2.m4a", "w");
		int j = 0;
		// int fputc(int c, FILE *stream);
		for(j = 0; j < init_audio; j++) {
			fputc(destination_data[j], output_audio_i);
		}
		fclose(output_audio_i);
	}

	return 0;
}
