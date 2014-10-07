#include "../include/i2libisoff.h"

int main(){
    byte *source_data;
    byte *destination_data;

    uint32_t size_source_data;

    FILE *output_video_i, *output_audio_i, *output_segment_v, *output_segment_a;

    i2ctx *context = (i2ctx *) malloc(sizeof(i2ctx));
    context->ctxaudio = (i2ctx_audio *) malloc(sizeof(i2ctx_audio));
    context->ctxvideo = (i2ctx_video *) malloc(sizeof(i2ctx_video));

    i2ctx_audio *ctxAudio = context->ctxaudio; 
    i2ctx_video *ctxVideo = context->ctxvideo;
    
    ctxVideo->width = 854;
    ctxVideo->height = 480;

    ctxAudio->channels = 2;
    ctxAudio->sample_size = 16;
    ctxAudio->sample_rate = 48000;

    uint32_t initVideo, initAudio;

    // VIDEO INIT GENERATOR TEST
    source_data = (byte *) malloc (100);
    source_data[0] = 0x01;
    source_data[1] = 0x42;
    source_data[2] = 0xC0;
    source_data[3] = 0x1E;
    source_data[4] = 0xFF;
    source_data[5] = 0xE1;
    source_data[6] = 0x00;
    source_data[7] = 0x18;
    source_data[8] = 0x67;
    source_data[9] = 0x42;
    source_data[10] = 0xC0;
    source_data[11] = 0x1E;
    source_data[12] = 0xD9;
    source_data[13] = 0x00;
    source_data[14] = 0xD8;
    source_data[15] = 0x3D;
    source_data[16] = 0xE6;
    source_data[17] = 0xE1;
    source_data[18] = 0x00;
    source_data[19] = 0x00;
    source_data[20] = 0x03;
    source_data[21] = 0x00;
    source_data[22] = 0x01;
    source_data[23] = 0x00;
    source_data[24] = 0x00;
    source_data[25] = 0x03;
    source_data[26] = 0x00;
    source_data[27] = 0x30;
    source_data[28] = 0x0F;
    source_data[29] = 0x16;
    source_data[30] = 0x2E;
    source_data[31] = 0x48;
    source_data[32] = 0x01;
    source_data[33] = 0x00;
    source_data[34] = 0x05;
    source_data[35] = 0x68;
    source_data[36] = 0xCB;
    source_data[37] = 0x81;
    source_data[38] = 0x32;
    source_data[39] = 0xC8;

    size_source_data = 40;

    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);
    
    initVideo = initVideoGenerator(source_data, size_source_data, destination_data, &context);

    if ((initVideo != I2ERROR_ISOFF) && (initVideo != I2ERROR_CONTEXT_NULL) && (initVideo != I2ERROR_SOURCE_NULL) && (initVideo != I2ERROR_DESTINATION_NULL) && (initVideo != I2ERROR_SIZE_ZERO)){
        printf("OK INIT VIDEO!\n");
        output_video_i = fopen("/tmp/pruebas/isoff/video_init.m4v", "w");
        unsigned int i = 0;
        for(i = 0; i < initVideo; i++) {
            fputc(destination_data[i], output_video_i);
        }
        fclose(output_video_i);
    } else {
        if (initVideo == I2ERROR_SIZE_ZERO) {
            printf ("I2ERROR_SIZE_ZERO: %d\n", initVideo);
        }
        if (initVideo == I2ERROR_ISOFF) {
            printf ("I2ERROR: %d\n", initVideo);
        }
        if (initVideo == I2ERROR_CONTEXT_NULL) {
            printf ("I2ERROR_CONTEXT_NULL: %d\n", initVideo);
        }       
        if (initVideo == I2ERROR_SOURCE_NULL) {
            printf ("I2ERROR_SOURCE_NULL: %d\n", initVideo);
        }
        if (initVideo == I2ERROR_DESTINATION_NULL) {
            printf ("I2ERROR_DESTINATION_NULL: %d\n", initVideo);
        }
    }
    
    free(source_data);
    free(destination_data);

    // AUDIO INIT GENERATOR TEST
    source_data = (byte *) malloc (100);
    /*
    AUDIO LC AAC --> 1190
    source_data[0] = 0x11;
    source_data[0] = 0x90;

    size_source_data = 2;
    */

    /*
    AUDIO HE AAC --> EB098800
    */
    source_data[0] = 0xEB;
    source_data[1] = 0x09;
    source_data[2] = 0x88;
    source_data[3] = 0x00;

    size_source_data = 4;

    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);

    initAudio = initAudioGenerator(source_data, size_source_data, destination_data, &context);
    if ((initAudio != I2ERROR_ISOFF) && (initAudio != I2ERROR_CONTEXT_NULL) && (initAudio != I2ERROR_SOURCE_NULL) && (initAudio != I2ERROR_DESTINATION_NULL) && (initAudio != I2ERROR_SIZE_ZERO)){
        printf("OK INIT AUDIO!\n");
        output_audio_i = fopen("/tmp/pruebas/isoff/audio_init.m4a", "w");
        unsigned int i = 0;
        for(i = 0; i < initAudio; i++) {
            fputc(destination_data[i], output_audio_i);
        }
        fclose(output_audio_i);
    } else {
        if (initAudio == I2ERROR_SIZE_ZERO) {
            printf ("I2ERROR_SIZE_ZERO: %d\n", initAudio);
        }
        if (initAudio == I2ERROR_ISOFF) {
            printf ("I2ERROR: %d\n", initAudio);
        }
        if (initAudio == I2ERROR_CONTEXT_NULL) {
            printf ("I2ERROR_CONTEXT_NULL: %d\n", initAudio);
        }       
        if (initAudio == I2ERROR_SOURCE_NULL) {
            printf ("I2ERROR_SOURCE_NULL: %d\n", initAudio);
        }
        if (initAudio == I2ERROR_DESTINATION_NULL) {
            printf ("I2ERROR_DESTINATION_NULL: %d\n", initAudio);
        }
    }

    uint32_t seg_gen_video, seg_gen_audio;

    // VIDEO SEGMENT GENERATOR TEST
    uint32_t media_type = VIDEO_TYPE;

    ctxVideo->earliest_presentation_time = 42;
    ctxVideo->latest_presentation_time = 8823;

    ctxVideo->sequence_number = 0;

    ctxVideo->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));
    i2ctx_sample *ctxVSample = ctxVideo->ctxsample;

    ctxVSample->box_flags = 3841;
    ctxVSample->mdat_sample_length = 2;
    
    unsigned int i = 0;
    ctxVSample->mdat[0].duration_ms = 41;
    ctxVSample->mdat[0].size = 1868;
    ctxVSample->mdat[0].key = 1;
    ctxVSample->mdat[0].delay = 0;
    for (i = 1; i < ctxVSample->mdat_sample_length; ++i)
    {
        ctxVSample->mdat[i].duration_ms = 42;
        ctxVSample->mdat[i].size = 12;
        ctxVSample->mdat[i].key = 0;
        ctxVSample->mdat[i].delay = 0;
    }

    source_data = (byte *) malloc (100);
    source_data[0] = 0x0;
    source_data[1] = 0x0;
    source_data[2] = 0x02;
    source_data[3] = 0x6E;
    source_data[4] = 0x06;
    source_data[5] = 0x05;
    source_data[6] = 0xFF;
    source_data[7] = 0xFF;
    source_data[8] = 0x6A;
    source_data[9] = 0xDC;
    source_data[10] = 0x45;
    source_data[11] = 0xE9;
    source_data[12] = 0xBD;
    source_data[13] = 0xE6;
    source_data[14] = 0xD9;
    source_data[15] = 0x48;
    source_data[16] = 0xB7;
    source_data[17] = 0x96;
    source_data[18] = 0x2C;
    source_data[19] = 0xD8;
    source_data[20] = 0x20;
    source_data[21] = 0xD9;
    source_data[22] = 0x23;
    source_data[23] = 0xEE;
    source_data[24] = 0xEF;
    source_data[25] = 0x78;
    source_data[26] = 0x32;
    source_data[27] = 0x36;
    source_data[28] = 0x34;
    source_data[29] = 0x20;
    source_data[30] = 0x2D;
    source_data[31] = 0x20;
    source_data[32] = 0x43;
    source_data[33] = 0x6F;
    source_data[34] = 0x70;
    source_data[35] = 0x79;
    source_data[36] = 0x6C;
    source_data[37] = 0x65;
    source_data[38] = 0x66;
    source_data[39] = 0x75;

    size_source_data = 40;

    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);

    seg_gen_video = segmentGenerator(source_data, size_source_data, destination_data, media_type, &context);
    if ((seg_gen_video != I2ERROR_ISOFF) && (seg_gen_video != I2ERROR_CONTEXT_NULL) && (seg_gen_video != I2ERROR_SOURCE_NULL) && (seg_gen_video != I2ERROR_DESTINATION_NULL) && (seg_gen_video != I2ERROR_SIZE_ZERO) && (seg_gen_video != I2ERROR_MEDIA_TYPE)){
        printf("OK VIDEO SEGMENT!\n");
        output_segment_v = fopen("/tmp/pruebas/isoff/video_segment.m4v", "w");
        unsigned int i = 0;
        for(i = 0; i < seg_gen_video; i++) {
            fputc(destination_data[i], output_segment_v);
        }
        fclose(output_segment_v);
    } else {
        if (seg_gen_video == I2ERROR_SIZE_ZERO) {
            printf ("I2ERROR_SIZE_ZERO: %d\n", seg_gen_video);
        }
        if (seg_gen_video == I2ERROR_MEDIA_TYPE) {
            printf ("I2ERROR_MEDIA_TYPE: %d\n", seg_gen_video);
        }
        if (seg_gen_video == I2ERROR_ISOFF) {
            printf ("I2ERROR: %d\n", seg_gen_video);
        }
        if (seg_gen_video == I2ERROR_CONTEXT_NULL) {
            printf ("I2ERROR_CONTEXT_NULL: %d\n", seg_gen_video);
        }       
        if (seg_gen_video == I2ERROR_SOURCE_NULL) {
            printf ("I2ERROR_SOURCE_NULL: %d\n", seg_gen_video);
        }
        if (seg_gen_video == I2ERROR_DESTINATION_NULL) {
            printf ("I2ERROR_DESTINATION_NULL: %d\n", seg_gen_video);
        }
    }
    
    // AUDIO SEGMENT GENERATOR TEST
    media_type = AUDIO_TYPE;

    ctxAudio->earliest_presentation_time = 0;
    ctxAudio->latest_presentation_time = 8853;
    context->reference_size = 145645;

    ctxAudio->sequence_number = 0;

    ctxAudio->ctxsample = (i2ctx_sample *) malloc(sizeof(i2ctx_sample));
    i2ctx_sample *ctxASample = ctxAudio->ctxsample;

    ctxASample->box_flags = 769;
    ctxASample->mdat_sample_length = 2;
    i = 0;

    ctxASample->mdat[0].duration_ms = 21;
    ctxASample->mdat[0].size = 341;
    for (i = 1; i < ctxASample->mdat_sample_length; ++i)
    {
        ctxASample->mdat[i].duration_ms = 21;
        ctxASample->mdat[i].size = 341;
    }

    source_data = (byte *) malloc (100);
    source_data[0] = 0x21;
    source_data[1] = 011;
    source_data[2] = 0x45;
    source_data[3] = 0x00;
    source_data[4] = 0x14;
    source_data[5] = 0x50;
    source_data[6] = 0x01;
    source_data[7] = 0x46;
    source_data[8] = 0xFF;
    source_data[9] = 0xF1;
    source_data[10] = 0x0A;
    source_data[11] = 0x5A;
    source_data[12] = 0x5A;
    source_data[13] = 0x5A;
    source_data[14] = 0x5A;
    source_data[15] = 0x5A;
    source_data[16] = 0x5A;
    source_data[17] = 0x5A;
    source_data[18] = 0x5A;
    source_data[19] = 0x5A;
    source_data[20] = 0x5A;
    source_data[21] = 0x5D;
    source_data[22] = 0xE5;
    source_data[23] = 0xC2;
    source_data[24] = 0x14;
    source_data[25] = 0xB4;
    source_data[26] = 0xB4;
    source_data[27] = 0xB4;
    source_data[28] = 0xB4;
    source_data[29] = 0xB4;
    source_data[30] = 0xB4;
    source_data[31] = 0xBC;
    source_data[32] = 0x21;
    source_data[33] = 0x1A;
    source_data[34] = 0x13;
    source_data[35] = 0xA5;
    source_data[36] = 0x9C;
    source_data[37] = 0x86;
    source_data[38] = 0x04;
    source_data[39] = 0x20;

    size_source_data = 40;

    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);

    seg_gen_audio = segmentGenerator(source_data, size_source_data, destination_data, media_type, &context);
    if ((seg_gen_audio != I2ERROR_ISOFF) && (seg_gen_audio != I2ERROR_CONTEXT_NULL) && (seg_gen_audio != I2ERROR_SOURCE_NULL) && (seg_gen_audio != I2ERROR_DESTINATION_NULL) && (seg_gen_audio != I2ERROR_SIZE_ZERO) && (seg_gen_audio != I2ERROR_MEDIA_TYPE)){
        printf("OK AUDIO SEGMENT!\n");
        output_segment_a = fopen("/tmp/pruebas/isoff/audio_segment.m4a", "w");
        unsigned int i = 0;

        for(i = 0; i < seg_gen_audio; i++) {
            fputc(destination_data[i], output_segment_a);
        }
        fclose(output_segment_a);
    } else {
        if (seg_gen_audio == I2ERROR_SIZE_ZERO) {
            printf ("I2ERROR_SIZE_ZERO: %d\n", seg_gen_audio);
        }
        if (seg_gen_audio == I2ERROR_MEDIA_TYPE) {
            printf ("I2ERROR_MEDIA_TYPE: %d\n", seg_gen_audio);
        }
        if (seg_gen_audio == I2ERROR_ISOFF) {
            printf ("I2ERROR: %d\n", seg_gen_audio);
        }
        if (seg_gen_audio == I2ERROR_CONTEXT_NULL) {
            printf ("I2ERROR_CONTEXT_NULL: %d\n", seg_gen_audio);
        }       
        if (seg_gen_audio == I2ERROR_SOURCE_NULL) {
            printf ("I2ERROR_SOURCE_NULL: %d\n", seg_gen_audio);
        }
        if (seg_gen_audio == I2ERROR_DESTINATION_NULL) {
            printf ("I2ERROR_DESTINATION_NULL: %d\n", seg_gen_audio);
        }
    }

    return 0;
}
