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

//tkhd for audio and video files is the same
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

//dinf for audio and video files is the same
uint32_t write_dinf(byte *data, uint32_t media_type);

//dref for audio and video files is the same
uint32_t write_dref(byte *data, uint32_t media_type);

uint32_t write_url(byte * data);

uint32_t write_stbl(byte *data, uint32_t media_type, i2ctx *context);

uint32_t write_stsd(byte *data, uint32_t media_type, i2ctx *context);

//only video
uint32_t write_avc1(byte *data, i2ctx_video *ctxVideo);

//only video
uint32_t write_avc3(byte *data, i2ctx_video *ctxVideo);

//only video
uint32_t write_avcc(byte *data, i2ctx_video *ctxVideo);

//only audio
uint32_t write_mp4a(byte *data, i2ctx_audio *ctxAudio);

//only audio
uint32_t write_esds(byte *data, i2ctx_audio *ctxAudio);

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

uint32_t write_mdat(byte* source_data, uint32_t size_source_data, byte *data, uint32_t media_type, i2ctx *context);

uint32_t initVideoGenerator(byte *source_data, uint32_t size_source_data, byte *destination_data, i2ctx *context) {
	uint32_t count, size_ftyp, size_moov;
	
	count = 0;
	context->ctxvideo->pps_sps_data = (byte*) malloc(size_source_data);
	memcpy(context->ctxvideo->pps_sps_data, source_data, size_source_data);
	context->ctxvideo->pps_sps_data_length = size_source_data;
	size_ftyp = write_ftyp(destintation_data + count, VIDEO_TYPE, context);

	if (size_ftyp < 8)
		return I2ERROR;

	count = count + size_ftyp;
	size_moov = write_moov(destintation_data + count, VIDEO_TYPE, context);

	if (size_moov < 8)
		return I2ERROR;

	count = count + size_moov;

	return count;
}

uint32_t initAudioGenerator(byte *source_data, uint32_t size_source_data, byte *destination_data, i2ctx *context) {
	uint32_t count, size_ftyp, size_moov;
	
	count = 0;
	context->ctxaudio->aac_data = (byte*) malloc(size_source_data);
	memcpy(context->ctxaudio->aac_data, source_data, size_source_data);
	context->ctxaudio->aac_data_length = size_source_data;
	size_ftyp = write_ftyp(destintation_data + count, AUDIO_TYPE, context);
	
	if (size_ftyp < 8)
		return I2ERROR;

	count = count + size_ftyp;
	size_moov = write_moov(destintation_data + count, AUDIO_TYPE, context);

	if (size_moov < 8)
		return I2ERROR;

	count = count + size_moov;

	return count;
}

uint32_t segmentGenerator(byte *source_data, uint32_t size_source_data, byte *destination_data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size_styp, size_sidx, size_moof, size_mdat;

	//TODO AUDIOVIDEO_TYPE
	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;
	
	count = 0;
	size_styp = write_styp(destintation_data + count, media_type, context);
	
	if (size_ftyp < 8)
		return I2ERROR;

	count = count + size_styp;
	size_sidx = write_sidx(destintation_data + count, media_type, context);
	
	if (size_sidx < 8)
		return I2ERROR;

	count = count + size_sidx;
	size_moof = write_moof(destintation_data + count, media_type, context);

	if (size_moof < 8)
		return I2ERROR;

	count = count + size_moof;
	size_mdat = write_mdat(source_data , size_source_data, destintation_data + count, media_type, context);

	if (size_mdat < 8)
		return I2ERROR;

	count = count + size_mdat;

	return count;
}

uint32_t write_matrix(byte *data, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t tx, uint32_t ty);

