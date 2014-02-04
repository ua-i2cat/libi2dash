#ifndef __CONTEXT__
#define __CONTEXT__

typedef unsigned char byte;
#define NO_TYPE 0
#define VIDEO_TYPE 1
#define AUDIO_TYPE 2
#define AUDIOVIDEO_TYPE 3

//CONTEXT
typedef struct {
	u_char *avc_header;
	uint16_t width;
	uint16_t height;
	uint32_t frame_rate;
	uint32_t avc_version;
	uint32_t avc_profile;
	uint32_t avc_compat;
	uint32_t avc_level;
} i2ctx_video; //TODO

typedef struct {
	byte *aac_header;
	uint16_t channels;
	uint16_t sample_rate;
	uint16_t sample_size;
	uint32_t aac_profile;
	uint32_t data_rate;
} i2ctx_audio; //TODO

typedef struct {
	i2ctx_audio *ctxaudio;
	i2ctx_video *ctxvideo;
	i2ctx_sample *ctxsample;
	uint32_t duration_ms; // Optimum duration
	int threshold_ms; // Segment duration threshold
	char *path;
	uint32_t reference_size;
} i2ctx; //TODO

typedef struct {
    uint32_t        size; // sample_size
    uint32_t        duration_ms; // sample_duration
    uint32_t        delay; // sample_delay
    uint32_t        timestamp;
    unsigned        key:1; // sample_key_frame
    uint32_t		index;
    uint32_t 		decode_time_ms;
    uint32_t		mdat_size;
    uint32_t		moof_pos;
    uint32_t		sample_count; // number of samples per segment
} i2ctx_sample;

 /* assume config fits one chunk (highly probable) */

    /*
     * Skip:
     * - flv fmt
     * - H264 CONF/PICT (0x00)
     * - 0
     * - 0
     * - 0
     */

i2Err createContext(i2ctx *context); //TODO

#endif
