import qbs

LPCProduct {
    type: "application"
    //type: "elf","hex","bin"

//    consoleApplication: true

    //type: "staticlibrary"
    destinationDirectory: "./bin"
    buildDirectory: "./build"

    cpp.positionIndependentCode: false
    cpp.executableSuffix: ".elf"

    //cpp.compilerPath: "C:/ARM/gcc-arm-none-eabi-4_9/bin/arm-none-eabi-gcc-4.9.3.exe"
    //cpp.compilerName: "arm-none-eabi-gcc-4.9.3.exe"
    //cpp.linkerPath:   "C:/ARM/gcc-arm-none-eabi-4_9/bin/arm-none-eabi-ld.exe"
    //cpp.linkerName:   "arm-none-eabi-ld.exe"

//    cpp.libraryPaths: "./lib"

//    cpp.staticLibraries: [
//        "CubeMX.a"
//    ]

    Properties {
        //condition: cpp.debugInformation
        //condition: qbs.buildVariant === "debug"
        condition: qbs.buildVariant === "release"
        //cpp.defines: outer.concat("DEBUG")
        //cpp.defines: outer.concat(["DEBUG=1"])
    }

//    asm.commonCompilerFlags: [
//        "-D__RAM_MODE__=0",
//    ]

    cpp.commonCompilerFlags: [
        "-Wa,--defsym,__RAM_MODE__=0",
        "-g",
        //------------------------
        //"-c",
        "-mcpu=cortex-m3",
        "-mthumb",
        "-Wall",
        //"-O$(OPTIM)",
        "-mapcs-frame",
        //"-D__thumb2__=1",
        "-msoft-float",
        //"-gdwarf-2",
        //"-mno-sched-prolog",
        //"-fno-hosted",
        "-mtune=cortex-m3",
        "-march=armv7-m",
        "-mfix-cortex-m3-ldrd",
        "-ffunction-sections",
        "-fdata-sections",
        //-------------------------------------------------------
        //"-mthumb-interwork",
        //"-mno-bit-align",
        //"mstructure-size-boundary=8",
        //"-Wpacked",
        //"-Wpadded",
        //"-fpack-struct=0",
        //-------------------------------------------------------
        "-fno-builtin",
        "-fno-strict-aliasing",
        //"-D PACK_STRUCT_END=__attribute\(\(packed\)\)",
        //"-D ALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\)",
        //"-fmessage-length=0",
        //"-funsigned-char",
        //"-Wextra",
        //"-MMD",
        //"-MP",
        //"-MF"$(@:%.o=%.d)"",
        //"-MT"$(@:%.o=%.d)"",
/*
        "-mthumb",
        "-mcpu=cortex-m4",
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16",
        //-----------------
        // Оптимизация компиляции
        //http://habrahabr.ru/post/191058/
        "-fno-exceptions",
        "-fno-unwind-tables",
        "-fno-asynchronous-unwind-tables",
        "-ffunction-sections",
        "-fdata-sections",
        //-----------------
        "-Wl,--gc-sections",
        //-----------------
        "-fno-builtin",
        "-fno-inline",
        "-std=c99",
        //"-std=c++11",
        // сгенерировать карту памяти (linker memory map)
        "-Wl,-Map=./build/CubeMX.map",
        "-fpack-struct",
        // сгенерировать таблицу перекрестных ссылок (cross reference table, опция для линкера)
        "-Wl,-cref",
        "-Wcpp",
        "-std=gnu99",
        // Generate debug information
        "-g",
        //------------------
        "-nostdlib",
        //"-nostartfiles",
        "-ffreestanding",
        //------------------
*/
    ]

    cpp.linkerFlags:[        
        // Semihosting
        // http://www.wolinlabs.com/blog/stm32f4.semihosting.html
        "--specs=rdimon.specs",
        "-lrdimon",
        //--------------------------------------------------
        "-lg",
        "-lgcc",
        "-lc",
        "-lm",
        "-lnosys",
        //--------------------------------------------------
        "-nostartfiles",
        "-nodefaultlibs",
        "-nostdlib",
        //--------------------------------------------------
        "-static",
        "-mcpu=cortex-m3",
        "-mthumb",
        "-Wl,-Map=project.map",
        "-mthumb-interwork",
        //"-Wl,--start-group $(TARGET_FWLIB_LIB)",
        "-Wl,--start-group",        
        //"-L$(THUMB2GNULIB) ",
        //"-L$(THUMB2GNULIB2)",
        //"-lstdc++",
        //"-lsupc++",
        //"-Wl,--end-group",
        "-Wl,--gc-sections",
        //"-Wl,--print-gc-sections",
        //--------------------------------------------------


/*
        "-mthumb",
        "-mcpu=cortex-m4",
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16",
        "--specs=nano.specs",
        "--specs=nosys.specs",
        // Подключить карту памяти (linker memory map)
        //"-Wl,-Map=./build/CubeMX.map",
        "-Wl,-Map=CubeMX.map",
        // Подключить таблицу перекрестных ссылок (cross reference table, опция для линкера)
        "-Wl,-cref",
        "-u _printf_float -u _scanf_float",
        //Оптимизация сборки секций
        "-Wl,--gc-sections",
        // Do not link dynamic libraries (use .a libraries instead of .so)
        //"--static",
        "-static",
        // Do not link standard start files. We are providing our own start file *.s
        //"-nostartfiles",        
        "-lnosys",
        // Подключает libgcc.a: Compiler helper library
        "-lgcc",
        // Подключает libc.a: Standard C library (stdlib, stdio, string,…)
        "-lc",
        // Подключает libm.a: Mathematical functions (log, sin,…)
        "-lm",
        // Generate debug information
        "-g",
        //"-Wl,--start-group",
        //"-lc",
        //"-lm",
        //"-Wl,--end-group",
        //"-Wl,-cref,-u,Reset_Handler",
        */
    ]

    // Настройка запуска преобразователя и компилятора
    // http://habrahabr.ru/post/258467/
    // https://devzone.nordicsemi.com/question/24109/st-link-nrf51822-and-qt-creator/

}