uint32_t write_ftyp(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, version, hton_version, zero;
	
	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

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

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	
	//Box type
	memcpy(data + count, "moov", 4);
	count = count + 4;

    size_mvhd = write_mvhd(data + count, media_type, context);
	if (size_mvhd < 8)
		return I2ERROR;
	count = count + size_mvhd;
	size_mvex = write_mvex(data + count, media_type, context);
	if (size_mvex < 8)
		return I2ERROR;
	count = count + size_mvex;
	size_trak = write_trak(data + count, media_type, context);
	if (size_trak < 8)
		return I2ERROR;
	count = count + size_trak;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_mvhd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_matrix, flag32, hton_flag32;
	uint16_t flag16, hton_flag16;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;	
	//Box type
	memcpy(data + count, "mvhd", 4);
	count = count + 4;

	//Version
	flag32 = 0x0;
    memcpy(data + count, flag32, 4);
	count = count + 4;

    //Creation time
	flag32 = 0x0;
    memcpy(data + count, flag32, 4);
	count = count + 4;

    //Modification time
	flag32 = 0x0;
    memcpy(data + count, flag32, 4);
	count = count + 4;

    //Timescale
	flag32 = 1000;
	hton_flag32 = htonl(flag32);
    memcpy(data + count, flag32, 4);
	count = count + 4;

    //Duration
	flag32 = 0x0;
    memcpy(data + count, flag32, 4);
	count = count + 4;

    //Reserved
	flag32 = 0x00010000;
	hton_flag32 = htonl(flag32);
    memcpy(data + count, hton_flag32, 4);
	count = count + 4;
	flag16 = 0x0100;
	hton_flag16 = htons(flag16);
    memcpy(data + count, flag16, 2);
	count = count + 2;
	flag16 = 0;
    memcpy(data + count, flag16, 2);
	count = count + 2;
	flag32 = 0;
    memcpy(data + count, flag32, 4);
	count = count + 4;
    memcpy(data + count, flag32, 4);
	count = count + 4;
	
	//transformation matrix
    size_matrix = write_matrix(data, 1, 0, 0, 1, 0, 0);
	count = count + size_matrix;

    //Reserved
	flag32 = 0;
    memcpy(data + count, flag32, 4);
	count = count + 4;
    memcpy(data + count, flag32, 4);
	count = count + 4;
    memcpy(data + count, flag32, 4);
	count = count + 4;
    memcpy(data + count, flag32, 4);
	count = count + 4;
    memcpy(data + count, flag32, 4);
	count = count + 4;
    memcpy(data + count, flag32, 4);
	count = count + 4;

    //Next track id
	flag32 = 0x01;
	hton_flag32 = htonl(flag32);
    memcpy(data + count, flag32, 4);
	count = count + 4;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;

}

uint32_t write_mvex(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_trex;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	//Box type
	memcpy(data + count, "mvex", 4);
	count = count + 4;

	size_trex = write_trex(data + count, media_type, context);
	if (size_trex < 8)
		return I2ERROR;
	count = count + size_trex;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_trex(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, flag32, hton_flag32;
	
	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	//Size is always 32, apparently	
	//Box size
	size = 32; //0x20
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	count = count + 4;

	//Box type
	memcpy(data + count, "trex", 4);
	count = count + 4;

    //Version & flags
	flag32 = 0x0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Track id
	flag32 = 1;
	hton_flag32 = htonl(flag32);
	memcpy(data + count, hton_flag32, 4);
	count = count + 4;

    //Default sample description index
	flag32 = 1;
	hton_flag32 = htonl(flag32);
	memcpy(data + count, hton_flag32, 4);
	count = count + 4;

    //Default sample duration
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Default sample size, 1024 for AAC
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Default sample flags, key on
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	return count;
}

uint32_t write_trak(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_trex, size_mdia;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	//Box type
	memcpy(data + count, "trak", 4);
	count = count + 4;

	size_tkhd = write_tkhd(data + count, media_type, context);
	if (size_tkhd < 8)
		return I2ERROR;
	count = count + size_tkhd;
	size_mdia = write_mdia(data + count, media_type, context);
	if (size_mdia < 8)
		return I2ERROR;
	count = count + size_tkhd;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);

	return count;
}

