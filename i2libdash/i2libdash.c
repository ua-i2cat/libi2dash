#include "i2libdash.h"

// PRIVATE FUNCTIONS DECLARATION
// Función que actualiza el context cada vez que se genera un segmento
void context_refresh(i2ctx **context, uint32_t media_type);

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
	ctxAudio->segment_data_size = 0;
	ctxAudio->channels = 2;
	ctxAudio->sample_rate = 44100;
	ctxAudio->sample_size = 16;
	ctxAudio->sequence_number = 0;
	ctxAudio->earliest_presentation_time = 0;
	ctxAudio->latest_presentation_time = 0;
	ctxAudio->current_audio_duration_ms = 0;

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
	ctxVideo->segment_data_size = 0;
	ctxVideo->width = 0;
	ctxVideo->height = 0;
	ctxVideo->frame_rate = 25;
	ctxVideo->earliest_presentation_time = 0;
	ctxVideo->latest_presentation_time = 0;
	ctxVideo->sequence_number = 0;
	ctxVideo->current_video_duration_ms = 0;

	video_sample_context_initializer(&ctxVideo);
}

void context_refresh(i2ctx **context, uint32_t media_type) {
	if (media_type == VIDEO_TYPE) {
		(*context)->ctxvideo->earliest_presentation_time = 0;
		(*context)->ctxvideo->latest_presentation_time = 0;
		(*context)->ctxvideo->sequence_number++;
		(*context)->ctxvideo->current_video_duration_ms = 0;
		(*context)->ctxvideo->segment_data_size = 0;
		(*context)->ctxvideo->ctxsample->mdat_sample_length = 0;
		(*context)->ctxvideo->ctxsample->mdat_total_size = 0;
	}
	if (media_type == AUDIO_TYPE) {
		(*context)->ctxaudio->earliest_presentation_time = 0;
		(*context)->ctxaudio->latest_presentation_time = 0;
		(*context)->ctxaudio->sequence_number++;
		(*context)->ctxaudio->current_audio_duration_ms = 0;
		(*context)->ctxaudio->segment_data_size = 0;
		(*context)->ctxaudio->ctxsample->mdat_sample_length = 0;
		(*context)->ctxaudio->ctxsample->mdat_total_size = 0;
	}
	// TODO, depende de lo que se precise en add_sample
}

void video_sample_context_initializer(i2ctx_video **ctxVideo) {
	(*ctxVideo)->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));	
	i2ctx_sample *ctxVSample = (*ctxVideo)->ctxsample;

	ctxVSample->box_flags = 3841;
	ctxVSample->mdat_sample_length = 0;
	ctxVSample->mdat_total_size = 0;
	ctxVSample->moof_pos = 0;
}

