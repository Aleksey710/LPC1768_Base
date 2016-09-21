//======================================================
#define uchar unsigned char 
#define uint unsigned int
//==========================LCD DEFINE
#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW   0xFFE0

#define TRANSP  1           //ЧЦМеПФКѕµДК±єтІ»ґш±іѕ°СХЙ«
#define NORMAL  0           //ЧЦМеПФКѕµДК±єтУР±іѕ°СХЙ«

sbit RS=P1^0;
sbit rd=P1^1;
sbit res=P1^2; 
sbit RW=P1^3; 
sbit CS=P1^4; 

#define	HZ_column  16 //єєЧЦЧЦМеґуРЎ
#define DATA_H  P2     
#define DATA_L  P0  
//==========================TOUCH DEFINE
sbit touch_CS=P1^5;
sbit touch_DCLK=P1^6;
sbit touch_DIN=P1^7; 
sbit touch_INT=P3^2; 
sbit touch_DOUT=P3^3; 
sbit touch_BUSY=P3^4;

// A/D НЁµАСЎФсГьБоЧЦєН№¤ЧчјДґжЖч
#define CHX     0x90    //НЁµАY+µДСЎФсїШЦЖЧЦ    
#define CHY     0xD0    //НЁµАX+µДСЎФсїШЦЖЧЦ 




//=================================
void DelayNS(uint time)                
{
    while(time--!=0); 
}