/*****************************************************************************/
/* startup_LPC17xx.s: Startup file for LPC17xx device series                 */
/*****************************************************************************/

/*
*** <<< Use Configuration Wizard in Context Menu >>> ***
*/
    .global   _Reset_Handler
    .type    _Reset_Handler, %function
    .global   Reset_Handler
    .type    Reset_Handler, %function


// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>

.syntax unified
    .arch armv7-m

    .section .stack,"w"
    .align 3
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
/*#ifdef __STACK_SIZE
    .space    __STACK_SIZE
#else
    .space    fasdsdf
#endif
*/
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
/*#ifdef __HEAP_SIZE
    .space    __HEAP_SIZE
#endif*/
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .vectors
    .align 2
    .globl __Vectors
    .type  __Vectors, %object

    .globl __isr_vector
    .type  __isr_vector, %object
    .globl g_pfnVectors
    .type  g_pfnVectors, %object
    .globl  __cs3_interrupt_vector_cortex_m
    .type   __cs3_interrupt_vector_cortex_m, %object

__cs3_interrupt_vector_cortex_m:/* code soursery */
g_pfnVectors:                   /* lpcexpresso */
__isr_vector:                   /* old cmsis */
__Vectors:                      /* new cmsis */
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */

    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   0                           /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
    .long   WDT_IRQHandler              /* 16: Watchdog Timer               */
    .long   TIMER0_IRQHandler           /* 17: Timer0                       */
    .long   TIMER1_IRQHandler           /* 18: Timer1                       */
    .long   TIMER2_IRQHandler           /* 19: Timer2                       */
    .long   TIMER3_IRQHandler           /* 20: Timer3                       */
    .long   UART0_IRQHandler            /* 21: UART0                        */
    .long   UART1_IRQHandler            /* 22: UART1                        */
    .long   UART2_IRQHandler            /* 23: UART2                        */
    .long   UART3_IRQHandler            /* 24: UART3                        */
    .long   PWM1_IRQHandler             /* 25: PWM1                         */
    .long   I2C0_IRQHandler             /* 26: I2C0                         */
    .long   I2C1_IRQHandler             /* 27: I2C1                         */
    .long   I2C2_IRQHandler             /* 28: I2C2                         */
    .long   SPI_IRQHandler              /* 29: SPI                          */
    .long   SSP0_IRQHandler             /* 30: SSP0                         */
    .long   SSP1_IRQHandler             /* 31: SSP1                         */
    .long   PLL0_IRQHandler             /* 32: PLL0 Lock (Main PLL)         */
    .long   RTC_IRQHandler              /* 33: Real Time Clock              */
    .long   EINT0_IRQHandler            /* 34: External Interrupt 0         */
    .long   EINT1_IRQHandler            /* 35: External Interrupt 1         */
    .long   EINT2_IRQHandler            /* 36: External Interrupt 2         */
    .long   EINT3_IRQHandler            /* 37: External Interrupt 3         */
    .long   ADC_IRQHandler              /* 38: A/D Converter                */
    .long   BOD_IRQHandler              /* 39: Brown-Out Detect             */
    .long   USB_IRQHandler              /* 40: USB                          */
    .long   CAN_IRQHandler              /* 41: CAN                          */
    .long   DMA_IRQHandler              /* 42: General Purpose DMA          */
    .long   I2S_IRQHandler              /* 43: I2S                          */
    .long   ENET_IRQHandler             /* 44: Ethernet                     */
    .long   RIT_IRQHandler              /* 45: Repetitive Interrupt Timer   */
    .long   MCPWM_IRQHandler            /* 46: Motor Control PWM            */
    .long   QEI_IRQHandler              /* 47: Quadrature Encoder Interface */
    .long   PLL1_IRQHandler             /* 48: PLL1 Lock (USB PLL)          */
    .long	USBActivity_IRQHandler		/* 49: USB Activity 				*/
    .long 	CANActivity_IRQHandler		/* 50: CAN Activity					*/

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb


/* Reset Handler */

    .thumb_func
    .align 2
    .global   _Reset_Handler
    .type    _Reset_Handler, %function
    .global   Reset_Handler
    .type    Reset_Handler, %function
    .global  __cs3_reset_cortex_m
    .type   __cs3_reset_cortex_m, %function
__cs3_reset_cortex_m:
Reset_Handler:
_Reset_Handler:
    .fnstart
.if (__RAM_MODE__)
.else
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */
    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

    subs    r3, r2
    ble    .flash_to_ram_loop_end

    movs    r4, 0
.flash_to_ram_loop:
    ldr    r0, [r1,r4]
    str    r0, [r2,r4]
    adds    r4, 4
    cmp    r4, r3
    blt    .flash_to_ram_loop
.flash_to_ram_loop_end:
.endif


/* Clear .bss section (Zero init) */
	movs    R0, 0
	LDR     R1, =__bss_start__
	LDR     R2, =__bss_end__
	CMP     R1,R2
	BEQ     BSSIsEmpty
LoopZI:
	CMP     R1, R2
	BHS	BSSIsEmpty
	STR   	R0, [R1]
	adds	R1, 4
	BLO     LoopZI
BSSIsEmpty:
#ifndef __NO_SYSTEM_INIT
	LDR     R0, =SystemInit
	BLX     R0
#endif
	LDR     R0,=main
	BX      R0

    .pool
    .fnend
    .size Reset_Handler, . - Reset_Handler

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    TST LR, #4
    ITE EQ
    MRSEQ R0, MSP
    MRSNE R0, PSP
    B HardFault_Handler
//    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
    B       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
    B       .
    .size   DebugMon_Handler, . - DebugMon_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  IRQ handler
    .align 1
    .thumb_func
    .weak   \handler
    .type    \handler, %function
\handler :
/*    b    .
    .size    \handler, . - \handler*/
    .endm

    IRQ     WDT_IRQHandler
    IRQ     TIMER0_IRQHandler
    IRQ     TIMER1_IRQHandler
    IRQ     TIMER2_IRQHandler
    IRQ     TIMER3_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     UART2_IRQHandler
    IRQ     UART3_IRQHandler
    IRQ     PWM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     I2C2_IRQHandler
    IRQ     SPI_IRQHandler
    IRQ     SSP0_IRQHandler
    IRQ     SSP1_IRQHandler
    IRQ     PLL0_IRQHandler
    IRQ     RTC_IRQHandler
    IRQ     EINT0_IRQHandler
    IRQ     EINT1_IRQHandler
    IRQ     EINT2_IRQHandler
    IRQ     EINT3_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     BOD_IRQHandler
    IRQ     USB_IRQHandler
    IRQ     CAN_IRQHandler
    IRQ     DMA_IRQHandler
    IRQ     I2S_IRQHandler
    IRQ     ENET_IRQHandler
    IRQ     RIT_IRQHandler
    IRQ     MCPWM_IRQHandler
    IRQ     QEI_IRQHandler
    IRQ     PLL1_IRQHandler
    IRQ		USBActivity_IRQHandler
    IRQ		CANActivity_IRQHandler

/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

    .end
