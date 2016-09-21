/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

// CMCSIS lib is used for definitions pin names
#include "lpc17xx_gpio.h"

// On this board LCD connected to MCU via 8 => 16 bit converter
/*
 * -EN       => P0.19
 * -LE       => P0.20
 * -DIR      => P0.21
 * -CS       => P0.22
 * -RS       => P0.23
 * -WR       => P0.24
 * -RD       => P0.25
 * -DB[0:7]  => P2.0 .. P2.7
 * -DB[8:15] => P2.0 .. P2.7
 */

#define PIN_EN		(1 << 19)
#define PIN_LE		(1 << 20)
#define PIN_DIR		(1 << 21)
#define PIN_CS          (1 << 22)
#define PIN_RS		(1 << 23)
#define PIN_WR		(1 << 24)
#define PIN_RD		(1 << 25)

//struct GDisplay {
//    int board;
//    int controllerdisplay;
//};

// объявление структуры
//struct GDisplay *g;// = maloc(GDisplay) ;


//#define int GDisplay
#define bool bool_t

// Pin EN setting to 0 or 1
#define LCD_EN(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_EN) : (LPC_GPIO0->FIOCLR = PIN_EN));
// Pin LE setting to 0 or 1
#define LCD_LE(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_LE) : (LPC_GPIO0->FIOCLR = PIN_LE));
// Pin DIR setting to 0 or 1
#define LCD_DIR(x)  ((x) ? (LPC_GPIO0->FIOSET = PIN_DIR) : (LPC_GPIO0->FIOCLR = PIN_DIR));
// Pin CS setting to 0 or 1
#define LCD_CS(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_CS) : (LPC_GPIO0->FIOCLR = PIN_CS));
// Pin RS setting to 0 or 1
#define LCD_RS(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_RS) : (LPC_GPIO0->FIOCLR = PIN_RS));
// Pin WR setting to 0 or 1
#define LCD_WR(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_WR) : (LPC_GPIO0->FIOCLR = PIN_WR));
// Pin RD setting to 0 or 1
#define LCD_RD(x)   ((x) ? (LPC_GPIO0->FIOSET = PIN_RD) : (LPC_GPIO0->FIOCLR = PIN_RD));

// Internal functions 
static inline void lcd_send(uint16_t byte)
{
    LPC_GPIO2->FIODIR |= 0x000000ff;  //P2.0...P2.7 Output
    LCD_DIR(1)                        //Interface A->B
    LCD_EN(0)                         //Enable 2A->2B
    LPC_GPIO2->FIOPIN =  byte;        //Write D0..D7
    LCD_LE(1)
    LCD_LE(0)                         //latch D0..D7
    LPC_GPIO2->FIOPIN =  byte >> 8;   //Write D8..D15 
}

static inline uint16_t lcd_read(void)
{
    uint16_t data;
    LPC_GPIO2->FIODIR &= 0xffffff00;                    //P2.0...P2.7 Input
    LCD_DIR(0)                                          //Interface B->A
    LCD_EN(0)                                           //Enable 2B->2A
    data = LPC_GPIO2->FIOPIN & 0x00ff;                  //Read D8..D15                         
    LCD_EN(1)                                           //Enable 1B->1A
    __asm volatile ("nop \n");                          //FIXME: delay 80 something
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    __asm volatile ("nop \n");
    data = (data << 8) | (LPC_GPIO2->FIOPIN & 0x00ff);  //Read D0..D7                         
    LCD_DIR(1)
    return(data);
}

// External (inreface) functions
/*
static inline void init_board(GDisplay *g)
{

	// As we are not using multiple displays we set g->board to NULL as we don't use it.
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:											// Set up for Display 0
		GPIO_SetDir(0, 0x03F80000, 1);              // Set control pins to Output
		break;
	}
}

static inline void post_init_board(GDisplay *g)
{
	(void) g;
}

static inline void setpin_reset(GDisplay *g, bool_t state)
{
	(void) g;
	(void) state;

        // Nothing to do here - reset pin tied to Vcc
}

static inline void set_backlight(GDisplay *g, uint8_t percent)
{
	(void) g;
	(void) percent;

        // Nothing to do here - Backlight always on
}

static inline void acquire_bus(GDisplay *g)
{
	(void) g;
}

static inline void release_bus(GDisplay *g)
{
	(void) g;
}

static inline void write_index(GDisplay *g, uint16_t index)
{
	(void) g;

    LCD_RS(0)
    LCD_RD(1)
    lcd_send(c);
    LCD_WR(0)
    __asm volatile ("nop \n");
    LCD_WR(1)
}

static inline void write_data(GDisplay *g, uint16_t data)
{
	(void) g;

    LCD_RS(1)
    LCD_RD(1)
    lcd_send(c);
    LCD_WR(0)
    __asm volatile ("nop \n");
    LCD_WR(1)
}

static inline void setreadmode(GDisplay *g)
{
	(void) g;
}

static inline void setwritemode(GDisplay *g)
{
	(void) g;
}

static inline uint16_t read_data(GDisplay *g) 
{
    (void) g;
    uint16_t val = 0;
    LCD_RS(1)
    LCD_WR(1)
    LCD_RD(0)
    val = lcd_read();
    LCD_RD(1)
    return val;
}
*/
#if defined(GDISP_USE_DMA)
	#error "GDISP - SSD1289: The GPIO interface does not support DMA"
#endif

#endif /* _GDISP_LLD_BOARD_H */

