#include "i2libisoff.h"

//ftyp for audio and video files is the same
uint32_t write_ftyp(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_moov(byte *data, uint32_t media_type, i2ctx *context);

//mvhd for audio and video files is the same
uint32_t write_mvhd(byte *data, uint32_t media_type, i2ctx *context);

//mvex for audio and video files is the same
uint32_t write_mvex(byte *data, uint32_t media_type, i2ctx *context);

//trex for audio and video files is the same
uint32_t write_trex(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_trak(byte *data, uint32_t media_type, i2ctx *context);

//trex for audio and video files is the same
uint32_t write_tkhd(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_mdia(byte *data, uint32_t media_type, i2ctx *context);

//mdhd for audio and video files is the same
uint32_t write_mdhd(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_hdlr(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_minf(byte *data, uint32_t media_type, i2ctx *context);

//only video
uint32_t write_vmhd(byte *data);

//only audio
uint32_t write_smhd(byte *data);

//mdhd for audio and video files is the same
uint32_t write_dinf(byte *data, uint32_t media_type);

//mdhd for audio and video files is the same
uint32_t write_dref(byte *data, uint32_t media_type);

uint32_t write_url(byte * data);

uint32_t write_stbl(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_stsd(byte *data, uint32_t media_type, i2ctx *context);

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
uint32_t write_stts(byte *data, uint32_t media_type, i2ctx *context);

//stsc for audio and video files is the same
uint32_t write_stsc(byte *data, uint32_t media_type, i2ctx *context);

//stsz for audio and video files is the same
uint32_t write_stsz(byte *data, uint32_t media_type, i2ctx *context);

//stco for audio and video files is the same
uint32_t write_stco(byte *data, uint32_t media_type, i2ctx *context);

//styp for audio and video files is the same
uint32_t write_styp(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_sidx(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_moof(byte *data, uint32_t media_type, i2ctx *context);

//mfhd for audio and video files is the same
uint32_t write_mfhd(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_traf(byte *data, uint32_t media_type, i2ctx *context);

//tfhd for audio and video files is the same
uint32_t write_tfhd(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_tfdt(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_trun(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_mdat(byte *data, uint32_t media_type, i2ctx *context);

i2Err initVideoGenerator(byte *sps, byte *pps, i2ctx *context){}

i2Err initAudioGenerator(byte *aac_data, i2ctx *context){}
//TODO mirar que es lo que nos importa de aac

i2Err segmentGenerator(byte *data, uint32_t media_type, i2ctx *context){}

uint32_t write_ftyp(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, version, hton_version, zero;

	count = 4;
	version = 1;
	zero = 0;
	
	//Box type
	memcpy(data + count, "ftyp", 4);
	count = count + 4;

	//Major brand
    memcpy(data + count, "iso6", 4);
	count = count + 4;

    //Version
	hton_version = htonl(version);
    memcpy(data + count, hton_version, 4);
	count = count + 4;

    //Compatible brands
    memcpy(data + count, "isom", 4);
	count = count + 4;
    memcpy(data + count, "iso6", 4);
	count = count + 4;
    memcpy(data + count, "dash", 4);
	count = count + 4;
	
	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_moov(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, size_mvhd, size_mvex, size_trak, hton_size;
	count = 4;
	
	//Box type
	memcpy(data + count, "moov", 4);
	count = count + 4;

    size_mvhd = write_mvhd(data + count, media_type, context);
	count = count + size_mvhd;
	size_mvex = write_mvex(data + count, media_type, context);
	count = count + size_mvex;
	size_trak = write_trak(data + count, media_type, context);
	count = count + size_trak;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;


}

uint32_t write_mvhd(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_mvex(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_trex(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_trak(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_tkhd(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_mdia(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_mdhd(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_hdlr(byte *data, uint32_t media_type, i2ctx *context) {

}

uint32_t write_minf(byte *data, uint32_t media_type, i2ctx *context) {

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
	uint32_t count, size, hton_size;
	uint64_t zero;
	// smhd size is always 16, apparently
	size = 16;
	count = 0;
	zero = 0;
	// Box size
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;
	// Box type
	memcpy(data + count, "smhd", 4);
	count = count + 4;
	// Version and flags and reserved (balance normally = 0)
	memcpy(data + count, zero, 8);
	count = count + 8;

	return count;
}

uint32_t write_dinf(byte *data, uint32_t media_type, i2ctx *context) {
}

//mdhd for audio and video files is the same
uint32_t write_dref(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, one, url_size;
	count = 0;
	zero = 0;
	one = 1;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "dref", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, one, 4);
	count = count + 4;
	// TODO call url box generation + implementation

	return count;
}

uint32_t write_url(byte * data) {
	uint32_t count, size, version_flags;
	// I think that url_size don't need hton
	count = 0;
	size = 0xc;
	flags = 0x00000001;
	// TODO check this call
	// size
	memcpy(data + count, size, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "url ", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, flags);
	count = count + 4;

	return count;
}

uint32_t write_stbl(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, stsd, stts, stsc, stsz, stco;
	count = 0;
	
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "stbl", 4);
	count = count + 4;

	// write subBoxes and update count value
	stsd = write_stsd(data + count, media_type, context);
	if !(stsd > 0 && stsd != I2ERROR)
		return I2ERROR
	count = count + stsd;
	
	stts = write_stts(data + count, media_type, context);	
	if(stts > 0 && stts != I2ERROR)
		return I2ERROR
	count = count + stts;

	stsc = write_stsc(data + count, media_type, context);
	if(stsc > 0 && stsc != I2ERROR)
		return I2ERROR
	count = count + stsc;

	stsz = write_stsz(data + count, media_type, context);
	if(stsz > 0 && stsz != I2ERROR)
		return I2ERROR
	count = count + stsz;
	
	stco = write_stco(data + count, media_type, context);
	if(stco > 0 && stco != I2ERROR)
		return I2ERROR
	count = count + stco;
	
	return count;
}

uint32_t write_stsd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, one;
	count = 0;
	zero = 0;
	one = 1;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "stsd", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, one, 4);
	count = count + 4;
	/*
	* media_type = 0 none
	* media_type = 1 video
	* media_type = 2 audio
	* media_type = 3 video_audio
	*/
	// write avcX or AAC boxes
	if(media_type == 1) {
		// TODO call write_avc1 or write_avc3...
	} else if(media_type == 2) {
		// TODO call write_aac
	} else if(media_type == 3) {
		// TODO Handle video+audio case
	} else {
		return I2ERR;
	}

	return count;
}


uint32_t write_avc1(byte *data, i2ctx_video ctxVideo) {
	// TODO
}


uint32_t write_avc3(byte *data, i2ctx_video ctxVideo) {
	// TODO
}

uint32_t write_avcc(byte *data, i2ctx_video ctxVideo) {

}

uint32_t write_mp4a(byte *data, i2ctx_audio ctxAudio) {
	// TODO
}

uint32_t write_esds(byte *data, i2ctx_audio ctxAudio) {
	// TODO
}

uint32_t write_stts(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero;
	count = 0;
	zero = 0;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "stts", 4);
	count = count + 4;
	// version
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, zero, 4);
	count = count + 4;

	return count;
}

uint32_t write_stsc(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero;
	count = 0;
	zero = 0;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "stsc", 4);
	count = count + 4;
	// version
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, zero, 4);
	count = count + 4;

	return count;
}

uint32_t write_stsz(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero;
	count = 0;
	zero = 0;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// Box type
	memcpy(data + count, "stsz", 4);
	count = count + 4;
	// Version
	memcpy(data + count, zero, 4);
	count = count + 4;
	// Flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	// Entries
	memcpy(data + count, zero, 4);
	count = count + 4;

	return count;
}

uint32_t write_stco(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero;
	count = 0;
	zero = 0;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "stco", 4);
	count = count + 4;
	// version
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, zero, 4);
	count = count + 4;

	return count;
}

uint32_t write_styp(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero;
	count = 0;
	zero = 0;
	// size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "styp", 4);
	count = count + 4;
	// major brand
	memcpy(data + count, "iso6", 4);
	count = count + 4;
	// compatible brands
	memcpy(data + count, "isom", 4);
	count = count + 4;
	memcpy(data + count, "iso6", 4);
	count = count + 4;
	memcpy(data + count, "dash", 4);
	count = count + 4;

	return count;
}

uint32_t write_sidx(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_moof(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_mfhd(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_traf(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_tfhd(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_tfdt(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_trun(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

uint32_t write_mdat(byte *data, uint32_t media_type, i2ctx *context) {
	// TODO
}

