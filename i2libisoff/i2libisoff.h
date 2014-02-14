#ifndef __ISOFF_LIB__
#define __ISOFF_LIB__


#include "../include/i2context.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ISOMEDIA LIBRARY


uint32_t initVideoGenerator(byte *source_data, uint32_t size_source_data, byte *destination_data, i2ctx **context);

uint32_t initAudioGenerator(byte *source_data, uint32_t size_source_data, byte *destination_data, i2ctx **context);

uint32_t segmentGenerator(byte *source_data, uint32_t size_source_data, byte *destination_data, uint32_t media_type, i2ctx **context);

#endif
