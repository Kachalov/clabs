#pragma once

#define EOK 0
#define EIO 1
#define EOOM 2
#define ENOTFOUND 4
#define EFORMAT 5
#define EARGS 6

#ifdef DEBUG
#define DPRINT(...) do {\
fprintf(stderr, "DEBUG: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");\
} while (0)
#else
#define DPRINT(...)
#endif
