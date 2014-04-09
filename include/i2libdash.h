#ifndef __DASH_LIB__
#define __DASH_LIB__

#include "i2context.h"
#include "h264_stream.h"
#include "i2libisoff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t context_initializer(i2ctx **context, uint32_t media_type);

uint32_t init_video_handler(byte *metadata, uint32_t metadata_size, byte *metadata2, uint32_t metadata2_size, byte *sps_data, uint32_t *sps_size, byte *metadata3, uint32_t metadata3_size, byte *pps_data, uint32_t pps_size, byte *output_data, i2ctx **context);

uint32_t init_audio_handler(byte *input_data, uint32_t size_input, byte *output_data, i2ctx **context);

uint32_t add_sample(byte *input_data, uint32_t size_input, uint32_t duration_sample, uint32_t timestamp, uint32_t media_type, byte *output_data, uint8_t is_intra, i2ctx **context);

uint32_t finish_segment(uint32_t media_type, byte *output_data, i2ctx **context);

void set_segment_duration(uint32_t segment_duration, i2ctx **context);

uint32_t get_segment_duration(i2ctx *context);

void set_frame_rate(uint32_t frame_rate, i2ctx **context);

uint32_t get_frame_rate(i2ctx *context);

void set_sample_rate(uint32_t sample_rate, i2ctx **context);

uint32_t get_sample_rate(i2ctx *context);

#endif

