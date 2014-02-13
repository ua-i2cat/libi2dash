#include "i2libdash.h"
int main(){
	i2ctx *context;
	uint8_t width_height;
	byte *source_data;
	uint32_t size_sps_data;

	context_initializer(&context);

	// INIT CONTEXT TEST

	printf("CONTEXT:\n DURATION %u, REFERENCE SIZE %u, TRESHH %f\n", context->duration_ms, context->reference_size, context->threshold_ms);

	printf("CONTEXT AUDIO:\n AAC_DATA_LENGTH %u, SEG_SIZE %u, CHANNELS %u SAMPLE_RATE %u SAMPLE_SIZE %u SEQNUM %u EPT %u LPT %u\n", context->ctxaudio->aac_data_length, context->ctxaudio->segment_size, context->ctxaudio->channels, context->ctxaudio->sample_rate, context->ctxaudio->sample_size, context->ctxaudio->sequence_number, context->ctxaudio->earliest_presentation_time, context->ctxaudio->latest_presentation_time);

	printf("CONTEXT VIDEO:\n PPS_SPS_DATA_LENGTH %u, SEG_SIZE %u WIDTH %u HEIGHT %u FPS %u EPT %u LPT %u SEQNUM %u\n", context->ctxvideo->pps_sps_data_length, context->ctxvideo->segment_size, context->ctxvideo->width, context->ctxvideo->height, context->ctxvideo->frame_rate, context->ctxvideo->earliest_presentation_time, context->ctxvideo->latest_presentation_time, context->ctxvideo->sequence_number);

	printf("CONTEXT SAMPLE AUDIO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxaudio->ctxsample->box_flags, context->ctxaudio->ctxsample->mdat_sample_length, context->ctxaudio->ctxsample->mdat_total_size, context->ctxaudio->ctxsample->moof_pos);

	printf("CONTEXT SAMPLE VIDEO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxvideo->ctxsample->box_flags, context->ctxvideo->ctxsample->mdat_sample_length, context->ctxvideo->ctxsample->mdat_total_size, context->ctxvideo->ctxsample->moof_pos);

	// WIDTH AND HEIGHT TEST

	// En este caso es el SPS/PPS, etc
	source_data = (byte *) malloc (100 * sizeof(byte*));
	source_data[0] = 0x67;
	source_data[1] = 0x42;
	source_data[2] = 0xC0;
	source_data[3] = 0x1E;
	source_data[4] = 0xD9;
	source_data[5] = 0x00;
	source_data[6] = 0xD8;
	source_data[7] = 0x3D;
	source_data[8] = 0xE6;
	source_data[9] = 0xE1;
	source_data[10] = 0x00;
	source_data[11] = 0x00;
	source_data[12] = 0x03;
	source_data[13] = 0x00;
	source_data[14] = 0x01;
	source_data[15] = 0x00;
	source_data[16] = 0x00;
	source_data[17] = 0x03;
	source_data[18] = 0x00;
	source_data[19] = 0x30;
	source_data[20] = 0x0F;
	source_data[21] = 0x16;
	source_data[22] = 0x2E;
	source_data[23] = 0x48;

	size_sps_data = 24;

	width_height = get_width_height(source_data, &size_sps_data, &(context->ctxvideo));

	if(width_height != 0){
		printf("KO! get_width_height\n");
		return -1;
	}

	printf("WIDTH %u, HEIGHT %u\n", context->ctxvideo->width, context->ctxvideo->height);

	return 0;
}
