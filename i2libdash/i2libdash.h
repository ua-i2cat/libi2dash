#ifndef __DASH_LIB__
#define __DASH_LIB__

#include "../include/i2context.h"
#include "../include/h264_stream.h"
#include "../i2libisoff/i2libisoff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función encargada de gestionar las llamadas a segmentGenerator de i2libisoff, determina longitud segmentos
uint32_t add_sample(byte *input_data, uint32_t size_input, uint32_t duration_sample, uint32_t timestamp, uint32_t media_type, byte *output_data, i2ctx *context);
// Similar al de i2libisoff pero obteniendo datos al context, input sps/pps
uint32_t init_video_handler(byte *metadata, uint32_t metadata_size, byte *sps_data, uint32_t sps_size, byte *pps_data, uint32_t pps_size, byte *output_data, i2ctx *context);
// Similar al de i2libisoff pero obteniendo datos al context, input 
uint32_t init_audio_handler(byte *input_data, uint32_t size_input, byte *output_data, i2ctx *context);
// Función que reserva memoria para el context
void context_initializer(i2ctx **context);
// Setter de duración de segmento
void set_segment_duration(uint32_t segment_duration, i2ctx *context);
// Getter de duración de segmento
uint32_t get_segment_duration(i2ctx *context);
// Setter de frame rate para vídeo
void set_frame_rate(uint32_t frame_rate, i2ctx_video *ctxVideo);
// Getter de frame rate para vídeo
uint32_t get_frame_rate(i2ctx_video *ctxVideo);
// Setter de sample rate para audio
void set_sample_rate(uint32_t sample_rate, i2ctx_audio *ctxAudio);
// Getter de sample rate para audio
uint32_t get_sample_rate(i2ctx_audio *ctxAudio);

#endif

