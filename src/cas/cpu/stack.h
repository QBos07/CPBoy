#include <stdint.h>

extern "C"
void on_alt_stack(void *stack, void (*fun)(void *arg1), void *arg1);