uint32_t write_tkhd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_matrix, flag32, hton_flag32;
	uint16_t flag16, hton_flag16;
	uint8_t flag8;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;	
	//Box type
	memcpy(data + count, "tkhd", 4);
	count = count + 4;

    /* version */
	flag8 = 0;
	memcpy(data + count, flag8, 1);
	count = count + 1;

    //Flags: TrackEnabled
	flag8 = 0;
	memcpy(data + count, flag8, 1);
	count = count + 1;
	flag16 = 0x0000f;
	hton_flag16 = htons(flag16);
	memcpy(data + count, hton_flag16, 2);
	count = count + 2;

    //Creation time
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Modification time
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Track id
	flag32 = 1;
	flag32 = htonl(flag32);
	memcpy(data + count, hton_flag32, 4);
	count = count + 4;

    //Reserved
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Duration
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Reserved
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;
	memcpy(data + count, flag32, 4);
	count = count + 4;
	memcpy(data + count, flag32, 4);
	count = count + 4;

    //Reserved
	if (media_type == VIDEO_TYPE)
		flag16 = 0;
	else
		flag16 = 0x0100;
	hton_flag16 = htons(flag16);
	memcpy(data + count, hton_flag16, 2);
	count = count + 2;

    //Reserved
	flag16 = 0;
	memcpy(data + count, hton_flag16, 2);
	count = count + 2;

    size_matrix = write_matrix(data, 1, 0, 0, 1, 0, 0);
	count = count + size_matrix;

    if (media_type == VIDEO_TYPE) {
		flag32 = 0;
		flag32 = context->ctxvideo->width << 16;
		hton_flag32 = htonl(flag32);
		memcpy(data + count, hton_flag32, 4);
		count = count + 4;
		flag32 = 0;
		flag32 = context->ctxvideo->height << 16;
		hton_flag32 = htonl(flag32);
		memcpy(data + count, hton_flag32, 4);
		count = count + 4;	
    } else {
		flag32 = 0;
		memcpy(data + count, flag32, 4);
		count = count + 4;	
		memcpy(data + count, flag32, 4);
		count = count + 4;	
    }

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_mdia(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_mdhd, size_hdlr, size_minf;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	//Box type
	memcpy(data + count, "mdia", 4);
	count = count + 4;

	size_mdhd = write_mdhd(data + count, media_type, context);
	if (size_mdhd < 8)
		return I2ERROR;
	count = count + size_mdhd;
	size_hdlr = write_hdlr(data + count, media_type, context);
	if (size_hdlr < 8)
		return I2ERROR;
	count = count + size_hdlr;
	size_minf = write_minf(data + count, media_type, context);
	if (size_minf < 8)
		return I2ERROR;
	count = count + size_minf;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;

}

