/*  The fault handler implementation calls a function called
    prvGetRegistersFromStack().
*/
#ifdef HardFault_Handler_ASM

static void HardFault_Handler(void)
{
    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}
#else
/*
// From Joseph Yiu, minor edits by FVH
// hard fault handler in C,
// with stack frame location as input parameter
// called from HardFault_Handler in file xxx.s
void HardFault_Handler (unsigned int * hardfault_args)
{
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;

    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);

    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

//    printf ("\n\n[Hard fault handler - all numbers in hex]\n");
//    printf ("R0 = %x\n", stacked_r0);
//    printf ("R1 = %x\n", stacked_r1);
//    printf ("R2 = %x\n", stacked_r2);
//    printf ("R3 = %x\n", stacked_r3);
//    printf ("R12 = %x\n", stacked_r12);
//    printf ("LR [R14] = %x  subroutine call return address\n", stacked_lr);
//    printf ("PC [R15] = %x  program counter\n", stacked_pc);
//    printf ("PSR = %x\n", stacked_psr);
//    printf ("BFAR = %x\n", (*((volatile unsigned long *)(0xE000ED38))));
//    printf ("CFSR = %x\n", (*((volatile unsigned long *)(0xE000ED28))));
//    printf ("HFSR = %x\n", (*((volatile unsigned long *)(0xE000ED2C))));
//    printf ("DFSR = %x\n", (*((volatile unsigned long *)(0xE000ED30))));
//    printf ("AFSR = %x\n", (*((volatile unsigned long *)(0xE000ED3C))));
    //printf ("SCB_SHCSR = %x\n", SCB->SHCSR);

    //while (1);
}
*/
static void HardFault_Handler( void ) __attribute__( ( naked ) );

/* The fault handler implementation calls a function called
prvGetRegistersFromStack(). */
static void HardFault_Handler(void)
{
    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}

//void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
void prvGetRegistersFromStack( unsigned int *pulFaultStackAddress )
{
    volatile unsigned int r0;
    volatile unsigned int r1;
    volatile unsigned int r2;
    volatile unsigned int r3;
    volatile unsigned int r12;
    volatile unsigned int lr; /* Link register. */
    volatile unsigned int pc; /* Program counter. */
    volatile unsigned int psr;/* Program status register. */

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];
    pc = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}


#endif
