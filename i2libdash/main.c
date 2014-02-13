#include "i2libdash.h"
int main(){
	i2ctx *context;

	context_initializer(&context);

	printf("DURATION %u, REFERENCE SIZE %u, TRESHH %f\n", context->duration_ms, context->reference_size, context->threshold_ms);

	return 0;
}
