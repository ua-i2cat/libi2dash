#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "error.h"


typedef struct {
    int segment_nb;
    int fragment_nb;
    int frame_nb;

    /** segment duration in ms */
    int segment_duration;

    int frames_per_fragment;
    int frames_per_segment;

    float frame_rate;
} i2DASHContext;


i2DASHError i2dash_context_update_frame_rate(i2DASHContext *context, float frame_rate);

#endif
