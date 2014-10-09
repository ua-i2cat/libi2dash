#include "../include/i2libdash.h"
int main(){
    i2ctx *context, *context_null = NULL;
    byte *sps_data, *pps_data, *metadata, *metadata2, *metadata3, *destination_data, *aac_data, *source_data, *source_data_a;
    uint32_t metadata_size, metadata2_size, metadata3_size, init_video, init_audio, size_source_data, size_source_data_a;
    uint32_t sps_size, pps_size, aac_data_size, duration_sample, timestamp, seg_size, i, sps_zero = 0;
    uint8_t is_intra, i2error, close_fragment;

    FILE *output_video_i,*output_audio_i;

    i2error= context_initializer(&context, NO_TYPE);
    if (i2error == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
    else
        printf("CONTEXT OK!\n");

    i2error= context_initializer(&context, 4);
    if (i2error == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
    else
        printf("CONTEXT OK!\n");

    i2error= context_initializer(&context, AUDIOVIDEO_TYPE);
    if (i2error == I2ERROR_MEDIA_TYPE) {
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
        exit(1);    
    }
    else
        printf("CONTEXT OK!\n");
    
    // INIT CONTEXT TEST
    printf("CONTEXT:\n DURATION %u, REFERENCE SIZE %u, TRESHH %u\n", context->duration_ms, context->reference_size, context->threshold_ms);

    printf("CONTEXT AUDIO:\n AAC_DATA_LENGTH %u, SEG_SIZE %u, CHANNELS %u SAMPLE_RATE %u SAMPLE_SIZE %u SEQNUM %u EPT %u LPT %u\n", context->ctxaudio->aac_data_length, context->ctxaudio->segment_data_size, context->ctxaudio->channels, context->ctxaudio->sample_rate, context->ctxaudio->sample_size, context->ctxaudio->sequence_number, context->ctxaudio->earliest_presentation_time, context->ctxaudio->latest_presentation_time);

    printf("CONTEXT VIDEO:\n PPS_SPS_DATA_LENGTH %u, SEG_SIZE %u WIDTH %u HEIGHT %u FPS %u EPT %u LPT %u SEQNUM %u\n", context->ctxvideo->pps_sps_data_length, context->ctxvideo->segment_data_size, context->ctxvideo->width, context->ctxvideo->height, context->ctxvideo->frame_rate, context->ctxvideo->earliest_presentation_time, context->ctxvideo->latest_presentation_time, context->ctxvideo->sequence_number);

    printf("CONTEXT SAMPLE AUDIO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxaudio->ctxsample->box_flags, context->ctxaudio->ctxsample->mdat_sample_length, context->ctxaudio->ctxsample->mdat_total_size, context->ctxaudio->ctxsample->moof_pos);

    printf("CONTEXT SAMPLE VIDEO\n FLAGS %u MDAT_SAMP_LENGTH %u MDAT_TOTAL_SIZE %u MDAT_MOOF_POS %u\n", context->ctxvideo->ctxsample->box_flags, context->ctxvideo->ctxsample->mdat_sample_length, context->ctxvideo->ctxsample->mdat_total_size, context->ctxvideo->ctxsample->moof_pos);

    // INIT VIDEO HANDLER TEST

    // SPS
    sps_data = (byte *) malloc (100);
    sps_data[0] = 0x67;
    sps_data[1] = 0x42;
    sps_data[2] = 0xC0;
    sps_data[3] = 0x1E;
    sps_data[4] = 0xD9;
    sps_data[5] = 0x00;
    sps_data[6] = 0xD8;
    sps_data[7] = 0x3D;
    sps_data[8] = 0xE6;
    sps_data[9] = 0xE1;
    sps_data[10] = 0x00;
    sps_data[11] = 0x00;
    sps_data[12] = 0x03;
    sps_data[13] = 0x00;
    sps_data[14] = 0x01;
    sps_data[15] = 0x00;
    sps_data[16] = 0x00;
    sps_data[17] = 0x03;
    sps_data[18] = 0x00;
    sps_data[19] = 0x30;
    sps_data[20] = 0x0F;
    sps_data[21] = 0x16;
    sps_data[22] = 0x2E;
    sps_data[23] = 0x48;
    sps_size = 24;

    // PPS
    pps_data = (byte *) malloc (100);
    pps_data[0] = 0x68;
    pps_data[1] = 0xCB;
    pps_data[2] = 0x81;
    pps_data[3] = 0x32;
    pps_data[4] = 0xC8;
    pps_size = 5;

    // METADATA
    metadata = (byte *) malloc (100);
    metadata[0] = 0x01;
    metadata[1] = 0x42;
    metadata[2] = 0xC0;
    metadata[3] = 0x1E;
    metadata_size = 4;

    // METADATA2
    metadata2 = (byte *) malloc (100);
    metadata2[0] = 0xFF;
    metadata2[1] = 0xE1;
    metadata2_size = 2;

    // METADATA3
    metadata3 = (byte *) malloc (100);
    metadata3[0] = 0x01;
    metadata3_size = 1;

    // DESTINATION DATA
    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);


        //--------------------------------------------------//
        //              ERROR CHECK INIT VIDEO              //
        //--------------------------------------------------//
    printf("//--------------------------------------------------//\n//              ERROR CHECK INIT VIDEO              //\n//--------------------------------------------------//\n");
    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context_null);
    if (init_video == I2ERROR_CONTEXT_NULL)
        printf ("I2ERROR_CONTEXT_NULL! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, NULL, &context);
    if (init_video == I2ERROR_DESTINATION_NULL)
        printf ("I2ERROR_DESTINATION_NULL! code %d\n", init_video);

    init_video = init_video_handler(NULL, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, NULL, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, NULL, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, NULL, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, NULL, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", init_video);

    init_video = init_video_handler(metadata, 0, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, 0, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_zero, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, 0, pps_data, pps_size, destination_data, &context);
    if (init_video == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", init_video);

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, 0, destination_data, &context);
    if (init_video == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", init_video);
    printf("//--------------------------------------------------//\n//             END ERROR CHECK INIT VIDEO           //\n//--------------------------------------------------//\n");
        //--------------------------------------------------//
        //            END-ERROR CHECK INIT VIDEO            //
        //--------------------------------------------------//

    init_video = init_video_handler(metadata, metadata_size, metadata2, metadata2_size, sps_data, &sps_size, metadata3, metadata3_size, pps_data, pps_size, destination_data, &context);
    if (init_video > I2ERROR_MAX) {
        printf("OK INIT VIDEO!\n");
        output_video_i = fopen("/tmp/pruebas/i2dash/video_init2.m4v", "w");
        unsigned int i = 0;
        for(i = 0; i < init_video; i++) {
            fputc(destination_data[i], output_video_i);
        }
        fclose(output_video_i);
    }

    // INIT AUDIO HANDLER TEST

    // AAC METADATA
    aac_data = (byte *) malloc (100 * sizeof(byte*));
    aac_data[0] = 0xaf;
    aac_data[1] = 0x00;
    aac_data[2] = 0x11;
    aac_data[3] = 0x90;

    aac_data_size = 4;

    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);
        //--------------------------------------------------//
        //              ERROR CHECK INIT AUDIO              //
        //--------------------------------------------------//
    printf("//--------------------------------------------------//\n//              ERROR CHECK INIT AUDIO              //\n//--------------------------------------------------//\n");

    init_audio = init_audio_handler(aac_data, aac_data_size, destination_data, &context_null);
    if (init_audio == I2ERROR_CONTEXT_NULL)
        printf ("I2ERROR_CONTEXT_NULL! code %d\n", init_audio);

    init_audio = init_audio_handler(aac_data, aac_data_size, NULL, &context);
    if (init_audio == I2ERROR_DESTINATION_NULL)
        printf ("I2ERROR_DESTINATION_NULL! code %d\n", init_audio);

    init_audio = init_audio_handler(NULL, aac_data_size, destination_data, &context);
    if (init_audio == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", init_audio);

    init_audio = init_audio_handler(aac_data, 0, destination_data, &context);
    if (init_audio == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", init_audio);

    printf("//--------------------------------------------------//\n//            END ERROR CHECK INIT AUDIO            //\n//--------------------------------------------------//\n");
        //--------------------------------------------------//
        //            END-ERROR CHECK INIT AUDIO            //
        //--------------------------------------------------//

    init_audio = init_audio_handler(aac_data, aac_data_size, destination_data, &context);

    if (init_audio > I2ERROR_MAX) {
        printf("OK INIT AUDIO!\n");
        output_audio_i = fopen("/tmp/pruebas/i2dash/audio_init2.m4a", "w");
        unsigned int j = 0;
        for(j = 0; j < init_audio; j++) {
            fputc(destination_data[j], output_audio_i);
        }
        fclose(output_audio_i);
    }

    //VIDEO DATA
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

    source_data_a = (byte *) malloc (100);
    source_data_a[0] = 0x21;
    source_data_a[1] = 011;
    source_data_a[2] = 0x45;
    source_data_a[3] = 0x00;
    source_data_a[4] = 0x14;
    source_data_a[5] = 0x50;
    source_data_a[6] = 0x01;
    source_data_a[7] = 0x46;
    source_data_a[8] = 0xFF;
    source_data_a[9] = 0xF1;
    source_data_a[10] = 0x0A;
    source_data_a[11] = 0x5A;
    source_data_a[12] = 0x5A;
    source_data_a[13] = 0x5A;
    source_data_a[14] = 0x5A;
    source_data_a[15] = 0x5A;
    source_data_a[16] = 0x5A;
    source_data_a[17] = 0x5A;
    source_data_a[18] = 0x5A;
    source_data_a[19] = 0x5A;
    source_data_a[20] = 0x5A;
    source_data_a[21] = 0x5D;
    source_data_a[22] = 0xE5;
    source_data_a[23] = 0xC2;
    source_data_a[24] = 0x14;
    source_data_a[25] = 0xB4;
    source_data_a[26] = 0xB4;
    source_data_a[27] = 0xB4;
    source_data_a[28] = 0xB4;
    source_data_a[29] = 0xB4;
    source_data_a[30] = 0xB4;
    source_data_a[31] = 0xBC;
    source_data_a[32] = 0x21;
    source_data_a[33] = 0x1A;
    source_data_a[34] = 0x13;
    source_data_a[35] = 0xA5;
    source_data_a[36] = 0x9C;
    source_data_a[37] = 0x86;
    source_data_a[38] = 0x04;
    source_data_a[39] = 0x20;

    size_source_data_a = 40;

    duration_sample = 10;
    timestamp = 0;
    destination_data = (byte *) malloc (MAX_MDAT_SAMPLE);   
    is_intra = 0;

        //--------------------------------------------------//
        //           ERROR CHECK ADD SAMPLE VIDEO           //
        //--------------------------------------------------//
    printf("//--------------------------------------------------//\n//           ERROR CHECK ADD SAMPLE VIDEO           //\n//--------------------------------------------------//\n");
    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context_null);
    if (seg_size == I2ERROR_CONTEXT_NULL)
        printf ("I2ERROR_CONTEXT_NULL! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, NULL, is_intra, &context);
    if (seg_size == I2ERROR_DESTINATION_NULL)
        printf ("I2ERROR_DESTINATION_NULL! code %d\n", seg_size);

    seg_size = add_sample(NULL, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", seg_size);

    seg_size = add_sample(source_data, 0, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, 0, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_DURATION_ZERO)
        printf ("I2ERROR_DURATION_ZERO! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, 2, &context);
    if (seg_size == I2ERROR_IS_INTRA)
        printf ("I2ERROR_IS_INTRA! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, NO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, AUDIOVIDEO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    printf("//--------------------------------------------------//\n//         END ERROR CHECK ADD SAMPLE VIDEO         //\n//--------------------------------------------------//\n");
        //--------------------------------------------------//
        //         END-ERROR CHECK ADD SAMPLE VIDEO         //
        //--------------------------------------------------//

    close_fragment = 0;
    for (i=0; i<550; i++) {
        timestamp += 10;
        if ((i == 500) || (i == 0))
            is_intra = 1;
        else
            is_intra = 0;
        seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, VIDEO_TYPE, destination_data, is_intra, &context);
        if (seg_size > I2ERROR_MAX) {
            close_fragment = 1;
            printf("OK VIDEO SEGMENT! %d\n", seg_size);
            output_video_i = fopen("/tmp/pruebas/i2dash/video_seg.m4v", "w");
            unsigned int i = 0;
            for(i = 0; i < seg_size; i++) {
                fputc(destination_data[i], output_video_i);
            }
            fclose(output_video_i);
        }
        if (close_fragment) {
            is_intra = 1;
            close_fragment = 0;
        }
        if (i == 0)
            is_intra = 0;
        seg_size = add_sample(source_data_a, size_source_data_a, duration_sample, timestamp, AUDIO_TYPE, destination_data, is_intra, &context);
        if (seg_size > I2ERROR_MAX) {
            printf("OK AUDIO SEGEMENT! %d\n", seg_size);
            output_audio_i = fopen("/tmp/pruebas/i2dash/audio_seg.m4a", "w");
            unsigned int j = 0;
            // int fputc(int c, FILE *stream);
            for(j = 0; j < seg_size; j++) {
                fputc(destination_data[j], output_audio_i);
            }
            fclose(output_audio_i);
        }
    }

        //--------------------------------------------------//
        //         ERROR CHECK FINISH SEGMENT VIDEO         //
        //--------------------------------------------------//
    printf("//--------------------------------------------------//\n//         ERROR CHECK FINISH SEGMENT VIDEO         //\n//--------------------------------------------------//\n");
    seg_size = finish_segment(VIDEO_TYPE, destination_data, &context_null);
    if (seg_size == I2ERROR_CONTEXT_NULL)
        printf ("I2ERROR_CONTEXT_NULL! code %d\n", seg_size);

    seg_size = finish_segment(VIDEO_TYPE, NULL, &context);
    if (seg_size == I2ERROR_DESTINATION_NULL)
        printf ("I2ERROR_DESTINATION_NULL! code %d\n", seg_size);

    seg_size = finish_segment(NO_TYPE, destination_data, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    seg_size = finish_segment(AUDIOVIDEO_TYPE, destination_data, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    printf("//--------------------------------------------------//\n//       END ERROR CHECK FINISH SEGMENT VIDEO       //\n//--------------------------------------------------//\n");
        //--------------------------------------------------//
        //       END-ERROR CHECK FINISH SEGMENT VIDEO       //
        //--------------------------------------------------//


    seg_size = finish_segment(VIDEO_TYPE, destination_data, &context);
    if (seg_size > I2ERROR_MAX) {
        printf("OK VIDEO SEGMENT! %d\n", seg_size);
        output_video_i = fopen("/tmp/pruebas/i2dash/video_seg_last.m4v", "w");
        unsigned int i = 0;
        for(i = 0; i < seg_size; i++) {
            fputc(destination_data[i], output_video_i);
        }
        fclose(output_video_i);
    }

//NEW CONTEXT ONLY AUDIO

    i2error= context_initializer(&context, AUDIO_TYPE);
    if (i2error == I2ERROR_MEDIA_TYPE) {
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", i2error);
        exit(1);    
    }
    else
        printf("CONTEXT OK!\n");

        //--------------------------------------------------//
        //           ERROR CHECK ADD SAMPLE AUDIO           //
        //--------------------------------------------------//
    printf("//--------------------------------------------------//\n//           ERROR CHECK ADD SAMPLE AUDIO           //\n//--------------------------------------------------//\n");
    seg_size = add_sample(source_data_a, size_source_data_a, duration_sample, timestamp, AUDIO_TYPE, destination_data, is_intra, &context_null);
    if (seg_size == I2ERROR_CONTEXT_NULL)
        printf ("I2ERROR_CONTEXT_NULL! code %d\n", seg_size);

    seg_size = add_sample(source_data_a, size_source_data_a, duration_sample, timestamp, AUDIO_TYPE, NULL, is_intra, &context);
    if (seg_size == I2ERROR_DESTINATION_NULL)
        printf ("I2ERROR_DESTINATION_NULL! code %d\n", seg_size);

    seg_size = add_sample(NULL, size_source_data_a, duration_sample, timestamp, AUDIO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_SOURCE_NULL)
        printf ("I2ERROR_SOURCE_NULL! code %d\n", seg_size);

    seg_size = add_sample(source_data_a, 0, duration_sample, timestamp, AUDIO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_SIZE_ZERO)
        printf ("I2ERROR_SIZE_ZERO! code %d\n", seg_size);

    seg_size = add_sample(source_data_a, size_source_data_a, 0, timestamp, AUDIO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_DURATION_ZERO)
        printf ("I2ERROR_DURATION_ZERO! code %d\n", seg_size);

    seg_size = add_sample(source_data_a, size_source_data_a, duration_sample, timestamp, AUDIO_TYPE, destination_data, 2, &context);
    if (seg_size == I2ERROR_IS_INTRA)
        printf ("I2ERROR_IS_INTRA! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, NO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    seg_size = add_sample(source_data, size_source_data, duration_sample, timestamp, AUDIOVIDEO_TYPE, destination_data, is_intra, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    printf("//--------------------------------------------------//\n//         END ERROR CHECK ADD SAMPLE AUDIO         //\n//--------------------------------------------------//\n");
        //--------------------------------------------------//
        //         END-ERROR CHECK ADD SAMPLE AUDIO         //
        //--------------------------------------------------//

    is_intra = 0;
    for (i=0; i<550; i++) {
        timestamp += 10;
        seg_size = add_sample(source_data_a, size_source_data_a, duration_sample, timestamp, AUDIO_TYPE, destination_data, is_intra, &context);
        if (seg_size > I2ERROR_MAX) {
            printf("OK AUDIO SEGEMENT! %d\n", seg_size);
            output_audio_i = fopen("/tmp/pruebas/i2dash/audio_seg_2.m4a", "w");
            unsigned int j = 0;
            for(j = 0; j < seg_size; j++) {
                fputc(destination_data[j], output_audio_i);
            }
            fclose(output_audio_i);
        }
    }
        //--------------------------------------------------//
        //         ERROR CHECK FINISH SEGMENT AUDIO         //
        //--------------------------------------------------//
    printf("//--------------------------------------------------//\n//         ERROR CHECK FINISH SEGMENT AUDIO         //\n//--------------------------------------------------//\n");
    seg_size = finish_segment(AUDIO_TYPE, destination_data, &context_null);
    if (seg_size == I2ERROR_CONTEXT_NULL)
        printf ("I2ERROR_CONTEXT_NULL! code %d\n", seg_size);

    seg_size = finish_segment(AUDIO_TYPE, NULL, &context);
    if (seg_size == I2ERROR_DESTINATION_NULL)
        printf ("I2ERROR_DESTINATION_NULL! code %d\n", seg_size);

    seg_size = finish_segment(NO_TYPE, destination_data, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    seg_size = finish_segment(AUDIOVIDEO_TYPE, destination_data, &context);
    if (seg_size == I2ERROR_MEDIA_TYPE)
        printf ("I2ERROR_MEDIA_TYPE! code %d\n", seg_size);

    printf("//--------------------------------------------------//\n//       END ERROR CHECK FINISH SEGMENT AUDIO       //\n//--------------------------------------------------//\n");
        //--------------------------------------------------//
        //       END-ERROR CHECK FINISH SEGMENT AUDIO       //
        //--------------------------------------------------//
    seg_size = finish_segment(AUDIO_TYPE, destination_data, &context);
        if (seg_size > I2ERROR_MAX) {
            printf("OK AUDIO SEGEMENT! %d\n", seg_size);
            output_audio_i = fopen("/tmp/pruebas/i2dash/audio_seg_last.m4a", "w");
            unsigned int j = 0;
            for(j = 0; j < seg_size; j++) {
                fputc(destination_data[j], output_audio_i);
            }
            fclose(output_audio_i);
        }

    return 0;
}
