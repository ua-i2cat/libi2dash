#ifndef __DASH_LIB__
#define __DASH_LIB__

#include "../include/i2context.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función encargada de gestionar las llamadas a segmentGenerator de i2libisoff, determina longitud segmentos
uint32_t add_sample(byte *input_data, uint32_t size_input, uint32_t duration_sample, uint32_t timestamp, uint32_t media_type, byte *output_data, i2ctx *context);
// Similar al de i2libisoff pero obteniendo datos al context, input sps/pps
uint32_t init_video_handler(byte *input_data, uint32_t size_input, byte *output_data, i2ctx *context);
// Similar al de i2libisoff pero obteniendo datos al context, input 
uint32_t init_audio_handler(byte *input_data, uint32_t size_input, byte *output_data, i2ctx *context);
// Función que reserva memoria para el context
uint32_t context_initializer(i2ctx *context);

#endif