uint8_t context_initializer(i2ctx **context, uint32_t media_type){
	if ((media_type != VIDEO_TYPE) && (media_type != AUDIO_TYPE) && (media_type != AUDIOVIDEO_TYPE)) {
		(*context) = NULL;
		return I2ERROR;
	}
	*context = (i2ctx *) malloc(sizeof(i2ctx));

	(*context)->duration_ms = 5 * 1000;
	(*context)->reference_size = 0;

	if ((media_type == VIDEO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		video_context_initializer(context);
	else
		(*context)->ctxvideo = NULL;

	if ((media_type == AUDIO_TYPE) || (media_type == AUDIOVIDEO_TYPE))
		audio_context_initializer(context);
	else
		(*context)->ctxaudio = NULL;
	
	// Threshold: 1/fps * 2 * 1000
	(*context)->threshold_ms = (2*1000)/(((*context)->ctxvideo->frame_rate)); 
	return I2OK;
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

uint32_t init_video_handler(byte *metadata, uint32_t metadata_size, byte *metadata2, uint32_t metadata2_size, byte *sps_data, uint32_t *sps_size, byte *metadata3, uint32_t metadata3_size, byte *pps_data, uint32_t pps_size, byte *output_data, i2ctx **context) {

	uint32_t initVideo, count, sps_pps_data_length;
	uint16_t pps16, sps16, hton_sps_size, hton_pps_size;
	byte *sps_pps_data;
	uint32_t sps_s = *sps_size, total_size;

	total_size = metadata_size + metadata2_size + 2 + sps_s + metadata3_size + 2 + pps_size;
	/*printf("TOTAL metadata_size %u\n", metadata_size); 
	printf("TOTAL metadata_size2 %u\n", metadata2_size); 
	printf("TOTAL sps_s %u\n", sps_s); 
	printf("TOTAL metadata3_size %u\n", metadata3_size); 
	printf("TOTAL pps_size %u\n", pps_size); 
	printf("TOTAL SIZE %u\n", total_size); */

	count = 0;

	sps_pps_data = (byte *) malloc(metadata_size + metadata2_size + 2 + sps_s + metadata3_size + 2 + pps_size);

	// Metadata
	memcpy(sps_pps_data + count, metadata, metadata_size);
	count = count + metadata_size;
	// Metadata2
	memcpy(sps_pps_data + count, metadata2, metadata2_size);
	count = count + metadata2_size;
	// Size SPS
	sps16 = sps_s;
	hton_sps_size = htons(sps16);
	memcpy(sps_pps_data + count, &hton_sps_size, 2);
	count = count + 2;
	// SPS
	memcpy(sps_pps_data + count, sps_data, sps_s);
	count = count + sps_s;
	// Metadata3
	memcpy(sps_pps_data + count, metadata3, metadata3_size);
	count = count + metadata3_size;
	// Size PPS
	pps16 = pps_size;
	hton_pps_size = htons(pps16);
	memcpy(sps_pps_data + count, &hton_pps_size, 2);
	count = count + 2;
	// PPS
	memcpy(sps_pps_data + count, pps_data, pps_size);
	count = count + pps_size;

	sps_pps_data_length = count;

	if(get_width_height(sps_data, sps_size, &((*context)->ctxvideo)) == I2ERROR)
		return I2ERROR;
	//printf("WIDTH %u, HEIGHT %u\n", (*context)->ctxvideo->width, (*context)->ctxvideo->height);
	initVideo = initVideoGenerator(sps_pps_data, sps_pps_data_length, output_data, context);

	return initVideo;
}

uint32_t init_audio_handler(byte *input_data, uint32_t size_input, byte *output_data, i2ctx **context) {
	uint32_t initAudio;

	initAudio =  initAudioGenerator(input_data, size_input, output_data, context);

	return initAudio;
}

uint32_t add_sample(byte *input_data, uint32_t size_input, uint32_t duration_sample, uint32_t timestamp, uint32_t media_type, byte *output_data, uint8_t is_intra, i2ctx **context) {
	uint32_t seg_gen, samp_len;
	
	if (media_type == VIDEO_TYPE) {
		seg_gen = I2OK;
		//printf("Before close segmentation %d\n", ((((*context)->duration_ms) - ((*context)->threshold_ms)) <= ((*context)->ctxvideo->current_video_duration_ms)));
		// Close segmentation
		if ((is_intra == TRUE) && ((((*context)->duration_ms) - ((*context)->threshold_ms)) <= ((*context)->ctxvideo->current_video_duration_ms))) {
			//printf("Close segmentation\n");
			seg_gen = segmentGenerator((*context)->ctxvideo->segment_data, (*context)->ctxvideo->segment_data_size, output_data, VIDEO_TYPE, context);			
			if(seg_gen != I2ERROR) {
				(*context)->ctxvideo->sequence_number++;
				context_refresh(context, VIDEO_TYPE); // TODO
			} else {
				seg_gen = I2ERROR;
			}
		}
		// Add sample or Init new segmentation
		//printf("Add sample or Init new segmentation %d\n", seg_gen);
		if(seg_gen != I2ERROR) {
			//printf("NO ERROR\n");
			i2ctx_sample *ctxSample = (*context)->ctxvideo->ctxsample;
			// Add segment data
			memcpy((*context)->ctxvideo->segment_data + (*context)->ctxvideo->segment_data_size, input_data, size_input);
			(*context)->ctxvideo->segment_data_size += size_input;
			if(ctxSample->mdat_sample_length == 0) {
				//printf("First sample\n");
				(*context)->ctxvideo->earliest_presentation_time = timestamp;
			}
			(*context)->ctxvideo->latest_presentation_time = timestamp;
			(*context)->ctxvideo->current_video_duration_ms += duration_sample;

			// Add metadata
			samp_len = ctxSample->mdat_sample_length;
			ctxSample->mdat[samp_len].size = size_input;
			ctxSample->mdat[samp_len].duration_ms = duration_sample;
			ctxSample->mdat[samp_len].timestamp = timestamp;
			ctxSample->mdat[samp_len].key = is_intra;
			ctxSample->mdat_sample_length++;
		}

	} else if(media_type == AUDIO_TYPE) {
		seg_gen = I2OK;
		// Close segmentation
		if ((((*context)->ctxvideo != NULL) && (is_intra == TRUE)) || (((*context)->ctxvideo == NULL) && (((*context)->duration_ms) <= ((*context)->ctxaudio->current_audio_duration_ms)))) { //this condition should be checked
			seg_gen = segmentGenerator((*context)->ctxaudio->segment_data, (*context)->ctxaudio->segment_data_size, output_data, AUDIO_TYPE, context);			
			if(seg_gen != I2ERROR) {
				(*context)->ctxaudio->sequence_number++;
				context_refresh(context, AUDIO_TYPE); // TODO
			} else {
				seg_gen = I2ERROR;
			}
		}
		// Add sample or Init new segmentation
		if(seg_gen != I2ERROR) {
			i2ctx_sample *ctxSample = (*context)->ctxaudio->ctxsample;
			// Add segment data
			memcpy((*context)->ctxaudio->segment_data + (*context)->ctxaudio->segment_data_size, input_data, size_input);
			(*context)->ctxaudio->segment_data_size = (*context)->ctxaudio->segment_data_size + size_input;
			if(ctxSample->mdat_sample_length == 0)
				(*context)->ctxaudio->earliest_presentation_time = timestamp;
			(*context)->ctxaudio->latest_presentation_time = timestamp;
			(*context)->ctxaudio->current_audio_duration_ms += duration_sample;

			// Add metadata
			samp_len = ctxSample->mdat_sample_length;
			ctxSample->mdat[samp_len].size = size_input;
			ctxSample->mdat[samp_len].duration_ms = duration_sample;
			ctxSample->mdat[samp_len].timestamp = timestamp;
			ctxSample->mdat[samp_len].key = is_intra;
			ctxSample->mdat_sample_length++;
		}
	} else if(media_type == AUDIOVIDEO_TYPE) {
		seg_gen = I2ERROR;
	} else {
		seg_gen = I2ERROR;
	}

	return seg_gen;
}
