#include "i2libdash.h"
#include "../i2libisoff/i2libisoff.h"

// Función recoge h264 y obtiene sps y pps, rellena el context con width y height.
uint32_t h264_handler(byte *input_data, uint32_t size_input, i2ctx *context);
// Privada. Función te dice si un sample es intra o no.
uint8_t is_key_frame(byte *input_data, uint32_t size_input);



