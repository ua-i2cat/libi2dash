//CONTEXT
typedef struct {
	u_char *sps;
	u_char *pps;

} i2ctx_video; //TODO

typedef struct {
	u_char *aac_data;

} i2ctx_audio; //TODO

typedef struct {
	i2ctx_audio *ctxaudio;
	i2ctx_video *ctxvideo;
	int duration_ms; // Optimum duration
	int threshold_ms; // Segment duration threshold
	char *path;
} i2ctx; //TODO

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

//LIBRERIA DASH

i2Err addData(char *buffer_in, int duration, i2ctx *context);





