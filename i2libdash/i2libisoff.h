#ifndef __ISOFF_LIB__
#define __ISOFF_LIB__


#include "i2context.h"
//LIBRERIA ISOMEDIA

i2Err initVideoGenerator(u_char *sps, u_char *pps, i2ctx *context);

i2Err initAudioGenerator(u_char *aac_data, i2ctx *context);
//TODO mirar que es lo que nos importa de aac

i2Err segmentGenerator(u_char *data, int video_audio, i2ctx *context);






//PRIVATE esto en el .c
//ftyp for audio and video files is the same
int write_ftyp(u_char *data, int video_audio, i2ctx *context);

int write_moov(u_char *data, int video_audio, i2ctx *context);

//mvhd for audio and video files is the same
int write_mvhd(u_char *data, int video_audio, i2ctx *context);

//mvex for audio and video files is the same
int write_mvex(u_char *data, int video_audio, i2ctx *context);

//trex for audio and video files is the same
int write_trex(u_char *data, int video_audio, i2ctx *context);

int write_trak(u_char *data, int video_audio, i2ctx *context);

//trex for audio and video files is the same
int write_tkhd(u_char *data, int video_audio, i2ctx *context);

int write_mdia(u_char *data, int video_audio, i2ctx *context);

//mdhd for audio and video files is the same
int write_mdhd(u_char *data, int video_audio, i2ctx *context);

int write_hdlr(u_char *data, int video_audio, i2ctx *context);

int write_minf(u_char *data, int video_audio, i2ctx *context);

//only video
int write_vmhd(u_char *data);

//only audio
int write_smhd(u_char *data);

//mdhd for audio and video files is the same
int write_dinf(u_char *data, int video_audio);

//mdhd for audio and video files is the same
int write_dref(u_char *data, int video_audio);

int write_stbl(u_char *data, int video_audio, i2ctx *context);

int write_stsd(u_char *data, int video_audio, i2ctx *context);

//only video
int write_avc1(u_char *data, i2ctx_video ctxVideo);

//only video
int write_avcc(u_char *data, i2ctx_video ctxVideo);

//only audio
int write_mp4a(u_char *data, i2ctx_audio ctxAudio);

//only audio
int write_esds(u_char *data, i2ctx_audio ctxAudio);

//stts for audio and video files is the same
int write_stts(u_char *data, int video_audio, i2ctx *context);

//stsc for audio and video files is the same
int write_stsc(u_char *data, int video_audio, i2ctx *context);

//stsz for audio and video files is the same
int write_stsz(u_char *data, int video_audio, i2ctx *context);

//stco for audio and video files is the same
int write_stco(u_char *data, int video_audio, i2ctx *context);



//Nadim hasta aca estan todos los parametros ingresados, mañana lo miramos juntos


int write_styp(u_char *data, int video_audio);

int write_sidx(u_char *data, int video_audio);

int write_moof(u_char *data, int video_audio);

int write_mfhd(u_char *data, int video_audio);

int write_traf(u_char *data, int video_audio);

int write_tfhd(u_char *data, int video_audio);

int write_tfdt(u_char *data, int video_audio);

int write_trun(u_char *data, int video_audio);

int write_mdat(u_char *data, int video_audio);

#endif