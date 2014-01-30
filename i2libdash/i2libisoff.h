#ifndef __ISOFF_LIB__
#define __ISOFF_LIB__

#define I2ERROR 1

#include "i2context.h"
#include <netinet/in.h>
//ISOMEDIA LIBRARY


i2Err initVideoGenerator(byte *sps, byte *pps, i2ctx *context);

i2Err initAudioGenerator(byte *aac_data, i2ctx *context);
//TODO mirar que es lo que nos importa de aac

i2Err segmentGenerator(byte *data, uint32_t video_audio, i2ctx *context);

#endif
