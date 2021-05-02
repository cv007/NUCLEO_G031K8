# STM32 NUCLEO G031K8
----------
#### This is a minimal example for the Nucleo32 board with the g031k8. There are 2 source files (main.cpp, startup.cpp), header files and a linker script in the root folder. No manufacturer code or headers are used.

#### The script folder contains bash scripts for compiling, so no makefile is needed and simply running _./update.sh_ is all that is needed. Folders will be created to contain the object files (obj), lss files (lss), and bin files (bin). The programming step can be changed as needed, and in this case is using the nucleo virtual drive by simply cp'ing the bin file to the drive.

#### The only additional thing needed is a compiler. Google for _'GNU Arm Embedded Toolchain Downloads'_ and you will find one. Extract the downloaded archive somewhere (in this same folder if you wish), then modify the _ARM_ var in the _scripts/common.sh_ file so it points to the bin folder of the toolchain.

#### The example uses C++, and its purpose is show C++. The header files contain the code, so no source files needed other than startup and main and is taking advantage of both the automatic inline property of structs/classes when there is no seperate declaration and definition, and also the C++17 feature of inline vars.

#### The Gpio class can easily be moved to any other stm32 with the same/similar style gpio peripheral, and the only change needed is to modify the mcu specific header which enums the available PIN's for the mcu. It may not always be as efficient as it could be when the compiler needs to use global storage for a pin instance, but in many cases that do not 'jump scope' the resulting code will be as minimal as anything else. (In this case, you can pass 'false' to the instance argument which then bypasses the Rcc enable to eliminate that code when you know its not needed). 

#### Function chaining was also put to use in the Gpio class as the stm32 is suited for that because of the way it spreads the pin config over several registers. You can then specify these properties in an easier way and in the order you want. The Uart constructor shows its use and also main.cpp shows it. There are alternatives to do similar via template parameter packs (single set of options provided, template argument deduction figures it out via the enum types passed in), but is not worth the trouble as function chaining works well in this case.

#### The Uart class shows the use of a virtual function via Printer class inheritence to get printf style use. The Printer class is using sprintf to do the work because it is easier for a simple example, but getting fprintf involved can also be done but requires more work. Any class with a write function can inherit Printer for printf style use. The Uart class also shows static constexpr use (via the mcu header) along with Gpio/PIN to specify Uart instance properties (also lamda function shown to set rcc enable), and in this example you can specify the Uart wanted by its uart number and tx/rx pins you want to use, and the Uart class handles setting up the pin.

#### Also demonstrated, is that the startup code is not difficult for cortex-m, and moving the vector table to ram is also easy. The linker script makes slight modifications to the typcical cortex-m linker script- the addition of a .ramvector section along with some symbols to provide its adddresses, and adding some stack checking assert to warn about lack of stack space.

#### An earlier all-in-one file variation can be seen in the online compiler - https://godbolt.org/z/hf63Wf5qY where it is now split out into appropriate headers here.

#### So, you do not need to stick to the manufacturers way of doing things if you prefer something else (better). The C++ language is also quite nice and as seen here there is no C++ standard library in use and there is no requirement to use it. You still have a limited mcu, so you weigh the cost of speed/space vs ease of use. The C++ language itself has quite a nice toolbox, and an mcu is a good fit for its use.
