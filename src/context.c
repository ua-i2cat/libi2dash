#include "context.h"


i2DASHError i2dash_context_initiliaze(i2DASHContext *context)
{
    context->segment_nb = 0;
    context->fragment_nb = 0;
    context->frame_nb = 0;
    
    // Default values (segment duration in ms)
    context->segment_duration = 1000;
    context->frames_per_fragment = 24;
    context->frames_per_segment = 24;
    context->frame_rate = 24.0;

    context->file = NULL;
    context->sample = NULL;

    return i2DASH_OK;
}

i2DASHError i2dash_context_update_frame_rate(i2DASHContext *context, float frame_rate)
{
    if (frame_rate <= 0.0) {
        return i2DASH_ERROR;
    }

    // TODO
    //return i2DASH_OK;
    return i2DASH_ERROR;
}