uint32_t write_mdhd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, flag32, hton_flag32;
	uint16_t flag16, hton_flag16;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	//Box type
	memcpy(data + count, "mdhd", 4);
	count = count + 4;

	//Version
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	//Creation time
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	//Modification time
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	//Time scale
	flag32 = 1000;
	hton_flag32 = htonl(flag32);
	memcpy(data + count, hton_flag32, 4);
	count = count + 4;

	//Duration
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	//Lanuguage
	flag16 = 0x15C7;
	hton_flag16 = htonl(flag16);
	memcpy(data + count, hton_flag16, 2);
	count = count + 2;

	//Reserved
	flag16 = 0;
	memcpy(data + count, flag16, 2);
	count = count + 2;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_hdlr(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, flag32, hton_flag32;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	//Box type
	memcpy(data + count, "hdlr", 4);
	count = count + 4;
	//Version and flags
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	//Pre defined
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	if (media_type == VIDEO_TYPE) {
		memcpy(data + count, "vide", 4);
		count = count + 4;
	} else {
		memcpy(data + count, "soun", 4);
		count = count + 4;
	}

	//Reserved
	flag32 = 0;
	memcpy(data + count, flag32, 4);
	count = count + 4;
	memcpy(data + count, flag32, 4);
	count = count + 4;
	memcpy(data + count, flag32, 4);
	count = count + 4;

	if (media_type == VIDEO_TYPE) {
		//Video handler string, NULL-terminated
		memcpy(data + count, "VideoHandler", sizeof("VideoHandler"));
		count = count + sizeof("VideoHandler");
    } else {
		//Sound handler string, NULL-terminated
		memcpy(data + count, "SoundHandler", sizeof("SoundHandler"));
		count = count + sizeof("SoundHandler");
	}

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_minf(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_vmhd, size_smhd, size_stbl, flag32, hton_flag32;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	//Box type
	memcpy(data + count, "minf", 4);
	count = count + 4;

	if (media_type == VIDEO_TYPE) {
		size_vmhd = write_vmhd(data + count, media_type, context);
		if (size_vmhd < 8)
			return I2ERROR;
		count = count + size_vmhd;
	} else {
		size_smhd = write_smhd(data + count, media_type, context);
		if (size_smhd < 8)
			return I2ERROR;
		count = count + size_smhd;
	}
	
	size_dinf = write_dinf(data + count, media_type, context);
	if (size_dinf < 8)
		return I2ERROR;
	count = count + size_dinf;
	size_stbl = write_stbl(data + count, media_type, context);
	if (size_stbl < 8)
		return I2ERROR;
	count = count + size_stbl;

	//Box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_vmhd(byte *data) {
	uint32_t count, size, hton_size, flag32, hton_flag32, zero;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	//Size is always 20, apparently
	size = 20;
	count = 0;
	flag32 = 0x01;
	zero = 0;
	//Box size
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;
	//Box type
	memcpy(data + count, "vmhd", 4);
	count = count + 4;

    //Version and flags
	hton_flag32 = htonl(flag32);
    memcpy(data + count, hton_flag32, 4);

	count = count + 4;

    //reserved (graphics mode=copy)
    memcpy(data + count, zero, 4);
	count = count + 4;
	memcpy(data + count, zero, 4);
	count = count + 4;
	
	return count;
}

uint32_t write_smhd(byte *data) {
	uint32_t count, size;
	uint64_t zero;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	// smhd size is always 16, apparently
	size = 16;
	count = 0;
	zero = 0;
	// Box size
	memcpy(data + count, htonl(size), 4);
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
	uint32_t count, size, hton_size, size_dref;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	memcpy(data + count, "dinf", 4);
	count = count + 4;
	size_dref = write_dref(data + count, media_type, context);
	if (size_dref < 8)
		return I2ERROR
	count = count + size_dref;

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

//dref for audio and video files is the same
uint32_t write_dref(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, zero, one, size_url;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	zero = 0;
	one = 1;

	// box type
	memcpy(data + count, "dref", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, htonl(one), 4);
	count = count + 4;
	size_url = write_url(data + count);
	if(size_url < 8)
		return I2ERROR;
	count = count + size_url;

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_url(byte * data) {
	uint32_t count, size, flags;

	count = 0;
	size = 0xc;
	flags = 0x00000001;
	// size
	memcpy(data + count, htonl(size), 4);
	count = count + 4;
	// box type
	memcpy(data + count, "url ", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, htonl(flags), 4);
	count = count + 4;

	return count;
}

uint32_t write_stbl(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, hton_size, size_stsd, size_stts, size_stsc, size_stsz, size_stco;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	
	// box type
	memcpy(data + count, "stbl", 4);
	count = count + 4;

	// write subBoxes and update count value
	size_stsd = write_stsd(data + count, media_type, context);
	if (size_stsd < 8)
		return I2ERROR
	count = count + size_stsd;
	
	size_stts = write_stts(data + count, media_type, context);	
	if (size_stts < 8)
		return I2ERROR
	count = count + size_stts;

	size_stsc = write_stsc(data + count, media_type, context);
	if (size_stsc < 8)
		return I2ERROR
	count = count + size_stsc;

	size_stsz = write_stsz(data + count, media_type, context);
	if (size_stsz < 8)
		return I2ERROR
	count = count + size_stsz;
	
	size_stco = write_stco(data + count, media_type, context);
	if (size_stco < 8)
		return I2ERROR
	count = count + size_stco;
	
	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_stsd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, one, size, hton_size, size_avc1, size_mp4a;
	i2ctx_audio *ctxaudio;
	i2ctx_video *ctxvideo;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	zero = 0;
	one = 1;
	ctxvideo = context->ctxvideo;
	ctxaudio = context->ctxaudio;

	// box type
	memcpy(data + count, "stsd", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	// entries
	memcpy(data + count, htonl(one), 4);
	count = count + 4;
	/*
	* media_type = 0 none
	* media_type = 1 video
	* media_type = 2 audio
	* media_type = 3 video_audio
	*/
	// write avcX or AAC boxes
	if(media_type == VIDEO_TYPE) {
		// write avc1
		size_avc1 = write_avc1(data + count, ctxvideo);
		if (size_avc1 < 8))
			return I2ERROR
		count = count + size_avc1;
	} else if(media_type == AUDIO_TYPE) {
		// write mp4a
		size_mp4a = write_mp4a(data + count, ctxaudio);
		if (size_mp4a < 8)
			return I2ERROR
		count = count + size_mp4a;
	} else {
		return I2ERROR;
	}

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}


uint32_t write_avc1(byte *data, i2ctx_video *ctxVideo) {
	uint32_t count, size, hton_size, zero_32, one, hv_resolution, avcc;
	uint64_t zero_64;
	uint16_t zero_16, width, height, flag_one, flag16;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	zero_16 = 0;
	zero_32 = 0;
	zero_64 = 0;
	one = 1;
	flag_one = 1;
	flag16 = 0;
	hv_resolution = 0x00480000;
	width = ctxVideo->width;
	height = ctxVideo->height;

	// box type
	memcpy(data + count, "avc1", 4);
	count + count + 4;
	// reserved
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	memcpy(data + count, zero_16, 2);
	count = count + 2;
	// data reference index
	memcpy(data + count, htons(flag_one), 2);
	count = count + 2;
	// codec stream version + revision + reserved
	memcpy(data + count, zero_64, 8);
	count = count + 8;
	memcpy(data + count, zero_64, 8);
	count = count + 8;
	// width
	memcpy(data + count, htons(width), 2);
	count = count + 2;
	// height
	memcpy(data + count, htons(height), 2);
	count = count + 2;
	// horitzonal and vertical resolution 72dpi
	memcpy(data + count, htonl(hv_resolution), 4);
	count = count + 4;
	memcpy(data + count, htonl(hv_resolution), 4); //2 veces???
	count = count + 4;
	// data size
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	// frame count
	memcpy(data + count, htons(flag_one), 2);
	count = count + 2;
	// compressor name
	memcpy(data + count, zero_64, 8);
	count = count + 8;
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	// reserved
	memcpy(data + count, zero_64, 8);
	count = count + 8;
	memcpy(data + count, zero_64, 8);
	count = count + 8;
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	flag16 = 0x18;
	memcpy(data + count, htons(flag16), 2);
	count = count + 2;
	flag16 = 0xffff;
	memcpy(data + count, htons(flag16), 2);
	count = count + 2;
	// write avcC
	size_avcc = write_avcc(data + count, ctxVideo);
	if (size_avcc < 8)
		return I2ERROR
	count = count + size_avcc;
	
	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_avc3(byte *data, i2ctx_video *ctxVideo) {
	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;
	// TODO
}

uint32_t write_avcc(byte *data, i2ctx_video *ctxVideo) {
	uint32_t count, zero, size, hton_size;
	
	count = 0;
	zero = 0;

	size = i2ctx_video->pps_sps_data_length + 8;
	hton_size = htonl(size);
	// box size
	memcpy(data + count, hton_size, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "avcC", 4);
	count = count + 4;
	// avc header, includes version, profile, level, sps and pps
	memcpy(data + count, i2ctx_video->pps_sps_data, i2ctx_video->pps_sps_data_length);
	
	count = count + i2ctx_video->pps_sps_data_length;

	return count;
}

uint32_t write_mp4a(byte *data, i2ctx_audio *ctxAudio) {
	uint32_t count, zero_32, size_esds, size, hton_size;
	uint16_t zero_16, audio_channels, sample_size, sample_rate;
	uint64_t zero_64;

	count = 4;
	zero_16 = 0;
	zero_32 = 0;
	zero_64 = 0;
	audio_channels = ctxAudio->channels;
	sample_size = ctxAudio->sample_size;
	sample_rate = ctxAudio->sample_rate;

	// box type
	memcpy(data + count, "mp4a", 4);
	count = count + 4;
	// reserved
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	memcpy(data + count, zero_16, 2);
	count = count + 2;
	// channel count
	memcpy(data + count, htons(audio_channels), 2);
	count = count + 2;
	// sample size
	memcpy(data + count, htons((sample_size) * 8), 2);
	count = count + 2;
	// reserved
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	// timescale
	memcpy(data + count, htons(1000), 2);
	count = count + 2;
	// sample rate
	memcpy(data + count, htons(sample_rate), 2);
	count = count + 2;
	// write esds
	size_esds = write_esds(data + count, ctxAudio);
	if (size_esds < 8)
		return I2ERROR
	count = count + size_esds;

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_esds(byte *data, i2ctx_audio *ctxAudio) {
	uint32_t count, zero_32;
	uint16_t one, zero_16;
	uint8_t zero_8;
	byte *descriptor;

	count = 0;
	zero_32 = 0;
	zero_16 = 0;
	zero_8 = 0;
	one = 1;
	//size
	memcpy(data + count, zero, 4);
	count = count + 4;
	// box type
	memcpy(data + count, "esds", 4);
	count = count + 4;
	// box version
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	



/*
	static ngx_int_t
	ngx_rtmp_mp4_put_descr(ngx_buf_t *b, int tag, size_t size)
	{
	    ngx_rtmp_mp4_field_8(b, (uint8_t) tag);
	    ngx_rtmp_mp4_field_8(b, size & 0x7F);

	    return NGX_OK;
	}
*/




}

uint32_t write_stts(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	//Size is always 16, apparently
	size = 16;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
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
	uint32_t count, zero, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	//Size is always 16, apparently
	size = 16;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
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
	uint32_t count, zero, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	//Size is always 20, apparently
	size = 20;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
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
	uint32_t count, zero, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	//Size is always 16, apparently
	size = 16;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
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
	uint32_t count, zero, version, hton_version, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	version = 1;
	//Size is always 28, apparently
	size = 28;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;

	// box type
	memcpy(data + count, "styp", 4);
	count = count + 4;

	// major brand
	memcpy(data + count, "iso6", 4);
	count = count + 4;

    //Version
	hton_version = htonl(version);
    memcpy(data + count, hton_version, 4);
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
	uint32_t count, zero_32, duration_ms, decode_time_ms, one_32, reference_size, subseg_duration_ms, size, hton_size;
	uint8_t zero_8;
	uint16_t zero_16, one_16;
	byte flag8;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	zero_8 = 0;
	zero_16 = 0;
	zero_32 = 0;
	one_16 = 1;
	one_32 = 1;
	subseg_duration_ms = context->i2ctx_sample.duration_ms;
	decode_time_ms = context->i2ctx_sample.decode_time_ms;
	reference_size = context.reference_size;
	duration_ms = context.duration_ms;

	// box type
	memcpy(data + count, "sidx", 4);
	count = count + 4;
	// version
	memcpy(data + count, zero_32, 4);
	count = count + 4;
	// reference id
	memcpy(data + count, one_32, 4);
	count = count + 4;
	// timescale
	memcpy(data + count, htonl(1000), 4);
	count = count + 4;
	// decode time
	memcpy(data + count, htonl(decode_time_ms), 4);
	count = count + 4;
	// duration
	memcpy(data + count, htonl(duration_ms), 4);
	count = count + 4;
	// reserved
	memcpy(data + count, zero_16, 2);
	count = count + 2;	
	// reference count = 1
	memcpy(data + count, htons(one_16), 2);
	count = count + 2;
	// reference size
	memcpy(data + count, htonl(reference_size), 4);
	count = count + 4;
	// subsegment_duration 
	memcpy(data + count, htonl(subseg_duration_ms), 4);
	count = count + 4;
	// 1st bit is reference type, the rest is reference size
	flag8 = 0x90;
	memcpy(data + count, flag8, 1);
	count = count + 1;
	// SAP delta time
	memcpy(data + count, zero_16, 2);
	count = count + 2;
	memcpy(data + count, zero_8, 1);
	count = count + 1;

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_moof(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, size, hton_size, size_traf, size_mfhd;
	i2ctx_sample *samples; 

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	zero = 0;
	
	if(media_type == VIDEO_TYPE) {
		samples = context->ctxvideo->ctxsample;
	} else if (media_type == AUDIO_TYPE) {
		samples = context->ctxaudio->ctxsample;
	} else {
		return I2ERROR;
	}

	// box type
	memcpy(data + count, "moof", 4);
	count = count + 4;
	samples->moof_pos = count;

	// write mfhd
	size_mfhd = write_mfhd(data + count, media_type, context);
	if (size_mfhd < 8)
		return I2ERROR

	count = count +size_ mfhd;
	// write traf
	size_traf = write_traf(data + count, media_type, context);
	if (size_traf < 8)
		return I2ERROR

	count = count + size_traf;

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_mfhd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, seqnum, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	seqnum = context->ctxsample.index;

	//Size is always 16, apparently
	size = 16;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;

	// box type
	memcpy(data + count, "mfhd", 4);
	count = count + 4;
	// version and flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	// sequence number
	memcpy(data + count, htonl(seqnum), 4);
	count = count + 4;

	return count;
}

uint32_t write_traf(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t zero, count, size_tfhd, size_tfdt, size_trun, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;

	// box type
	memcpy(data + count, "traf", 4);
	count = count + 4;
	
	// write tfhd
	size_tfhd = write_tfhd(data + count, media_type, context);
	if (size_tfhd < 8)
		return I2ERROR
	count = count + size_tfhd;
	
	// write tfdt
	size_tfdt = write_tfdt(data + count, media_type, context);
	if (size_tfdt < 8)
		return I2ERROR
	count = count + size_tfdt;
	
	// write trun
	size_trun = write_trun(data + count, media_type, context);
	if (size_trun < 8)
		return I2ERROR
	count = count + size_trun;

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_tfhd(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, size, zero, one, flags, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	one = 1;
	flags = 0x0002000;
	//Size is always 16, apparently
	size = 16;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;

	// box type
	memcpy(data + count, "tfhd", 4);
	count = count + 4;

	// version and flags
	memcpy(data + count, htonl(flags), 4);
	count = count + 4;

	// track id
	memcpy(data + count, htonl(one), 4);
	count = count + 4;

	return count;
}

uint32_t write_tfdt(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, decode_time_ms, size, hton_size;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	zero = 0;
	decode_time_ms = context->i2ctx_sample.decode_time_ms;
	//Size is always 16, apparently
	size = 16;
	hton_size = htonl(size);
	memcpy(data + count, hton_size, 4);
	count = count + 4;

	// box type
	memcpy(data + count, "tfdt", 4);
	count = count + 4;
	
	// flags
	memcpy(data + count, zero, 4);
	count = count + 4;
	
	// decode time
	memcpy(data + count, htonl(decode_time_ms), 4);
	count = count + 4;

	return count;
}

uint32_t write_trun(byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, zero, nitems, flags, sample_size, sample_duration;
	uint32_t sample_delay, sample_num, offset, moof_pos, size, hton_size;
	
	i2ctx_sample *samples;
	unsigned sample_key;
	int i  = 0;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 4;
	zero = 0;
	nitems = 0;

	if(media_type == VIDEO_TYPE) {
		samples = context->ctxvideo->ctxsample;
		nitems = 4;
	} else if (media_type == AUDIO_TYPE) {
		samples = context->ctxaudio->ctxsample;
		nitems = 2;
	} else {
		return I2ERROR;
	}

	flags = samples->box_flags;
	sample_num = samples->mdat_length;
	moof_pos = samples->moof_pos;


	// box type
	memcpy(data + count, "trun", 4);
	count = count + 4;
	offset = (count - moof_pos) + 20 + (sample_num * nitems * 4) + 8;

	// flags
	memcpy(data + count, htonl(flags), 4);
	count = count + 4;

	// sample count
	memcpy(data + count, htonl(sample_num), 4);
	count = count + 4;

	// offset
	memcpy(data + count, htonl(offset), 4);
	count = count + 4;
	samples->moof_pos = 0;

	for (i = 0; i < sample_count; i++)
	{
		// sample duration
		memcpy(data + count, htonl(samples->mdat[i].duration_ms), 4);
		count = count + 4;
		// sample size
		memcpy(data + count, htonl(samples->mdat[i].size), 4);
		count = count + 4;
		// video exclusive
		if(media_type == VIDEO_TYPE) {
			// sample flags
			memcpy(data + count, htonl(samples->mdat[i].key ? 0x00000000 : 0x00010000), 4);
			count = count + 4;
			// sample composition time offsets
			memcpy(data + count, htonl(samples->mdat[i].delay), 4);
			count = count + 4;
		}
	}

	// box size
	size = count;
	hton_size = htonl(size);
	memcpy(data, hton_size, 4);
	return count;
}

uint32_t write_mdat(byte* source_data, uint32_t size_source_data, byte *data, uint32_t media_type, i2ctx *context) {
	uint32_t count, mdat_size;
	i2ctx_sample *samples;

	if ((media_type == NO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		return I2ERROR;

	count = 0;
	mdat_size = size_source_data + 8;
	memcpy(data + count, htonl(mdat_size), 4);
	count = count + 4;
	memcpy(data + count, "mdat", 4);
	count = count + 4;
	memcpy(data + count, source_data, size_source_data);
	count = count + size_source_data;

	return count;
}

uint32_t write_matrix(byte *data, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t tx, uint32_t ty) {
	uint32_t count, value, hton_value;
	count = 0;
	value = 0x0;

	// transformation matrix
	// |a  b  u|
	// |c  d  v|
	// |tx ty w|

	//a in 16.16 format
	value = a << 16;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;
	//b in 16.16 format
	value = b << 16;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;
	//u in 2.30 format
	value = 0
	memcpy(data + count, value, 4);
	count = count + 4;
	//c in 16.16 format
	value = c << 16;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;
	//d in 16.16 format
	value = d << 16;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;
	//v in 2.30 format
	value = 0
	memcpy(data + count, value, 4);
	count = count + 4;
	//tx in 16.16 format
	value = tx << 16;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;
	//ty in 16.16 format
	value = ty << 16;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;
	//w in 2.30 format
	value = 1;
	hton_value = htonl(value);
	memcpy(data + count, hton_value, 4);
	count = count + 4;

    return count;
}
