/******************************************************************************/
/* Blinky.c: LED Flasher and graphic demo                                     */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"

#include <stdlib.h>
#include <stdio.h>

#define DEBUG
#include "debug_frmwrk.h"

#define LED_NUM     8                   /* Number of user LEDs                */
const  unsigned long led_mask[] = { 1<<0, 1<<1, 1UL<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7 };

extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;
extern unsigned char Bg_16bpp_t[];
extern unsigned char Bg_16bpp_l[];
extern unsigned char Bg_16bpp_r[];
extern unsigned char Bg_16bpp_b[];
extern unsigned char ARM_Ani_16bpp[];

/* Main Program                       */
int main (void) {

    int num     = -1;
    int dir     =  1;
    int pic     =  0;
    LPC_GPIO_TypeDef *gpio = LPC_GPIO2;

    SystemInit();

    // Initialize debug via UART0
    debug_frmwrk_init();

    //Disable STDOUT buffering. Otherwise nothing will be printed before
    //a newline character or when the buffer is flushed. This MUST be done
    //before any writes to STDOUT to have any effect...
    //setbuf(stdout, NULL);
    //printf("Hello world\r\n");

    //_DBG("SystemInit() \n\r");

    // #include "system_LPC17xx.c"
    // Internal RC oscillator frequency
    // #define IRC_OSC     ( 4000000UL)
    // System Clock Frequency (Core Clock)
    uint32_t SystemFrequency = 4000000UL;

    SysTick_Config(SystemFrequency/100);  /* Generate interrupt every 10 ms     */

    //  LPC_GPIO1->FIODIR = 0xB0000000;       /* LEDs on PORT1 defined as Output    */
    //  LPC_GPIO2->FIODIR = 0x0000007C;       /* LEDs on PORT2 defined as Output    */

    GLCD_Init();

    _DBG("GLCD_Init() \n\r");

    //GLCD_Clear (White);
    GLCD_Clear (Green);

    _DBG("GLCD_Clear (Green) \n\r");

    GLCD_Bmp (  0,   0, 320,  69, Bg_16bpp_t+70);
    GLCD_Bmp (  0,  69,   4, 102, Bg_16bpp_l+70);
    GLCD_Bmp (316,  69,   4, 102, Bg_16bpp_r+70);
    GLCD_Bmp (  0, 171, 320,  69, Bg_16bpp_b+70);

    /* Loop forever                       */
    for (;;)
    {
        if (ClockANI)
        {
            ClockANI = 0;
            if (pic++ > 8)
                pic = 0;

            GLCD_Bmp (99, 99, 120, 45, &ARM_Ani_16bpp[pic*(120*45*2)]);
        }

        /* Blink LED every 1 second (for 0.5s)*/
        if (ClockLEDOn)
        {
            ClockLEDOn  = 0;

            /* Calculate 'num': 0,1,...,LED_NUM-1,LED_NUM-1,...,1,0,0,...           */
            num += dir;
            if (num == LED_NUM)
            {
                dir = -1;
                num =  LED_NUM-1;
            } else if   (num < 0)
            {
                dir =  1;
                num =  0;
            }

            gpio = LPC_GPIO2;
            gpio->FIOPIN |=  led_mask[num];
        }

        if (ClockLEDOff)
        {
            ClockLEDOff = 0;
            gpio->FIOPIN &= ~led_mask[num];
        }
    }
}

#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
        /* User can add his own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

        _DBG("Wrong parameters value: file %s on line %d\r\n \n\r");
        printf("Wrong parameters value: file %s on line %d\r\n", file, line);

        /* Infinite loop */
        while(1);
}
#endif

