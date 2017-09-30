#include <stdio.h>
#include <string.h>

#include "errors.h"

char *error_msg(int err)
{
    static char *msg = "";

    switch (err)
    {
        case OK:
            msg = "Not an error at all ;)";
            break;
        case NO_FILENAME:
            msg = "No filename scepified";
            break;
        case NO_FILE:
            msg = "No file found";
            break;
        case FSEEK_ERROR:
            msg = "Fseek error";
            break;
        case MEM_ALLOC_ERR:
            msg = "Memory allocate error";
            break;
        default:
            sprintf(msg, "Unknown code #%d", err);
            break;
    }

    return msg;
}
