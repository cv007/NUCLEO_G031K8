//MyAvr.hpp
#pragma once
/*-------------------------------------------------------------
    using - stm32g031k8 - nucleo32
--------------------------------------------------------------*/
#include <cstdint>

using u8    = uint8_t;
using i8    = int8_t;
using u16   = uint16_t;
using i16   = int16_t;
using u32   = uint32_t;
using i32   = int32_t;
using u64   = uint64_t;
using i64   = int64_t;

#define SCA     static constexpr auto
#define II      [[ gnu::always_inline ]] inline
#define NOP     asm("nop")

/*--------------------------------------------------------------
    system vars - global access
--------------------------------------------------------------*/
struct System {

                //default out of reset, HSI16
                static inline u32 fcpu{ 16000000 };
};


/*--------------------------------------------------------------
    util functions - a Util.hpp header is a better place
--------------------------------------------------------------*/
                //helper template to get array size
                template<typename T, int N>
                auto
arraySize       (T(&)[N]){ return N; }

                #pragma GCC push_options
                #pragma GCC optimize ("-Os")

                //simple blocking inline delays
                #define CYCLES_PER_LOOP 4
                II static void 
delayCycles     (volatile i32 n){ while(n -= CYCLES_PER_LOOP, n > 0){} }
                II static void 
delayMS         (u16 ms){ delayCycles(System::fcpu/1000*ms-1); }
                II static void 
delayUS         (u16 us){ delayCycles(System::fcpu/1000000*us-1); }
                #undef CYCLES_PER_LOOP

                #pragma GCC pop_options


/*--------------------------------------------------------------
    mcu include
--------------------------------------------------------------*/
#include "stm32g031k8.hpp"

/*--------------------------------------------------------------
    common includes and inline vars
--------------------------------------------------------------*/
#include "Boards.hpp"
inline Boards::Nucleo32g031 board;      //everyone can access
inline Uart uart{ board.uart, 230400 }; //everyone can access
using namespace PINS;                   //bring into global namespace
