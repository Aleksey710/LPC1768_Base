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

#define TRANSP  1           //字体显示的时候不带背景颜色
#define NORMAL  0           //字体显示的时候有背景颜色

sbit RS=P1^0;
sbit rd=P1^1;
sbit res=P1^2; 
sbit RW=P1^3; 
sbit CS=P1^4; 

#define	HZ_column  16 //汉字字体大小
#define DATA_H  P2     
#define DATA_L  P0  
//==========================TOUCH DEFINE
sbit touch_CS=P1^5;
sbit touch_DCLK=P1^6;
sbit touch_DIN=P1^7; 
sbit touch_INT=P3^2; 
sbit touch_DOUT=P3^3; 
sbit touch_BUSY=P3^4;

// A/D 通道选择命令字和工作寄存器
#define CHX     0x90    //通道Y+的选择控制字    
#define CHY     0xD0    //通道X+的选择控制字 




//=================================
void DelayNS(uint time)                
{
    while(time--!=0); 
}