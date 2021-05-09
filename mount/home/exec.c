#include <errno.h>
#include <stdlib.h>

#include "../../lib/hill.h"

int main(void)
{
	return hill("/home") && errno != EBUSY?EXIT_FAILURE:EXIT_SUCCESS;
}
