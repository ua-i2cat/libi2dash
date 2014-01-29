#ifndef __ISOFF_LIB__
#define __ISOFF_LIB__


#include "i2context.h"
//LIBRERIA ISOMEDIA

i2Err initVideoGenerator(u_char *sps, u_char *pps, i2ctx *context);

i2Err initAudioGenerator(u_char *aac_data, i2ctx *context);
//TODO mirar que es lo que nos importa de aac

i2Err segmentGenerator(u_char *data, int video_audio, i2ctx *context);

#endif