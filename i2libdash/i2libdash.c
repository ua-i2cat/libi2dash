#include "i2libdash.h"

// PRIVATE FUNCTIONS DECLARATION

void audio_context_initializer(i2ctx **context);

void audio_sample_context_initializer(i2ctx_audio **ctxAudio);

void video_context_initializer(i2ctx **context);

void video_sample_context_initializer(i2ctx_video **ctxVideo);

uint8_t get_width_height(byte *nal_sps, uint32_t *size_nal_sps, i2ctx_video **ctxVideo);

uint8_t is_key_frame(byte *input_data, uint32_t size_input);

// IMPLEMENTATION

void set_segment_duration(uint32_t segment_duration, i2ctx **context){
	(*context)->duration_ms = segment_duration;
}

uint32_t get_segment_duration(i2ctx *context){
	return context->duration_ms;
}

void set_frame_rate(uint32_t frame_rate, i2ctx_video **ctxVideo){
	(*ctxVideo)->frame_rate = frame_rate;
}

uint32_t get_frame_rate(i2ctx_video *ctxVideo){
	return ctxVideo->frame_rate;
}

void set_sample_rate(uint32_t sample_rate, i2ctx_audio **ctxAudio){
	(*ctxAudio)->sample_rate = sample_rate;
}

uint32_t get_sample_rate(i2ctx_audio *ctxAudio){
	return ctxAudio->sample_rate;
}

void audio_context_initializer(i2ctx **context) {
	(*context)->ctxaudio = (i2ctx_audio *) malloc(sizeof(i2ctx_audio));
	i2ctx_audio *ctxAudio = (*context)->ctxaudio;

	ctxAudio->aac_data_length = 0;
	ctxAudio->segment_size = 0;
	ctxAudio->channels = 2;
	ctxAudio->sample_rate = 44100;
	ctxAudio->sample_size = 16;
	ctxAudio->sequence_number = 0;
	ctxAudio->earliest_presentation_time = 0;
	ctxAudio->latest_presentation_time = 0;

	audio_sample_context_initializer(&ctxAudio);
}

void audio_sample_context_initializer(i2ctx_audio **ctxAudio) {
	(*ctxAudio)->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));
	i2ctx_sample *ctxASample = (*ctxAudio)->ctxsample;

	ctxASample->box_flags = 0;
	ctxASample->mdat_sample_length = 0;
	ctxASample->mdat_total_size = 0;
	ctxASample->moof_pos = 0;
}

void video_context_initializer(i2ctx **context) {
	(*context)->ctxvideo = (i2ctx_video *) malloc(sizeof(i2ctx_video));
	i2ctx_video *ctxVideo = (*context)->ctxvideo;

	ctxVideo->pps_sps_data_length = 0;
	ctxVideo->segment_size = 0;
	ctxVideo->width = 0;
	ctxVideo->height = 0;
	ctxVideo->frame_rate = 25;
	ctxVideo->earliest_presentation_time = 0;
	ctxVideo->latest_presentation_time = 0;
	ctxVideo->sequence_number = 0;

	video_sample_context_initializer(&ctxVideo);
}

void video_sample_context_initializer(i2ctx_video **ctxVideo) {
	(*ctxVideo)->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));	
	i2ctx_sample *ctxVSample = (*ctxVideo)->ctxsample;

	ctxVSample->box_flags = 0;
	ctxVSample->mdat_sample_length = 0;
	ctxVSample->mdat_total_size = 0;
	ctxVSample->moof_pos = 0;
}

void context_initializer(i2ctx **context){
	*context = (i2ctx *) malloc(sizeof(i2ctx));

	(*context)->duration_ms = 5;
	(*context)->reference_size = 0;

	audio_context_initializer(context);
	video_context_initializer(context);

	// Threshold: 1/fps * 2
	(*context)->threshold_ms = 2/((double)((*context)->ctxvideo->frame_rate)); 
}

uint8_t get_width_height(byte *nal_sps, uint32_t *size_nal_sps, i2ctx_video **ctxVideo) {

	uint32_t width, height;
    sps_t* sps = (sps_t*)malloc(sizeof(sps_t));
    uint8_t* rbsp_buf = (uint8_t*)malloc(*size_nal_sps);
    if (nal_to_rbsp(nal_sps, (int*)size_nal_sps, rbsp_buf, (int*)size_nal_sps) < 0){
        free(rbsp_buf);
        free(sps);
        return I2ERROR;
    }
    bs_t* b = bs_new(rbsp_buf, *size_nal_sps);
    if(read_seq_parameter_set_rbsp(sps,b) < 0){
        bs_free(b);
        free(rbsp_buf);
        free(sps);
        return I2ERROR;
    }
    width = (sps->pic_width_in_mbs_minus1 + 1) * 16;
    height = (2 - sps->frame_mbs_only_flag) * (sps->pic_height_in_map_units_minus1 + 1) * 16;

    if (sps->frame_cropping_flag){
        width -= (sps->frame_crop_left_offset*2 + sps->frame_crop_right_offset*2);
        height -= (sps->frame_crop_top_offset*2 + sps->frame_crop_bottom_offset*2);
    }

    (*ctxVideo)->width = width;
    (*ctxVideo)->height = height;

    bs_free(b);
    free(rbsp_buf);
    free(sps);

    return 0;
}

uint32_t init_video_handler(byte *metadata, uint32_t metadata_size, byte *metadata2, uint32_t metadata2_size, byte *sps_data, uint32_t sps_size, byte *metadata3, uint32_t metadata3_size, byte *pps_data, uint32_t pps_size, byte *output_data, i2ctx *context) {

	uint32_t initVideo, count, sps_pps_data_length;
	uint16_t hton_sps_size, hton_pps_size;
	byte *sps_pps_data;

	count = 0;

	sps_pps_data = (byte *) malloc (sizeof(byte));

	// Metadata
	memcpy(sps_pps_data + count, metadata, metadata_size);
	count = count + metadata_size;
	// Metadata2
	memcpy(sps_pps_data + count, metadata2, metadata2_size);
	count = count + metadata2_size;
	// Size SPS
	hton_sps_size = htons(sps_size);
	memcpy(sps_pps_data + count, &hton_sps_size, 2);
	count = count + 2;
	// SPS
	memcpy(sps_pps_data + count, sps_data, sps_size);
	count = count + pps_size;
	// Metadata3
	memcpy(sps_pps_data + count, metadata3, metadata3_size);
	count = count + metadata3_size;
	// Size PPS
	hton_pps_size = htons(pps_size);
	memcpy(sps_pps_data + count, &hton_pps_size, 2);
	count = count + 2;
	// PPS
	memcpy(sps_pps_data + count, pps_data, pps_size);
	count = count + sps_size;

	sps_pps_data_length = count;

	if(get_width_height(sps_data, &sps_size, &(context->ctxvideo)) == I2ERROR)
		return I2ERROR;

	initVideo = initVideoGenerator(sps_pps_data, sps_pps_data_length, output_data, context);

	return initVideo;

}

