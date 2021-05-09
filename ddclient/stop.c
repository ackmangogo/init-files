#include <stdlib.h>
#include <unistd.h>
#include "../lib/stop.h"

int main(void)
{
        return kill_by_exec(SIGKILL, "/usr/bin/ddclient", NULL)?EXIT_SUCCESS:EXIT_FAILURE;
}

