#pragma once

#define OK 0
#define NO_FILENAME 1
#define NO_FILE 2
#define FSEEK_ERROR 3
#define MEM_ALLOC_ERR 4
#define DL_ERROR 5

char *error_msg(int err);
