#include "MyStm32.hpp"
/*-------------------------------------------------------------
    stm32g031k8 - nucleo32
--------------------------------------------------------------*/

/*-------------------------------------------------------------
    main
--------------------------------------------------------------*/
//'uart' and 'board' instances already created in MyStm32.hpp

//using pin D12 on Nucleo board as a switch
auto sw = GpioPin(board.D[12],LOWISON).mode(INPUT).pull(PULLUP);

                int
main            ()
                {
                //board.led is config locked, try to change
                board.led.mode(INPUT); 
                //does not change (led keeps working)
                //.lock() must be working

                auto n = 0;
                while( true ){
                    //toggle rate depends on switch
                    delayMS( sw.isOn() ? 100 : 500 );
                    board.led.toggle();
                    uart.print("count: %u\r\n", n++);
                    }
                }
