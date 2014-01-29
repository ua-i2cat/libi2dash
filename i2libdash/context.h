#ifndef __ISOFF_LIB__
#define __CONTEXT__

//CONTEXT
typedef struct {
	u_char *sps;
	u_char *pps;
	u_int width;
	u_int height;
	u_int frame_rate;
	u_int avc_profile;
	u_int avc_compat;
	u_int avc_level;


	

} i2ctx_video; //TODO

typedef struct {
	u_char *aac_header;
	u_int channels;
	u_int sample_rate;
	u_int sample_size;
	u_int aac_profile;
	u_int data_rate;

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