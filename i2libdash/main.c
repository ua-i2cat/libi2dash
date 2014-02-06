#include "i2libisoff.h"

int main(){
	byte *source_data;
	byte *destination_data;
	uint32_t size_source_data;

	FILE *output_video_i, *output_audio_i;

	i2ctx *context = (i2ctx *) malloc(sizeof(i2ctx));
	context->ctxaudio = (i2ctx_audio *) malloc(sizeof(i2ctx_audio));
	context->ctxvideo = (i2ctx_video *) malloc(sizeof(i2ctx_video));

	i2ctx_audio *ctxAudio = context->ctxaudio; 
	i2ctx_video *ctxVideo = context->ctxvideo;
	//i2ctx_sample *ctxASample = ctxAudio->ctxsample;
	//i2ctx_sample *ctxVSample = ctxVideo->ctxsample;
	ctxVideo->width = 854;
	ctxVideo->height = 480;
	ctxAudio->channels = 2;
	ctxAudio->sample_size = 2; // write_mp4a --> sample_size * 8
	// ctxAudio->sample_rate = 1000;
	ctxAudio->sample_rate = 48000;

	uint32_t initVideo, initAudio;

	// uint32_t media_type = AUDIO_TYPE;
	//uint32_t media_type = VIDEO_TYPE;
	// En este caso es el SPS/PPS, etc
	source_data = (byte *) calloc (100, sizeof(byte*));
	source_data[0] = 0x01;
	source_data[1] = 0x42;
	source_data[2] = 0xC0;
	source_data[3] = 0x1E;
	source_data[4] = 0xFF;
	source_data[5] = 0xE1;
	source_data[6] = 0x00;
	source_data[7] = 0x18;
	source_data[8] = 0x67;
	source_data[9] = 0x42;
	source_data[10] = 0xC0;
	source_data[11] = 0x1E;
	source_data[12] = 0xD9;
	source_data[13] = 0x00;
	source_data[14] = 0xD8;
	source_data[15] = 0x3D;
	source_data[16] = 0xE6;
	source_data[17] = 0xE1;
	source_data[18] = 0x00;
	source_data[19] = 0x00;
	source_data[20] = 0x03;
	source_data[21] = 0x00;
	source_data[22] = 0x01;
	source_data[23] = 0x00;
	source_data[24] = 0x00;
	source_data[25] = 0x03;
	source_data[26] = 0x00;
	source_data[27] = 0x30;
	source_data[28] = 0x0F;
	source_data[29] = 0x16;
	source_data[30] = 0x2E;
	source_data[31] = 0x48;
	source_data[32] = 0x01;
	source_data[33] = 0x00;
	source_data[34] = 0x05;
	source_data[35] = 0x68;
	source_data[36] = 0xCB;
	source_data[37] = 0x81;
	source_data[38] = 0x32;
	source_data[39] = 0xC8;

	size_source_data = 40;

	destination_data = (byte *) calloc (MAX_MDAT_SAMPLE, sizeof(byte*));

	initVideo = initVideoGenerator(source_data, size_source_data, destination_data, context);

	if(initVideo != I2ERROR) {
		printf("OK!\n");
		output_video_i = fopen("/home/dovahkiin/dash_rtmp_segments/output_i2.m4v", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < initVideo; i++) {
			fputc(destination_data[i], output_video_i);
		}
		fclose(output_video_i);
	}
	
	//free(source_data);
	//free(destination_data);

	source_data = (byte *) calloc (100, sizeof(byte*));
	source_data[0] = 0xaf;
	source_data[1] = 0x00;
	source_data[2] = 0x11;
	source_data[3] = 0x90;

	size_source_data = 4;

	destination_data = (byte *) calloc (MAX_MDAT_SAMPLE, sizeof(byte*));

	initAudio = initAudioGenerator(source_data, size_source_data, destination_data, context);

	if(initAudio != I2ERROR) {
		printf("OK!\n");
		output_audio_i = fopen("/home/dovahkiin/dash_rtmp_segments/output_i2.m4a", "w");
		int i = 0;
		// int fputc(int c, FILE *stream);
		for(i = 0; i < initAudio; i++) {
			fputc(destination_data[i], output_audio_i);
		}
		fclose(output_audio_i);
	}

	return 0;
}
