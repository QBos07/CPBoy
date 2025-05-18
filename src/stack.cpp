#include "sdk/os/debug.h"
#include "sdk/os/lcd.h"
#include <cstddef>
#include <cstdlib>
#include <csetjmp>

extern "C" constexpr unsigned int __stack_chk_guard = 0xEEEEEEEE;

extern "C" void __attribute__((noreturn)) __stack_chk_fail() {
    std::jmp_buf buf;
    setjmp(buf);
    for (std::size_t e = 0; e < sizeof(buf) / sizeof(*buf); e++) {
        Debug_Printf(3, e, true, 0, "%u: %08x", e, buf[e]);
    }
    LCD_Refresh();
    Debug_WaitKey();
    std::exit(EXIT_FAILURE);
}