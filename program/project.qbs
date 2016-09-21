import qbs
//import LPCProduct
import LPCApplication
//import LPCLibrary
import qbs.FileInfo
import qbs.ModUtils

LPCApplication {
    // Объявления defines для компилятора
    cpp.defines: [
        //-----------------------
        // LPC17XX
        "CPU=cortex-m3",
        "OPTIM=0",
        "__RAM_MODE__=0",
        "LPC17xx",
        "LPC1768",
        "__USE_CMSIS",
        //------------------------------
        // semihosting
        // http://www.wolinlabs.com/blog/stm32f4.semihosting.html
        "_Min_Heap_Size=1000",
        "_Min_Stack_Size=100",
        // ---- gnu ----
        // ROM
        //rom: AFLAGS += --defsym RAM_MODE=0
        //rom: CFLAGS += -D__RAM_MODE__=0
        //"__RAM_MODE__=0",
        // RAM
        //ram: AFLAGS += --defsym RAM_MODE=1
        //ram: CFLAGS += -D__RAM_MODE__=1
        //"RAM_MODE=1",
        // Following used for Chip Revision V00 only! --------------------------------------
        //"LPC17XX_REV00=1",
        // RAM_V00
        //ram_v00: AFLAGS += --defsym RAM_MODE=1
        //ram_v00: CFLAGS += -D__RAM_MODE__=1 -D__LPC17XX_REV00=1
        //"RAM_MODE=1",
        // ROM_V00
        //rom_v00: AFLAGS += --defsym RAM_MODE=0
        //rom_v00: CFLAGS += -D__RAM_MODE__=0 -D__LPC17XX_REV00=1
        //"RAM_MODE=0",

    ]

    cpp.includePaths: [
        //-----------------------------------------------------------------
        "./Core/mbed",
        "./Core/CMSIS/Include",
        "./Core/Device/NXP/LPC17xx/",
        //-----------------------------------------------------------------
        "./Drivers/include",
        //-----------------------------------------------------------------
        "./MyDevice/uIP",
        "./MyDevice/uIP/lpc17xx_port",
        "./MyDevice/uIP/uip",
        "./MyDevice/uIP/apps",
        "./MyDevice/uIP/apps/webserver",
        "./MyDevice/uIP/apps/webserver/httpd-fs",
        "./MyDevice/uIP/apps/dhcpc",
        //-----------------------------------------------------------------
        // for default FreeRTOSConfig.h
        "./MyDevice",
        //-----------------------------------------------------------------
        "./FreeRTOS/TestTask/include",
        //-----------------------------------------------------------------
        "./FreeRTOS/8.2.2/include",
        "./FreeRTOS/8.2.2/portable/MemMang",
        "./FreeRTOS/8.2.2/portable/GCC/ARM_CM3",
        "./FreeRTOS/8.2.2/portable/GCC/ARM_CM3_MPU",
        "./FreeRTOS/8.2.2/portable/GCC/ARM_CM4F",
        "./FreeRTOS/8.2.2/portable/GCC/ARM_CM7",
        //-----------------------------------------------------------------
    ]

    //==========================================================================================

    Group {
        name: "Core"

        prefix: "./Core"
        files: [
            //"/mbed/**",
            //---------------------------
            "/CMSIS/Include/**",
            //---------------------------
            // Рабочий
            "/Device/NXP/LPC17xx/system_LPC17xx.c",
            "/Device/NXP/LPC17xx/startup_LPC17xx.s",
            "/Device/NXP/LPC17xx/LPC17xx.h",
            //---------------------------
            //"/Device/NXP/LPC17xx/startup_LPC17xx.s",
            //---------------------------
            // Пример Keil LCD
            //"/Device/NXP/LPC17xx/LCDsystem_LPC17xx.c",
            //"/Device/NXP/LPC17xx/LCDstartup_LPC17xx.s",
            //---------------------------
            // Пример Rowley FreeRTOS
            //"/Device/NXP/LPC17xx/FreeRTOS_RedSuite/**",
            //"/Device/NXP/LPC17xx/LPC1700_Startup.s",
        ]

        // Исключить файлы из группы
        excludeFiles: [
            //---------------------------
            // Рабочий
            //"/Device/NXP/LPC17xx/system_LPC17xx.c",
            //"/Device/NXP/LPC17xx/startup_LPC17xx.s",
            //---------------------------
            // Пример Keil LCD
            //"/Device/NXP/LPC17xx/LCDsystem_LPC17xx.c",
            //"/Device/NXP/LPC17xx/LCDstartup_LPC17xx.s",
            //---------------------------
            // Пример Rowley FreeRTOS
            //"/Device/NXP/LPC17xx/LPC1700_Startup.s",
        ]
    }

    //==========================================================================================
/*
    Group {
        name: "DSP_Lib"

        prefix: "./Core/CMSIS/DSP_Lib"
        files: [
            "/**",
        ]

        // Исключить файлы из группы
        excludeFiles: [
            "/Examples/arm_class_marks_example/**",
            "/Examples/arm_convolution_example/**",
            "/Examples/arm_dotproduct_example/**",
            "/Examples/arm_fft_bin_example/**",
            "/Examples/arm_fir_example/**",
            "/Examples/arm_graphic_equalizer_example/**",
            "/Examples/arm_linear_interp_example/**",
            "/Examples/arm_matrix_example/**",
            "/Examples/arm_signal_converge_example/**",
            "/Examples/arm_sin_cos_example/**",
            "/Examples/arm_variance_example/**",
            "/Source/ARM/**",
            "/Source/GCC/**",
        ]
    }
*/
    //==========================================================================================

    Group {
        name: "Drivers"

        prefix: "./Drivers"
        files: [
            "/**",
            //"/include/lpc17xx_gpio.h",
            //"/source/lpc17xx_gpio.c",
        ]

        // Исключить файлы из группы
        excludeFiles: [
            "/include/lpc17xx_libcfg_default.h",
            "/source/lpc17xx_libcfg_default.c",
        ]
    }
    //==========================================================================================

    Group {
        name: "SystemDebug"

        prefix: "./SystemDebug"
        files: [
            "/**",
        ]

        // Исключить файлы из группы
        excludeFiles: [

        ]
    }
    //==========================================================================================

    Group {
        name: "uIP"

        prefix: "./uIP"
        files: [
            "/**",
        ]

        // Исключить файлы из группы
        excludeFiles: [

        ]
    }
    //==========================================================================================

    Group {
        name: "FreeRTOS"

        prefix: "./FreeRTOS/8.2.2/"
        files: [
            "/**",
            "../TestTask/**",
            "../pack_struct.h",
        ]

        // Исключить файлы из группы
        excludeFiles: [
            "portable/MemMang/heap_1.c",
            "portable/MemMang/heap_2.c",
            "portable/MemMang/heap_3.c",
            //"portable/MemMang/heap_4.c",
            "portable/MemMang/heap_5.c",
            //------------------------------------
            "portable/GCC/ARM_CM0/**",
            //"/8.2.2/portable/GCC/ARM_CM3/**",
            "portable/GCC/ARM_CM3_MPU/**",
            "portable/GCC/ARM_CM4F/**",
            "portable/GCC/ARM_CM7/**",
            //------------------------------------
            //"../TestTask/Minimal/**",
            "../TestTask/Minimal/TimerDemo.c",
            "../TestTask/Minimal/IntQueueTimer.c",
            "../TestTask/Minimal/IntQueue.c",
            "../TestTask/Minimal/EventGroupsDemo.c",
            "../TestTask/Minimal/comtest_strings.c",
            "../TestTask/Minimal/flop.c",
            "../TestTask/Minimal/sp_flop.c",
            "../TestTask/Minimal/crhook.c",
            //------------------------------------
            "../TestTask/Full/**",
        ]
    }


    //==========================================================================================
    Group {
        name: "MyDevice"

        prefix: "./MyDevice"
        files: [
            "/**",
        ]

        // Исключить файлы из группы
        excludeFiles: [
            "/FreeRTOSConfig.h",
            //-----------------------------
            "/Test/**",
            "/Blinky/**",
            "/Easy_Web/**",
            "/GLCD/**",
            "/GLCD/board_SSD1289.h",
            "/uIP/**",
            "/TFT/**",
            "/LCD_Blinky/**",
            "/LCD_Blinky/Flash/**",
            "/LCD_Blinky/core_cm3.c",
            "/LCD_Blinky/system_LPC17xx.c",
            "/LCD_Blinky/startup_LPC17xx.s",
            "/LCD_Blinky/GLCD_SPI_LPC1700.c",
            "/LCD_Blinky/GLCD_p.c",
//            "/LCD_Blinky/Flash/system_LPC17xx.s",
//            "/LCD_Blinky/Flash/system_LPC17xx.s",

            //"/FreeRTOS_RedSuite/**",

            "/FreeRTOS_RedSuite/test/**",

            //"/FreeRTOS_RedSuite/webserver/**",
            //"/FreeRTOS_RedSuite/LPCUSB/**",

            "/FreeRTOS_Rowley/**",
            //"/FreeRTOS_Rowley/test/**",
        ]
    }

    //==========================================================================================

    Group {
        name: "ldscripts"
        prefix: "../ldscripts/"
        files: [
            // рабочий
            //"gcc_arm.ld",
            //------------------------------------------------------
            // Define Required Linker script file in each build mode
            //"example/ldscript_ram_gnu.ld",
            //"example/ldscript_rom_gnu.ld",
            //------------------------------------------------------
            // Following used for Chip Revision V00 only
            //"example/ldscript_ram_v00_gnu.ld",
            //"example/ldscript_rom_v00_gnu.ld",
            //------------------------------------------------------
            "rtosdemo_rdb1768_Debug.ld",
        ]
        // Исключить файлы из группы
        excludeFiles: [
            "common/**",
            "example/**",
            "LPC17xx/**",
        ]
    }

    //особенно интересный момент: скрипты линковщика, описывают структуру бинарника, секции, и так далее
    cpp.linkerScripts: [
        //"../ldscripts/example/ldscript_ram_gnu.ld",
        //"../ldscripts/example/ldscript_rom_gnu.ld",
        //"../ldscripts/gcc_arm.ld",
        "../ldscripts/rtosdemo_rdb1768_Debug.ld",
    ]
}
