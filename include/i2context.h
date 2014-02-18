#ifndef __CONTEXT__
#define __CONTEXT__

typedef unsigned char byte;
#define NO_TYPE 0
#define VIDEO_TYPE 1
#define AUDIO_TYPE 2
#define AUDIOVIDEO_TYPE 3
#define MAX_MDAT_SAMPLE 65536
#define MAX_DAT 10*1024*1024
#define I2OK	2
#define I2ERROR 1
#define TRUE	1
#define	FALSE	0

#include <netinet/in.h>

typedef struct {
    uint32_t        size; // sample_size
    uint32_t        duration_ms; // sample_duration
    uint32_t        delay; // sample_delay
    uint32_t        timestamp;
    unsigned        key:1; // sample_key_frame
    uint32_t		index;
    uint32_t		decode_time_ms;
} mdat_sample;

typedef struct {
	uint32_t		box_flags;
	mdat_sample 	mdat[MAX_MDAT_SAMPLE];
	uint32_t		mdat_sample_length;
	uint32_t		mdat_total_size;
	uint32_t		moof_pos; // setted in write_moof, used in write_trun
} i2ctx_sample;

//CONTEXT
typedef struct {
	byte			*pps_sps_data;
	uint32_t 		pps_sps_data_length;
	byte			segment_data[MAX_DAT];
	uint32_t		segment_data_size;
	uint16_t		width;
	uint16_t		height;
	uint32_t		frame_rate;
	uint32_t		earliest_presentation_time;
	uint32_t		latest_presentation_time;
	uint32_t		sequence_number;
	uint32_t		current_video_duration_ms; // Current sample duration, increases by sample duration
	i2ctx_sample	*ctxsample;
} i2ctx_video;

typedef struct {
	byte			*aac_data;
	uint32_t		aac_data_length;
	byte			segment_data[MAX_DAT];
	uint32_t		segment_data_size;
	uint16_t		channels;
	uint16_t		sample_rate;
	uint16_t		sample_size; // bits quantizer
	uint32_t		earliest_presentation_time; // en dash_append si el sample count == 0 --> timestamp. sino es 0.
	uint32_t		latest_presentation_time; // Se refresca en cada dash_append con el timestamp.
	uint32_t		sequence_number; // Actualiza con cada segmento en el close_fragments
	uint32_t		current_audio_duration_ms; // Current segment duration, increases by sample duration
	i2ctx_sample 	*ctxsample;
} i2ctx_audio;

typedef struct {
	i2ctx_audio		*ctxaudio;
	i2ctx_video		*ctxvideo;
	uint32_t		duration_ms; // Optimum duration
	double			threshold_ms; // Segment duration threshold
	uint32_t		reference_size; // Se calcula en close fragments en llamada a sidx
	uint8_t			audio_segment_flag;
} i2ctx;

 /* assume config fits one chunk (highly probable) */

    /*
     * Skip:
     * - flv fmt
     * - H264 CONF/PICT (0x00)
     * - 0
     * - 0
     * - 0
     */

#endif
