#include "i2libdash.h"
#include "../i2libisoff/i2libisoff.h"

// Función recoge h264 y obtiene sps y pps, rellena el context con width y height.
uint32_t h264_handler(byte *input_data, uint32_t size_input, i2ctx *context);
// Privada. Función te dice si un sample es intra o no.
uint8_t is_key_frame(byte *input_data, uint32_t size_input);

void set_segment_duration(uint32_t segment_duration, i2ctx *context){
	context->duration_ms = segment_duration;
}

uint32_t get_segment_duration(i2ctx *context){
	return context->duration_ms;
}

void set_frame_rate(uint32_t frame_rate, i2ctx_video *ctxVideo){
	ctxVideo->frame_rate = frame_rate;
}

uint32_t get_frame_rate(i2ctx_video *ctxVideo){
	return ctxVideo->frame_rate;
}

void set_sample_rate(uint32_t sample_rate, i2ctx_audio *ctxAudio){
	ctxAudio->sample_rate = sample_rate;
}

uint32_t get_sample_rate(i2ctx_audio *ctxAudio){
	return ctxAudio->sample_rate;
}