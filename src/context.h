#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <gpac/isomedia.h>
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

    GF_ISOFile *file;
    GF_ISOSample *sample;

} i2DASHContext;


/**
 * @brief   initializes an i2DASHContext structure.
 *
 * @note    default segment duration: 1000ms.
 * @note    default frame rate: 24fps.
 * @note    by default, one fragment per segment.
 */
i2DASHError i2dash_context_initialize(i2DASHContext *context);

/**
 * @brief   updates the frame rate and the related parameters inside the
 *          <em>context</em> structure.
 * @param   context pointer the context structure to update
 * @param   frame_rate new frame rate to consider
 * @return  i2DASH_BAD_PARAM if the <em>frame_rate</em> is not valid (no
 *          changes are made then). i2DASH_OK otherwise.
 */
i2DASHError i2dash_context_update_frame_rate(i2DASHContext *context, float frame_rate);

#endif
