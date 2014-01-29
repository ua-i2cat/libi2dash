#ifndef __CONTEXT__
#define __CONTEXT__

typedef unsigned char byte;

//CONTEXT
typedef struct {
	byte *sps;
	byte *pps;
	uint32_t width;
	uint32_t height;
	uint32_t frame_rate;
	uint32_t avc_profile;
	uint32_t avc_compat;
	uint32_t avc_level;


	

} i2ctx_video; //TODO

typedef struct {
	byte *aac_header;
	uint32_t channels;
	uint32_t sample_rate;
	uint32_t sample_size;
	uint32_t aac_profile;
	uint32_t data_rate;

} i2ctx_audio; //TODO

typedef struct {
	i2ctx_audio *ctxaudio;
	i2ctx_video *ctxvideo;
	int duration_ms; // Optimum duration
	int threshold_ms; // Segment duration threshold
	char *path;
} i2ctx; //TODO

typedef struct {
    uint32_t        size;
    uint32_t        duration;
    uint32_t        delay;
    uint32_t        timestamp;
    unsigned        key:1;
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
