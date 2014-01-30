#include "i2libisoff.h"

//ftyp for audio and video files is the same
uint32_t write_ftyp(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_moov(byte *data, uint32_t video_audio, i2ctx *context);

//mvhd for audio and video files is the same
uint32_t write_mvhd(byte *data, uint32_t video_audio, i2ctx *context);

//mvex for audio and video files is the same
uint32_t write_mvex(byte *data, uint32_t video_audio, i2ctx *context);

//trex for audio and video files is the same
uint32_t write_trex(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_trak(byte *data, uint32_t video_audio, i2ctx *context);

//trex for audio and video files is the same
uint32_t write_tkhd(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_mdia(byte *data, uint32_t video_audio, i2ctx *context);

//mdhd for audio and video files is the same
uint32_t write_mdhd(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_hdlr(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_minf(byte *data, uint32_t video_audio, i2ctx *context);

//only video
uint32_t write_vmhd(byte *data);

//only audio
uint32_t write_smhd(byte *data);

//mdhd for audio and video files is the same
uint32_t write_dinf(byte *data, uint32_t video_audio);

//mdhd for audio and video files is the same
uint32_t write_dref(byte *data, uint32_t video_audio);

uint32_t write_stbl(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_stsd(byte *data, uint32_t video_audio, i2ctx *context);

//only video
uint32_t write_avc1(byte *data, i2ctx_video ctxVideo);

//only video
uint32_t write_avc3(byte *data, i2ctx_video ctxVideo);

//only video
uint32_t write_avcc(byte *data, i2ctx_video ctxVideo);

//only audio
uint32_t write_mp4a(byte *data, i2ctx_audio ctxAudio);

//only audio
uint32_t write_esds(byte *data, i2ctx_audio ctxAudio);

//stts for audio and video files is the same
uint32_t write_stts(byte *data, uint32_t video_audio, i2ctx *context);

//stsc for audio and video files is the same
uint32_t write_stsc(byte *data, uint32_t video_audio, i2ctx *context);

//stsz for audio and video files is the same
uint32_t write_stsz(byte *data, uint32_t video_audio, i2ctx *context);

//stco for audio and video files is the same
uint32_t write_stco(byte *data, uint32_t video_audio, i2ctx *context);

//styp for audio and video files is the same
uint32_t write_styp(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_sidx(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_moof(byte *data, uint32_t video_audio, i2ctx *context);

//mfhd for audio and video files is the same
uint32_t write_mfhd(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_traf(byte *data, uint32_t video_audio, i2ctx *context);

//tfhd for audio and video files is the same
uint32_t write_tfhd(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_tfdt(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_trun(byte *data, uint32_t video_audio, i2ctx *context);

uint32_t write_mdat(byte *data, uint32_t video_audio, i2ctx *context);

i2Err initVideoGenerator(byte *sps, byte *pps, i2ctx *context){}

i2Err initAudioGenerator(byte *aac_data, i2ctx *context){}
//TODO mirar que es lo que nos importa de aac

i2Err segmentGenerator(byte *data, uint32_t video_audio, i2ctx *context){}

uint32_t write_ftyp(byte *data, uint32_t video_audio, i2ctx *context) {
	uint32_t count, size, hton_size, flag, hton_flag, zero;
	//Size is always 20, apparently
	size = 24;
	count = 0;
	flag = 0x01;
	zero = 0;
	//Box size
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;
	//Box type
	memcpy(data + count, "vmhd", 4);
	count = count + 4;

    //Version and flags
	hton_flag = htonl(flag);
    memcpy(data + count, hton_flag, 4);
	count = count + 4;

    /* reserved (graphics mode=copy) */
    memcpy(data + count, zero, 4);
	count = count + 4;
	memcpy(data + count, zero, 4);
	count = count + 4;
	
	return count;
}

uint32_t write_moov(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_mvhd(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_mvex(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_trex(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_trak(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_tkhd(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_mdia(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_mdhd(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_hdlr(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_minf(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_vmhd(byte *data) {

	uint32_t count, size, hton_size, flag, hton_flag, zero;
	//Size is always 20, apparently
	size = 20;
	count = 0;
	flag = 0x01;
	zero = 0;
	//Box size
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;
	//Box type
	memcpy(data + count, "vmhd", 4);
	count = count + 4;

    //Version and flags
	hton_flag = htonl(flag);
    memcpy(data + count, hton_flag, 4);
	count = count + 4;

    /* reserved (graphics mode=copy) */
    memcpy(data + count, zero, 4);
	count = count + 4;
	memcpy(data + count, zero, 4);
	count = count + 4;
	
	return count;
}

uint32_t write_smhd(byte *data) {

}

uint32_t write_dinf(byte *data, uint32_t video_audio, i2ctx *context) {

}

//mdhd for audio and video files is the same
uint32_t write_dref(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_stbl(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_stsd(byte *data, uint32_t video_audio, i2ctx *context) {

}


uint32_t write_avc1(byte *data, i2ctx_video ctxVideo) {

}


uint32_t write_avc3(byte *data, i2ctx_video ctxVideo) {

}

uint32_t write_avcc(byte *data, i2ctx_video ctxVideo) {

}

uint32_t write_mp4a(byte *data, i2ctx_audio ctxAudio) {

}

uint32_t write_esds(byte *data, i2ctx_audio ctxAudio) {

}

uint32_t write_stts(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_stsc(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_stsz(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_stco(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_styp(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_sidx(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_moof(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_mfhd(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_traf(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_tfhd(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_tfdt(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_trun(byte *data, uint32_t video_audio, i2ctx *context) {

}

uint32_t write_mdat(byte *data, uint32_t video_audio, i2ctx *context) {

}

