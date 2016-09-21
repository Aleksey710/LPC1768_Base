#include <reg52.h>
//#include<stdio.h>
#include<define.h>
#include<asc_zimo.h>
#include<Hz_zimo.h>
//#include<pic.h>
#include<ssd1289.c>
#include<touch.c>

//=================================   
main()
{
    uint T_x = 3;
    uint T_y = 4;
    uchar R_data=0;
	uchar G_data=0;
	uchar B_data=0;
  //  uint i,j,k=0;
    res=0;      //低电平复位
    DelayNS(1000);
    res=1;
 //   send_command(0x00);
 //   i=rece_data();
    DelayNS(10000);//等待电源恢复正常
    ssd1289_init();
    touch_Init();
    DispClear();        
    send_command(0x22);
//	DispSmallPic(0, 0, 101, 103, pic2);
	DrawString(84, 0, "触摸测试:", WHITE, RED, NORMAL);
 //   DrawString(0, 152, "Easy Do It!!", RED, YELLOW, NORMAL);
//	DrawString(0, 168, "支持各种单片机", RED,YELLOW,TRANSP);
//	DrawString(0, 184, "提供Keil C51演示程序",YELLOW,RED,NORMAL);
 //   DispSmallPic(148, 0, 92, 175, pic);
	//==============================  
 //	Set_ramaddr(0,200);
//	send_command(0x22);
 /*	R_data=0;G_data=0;B_data=0;  	
    for(j=0;j<20;j++)//红色渐强条
	{
        for(i=0;i<240;i++)
            {R_data=i/8;send_data(R_data<<11|G_data<<5|B_data);}
	}
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<20;j++)
	{
        for(i=0;i<240;i++)
            {
			G_data=0x3f-(i/4);
			B_data=0x1f-(i/8);
			send_data(R_data<<11|G_data<<5|B_data);}
	}
//----------------------------------
	R_data=0;G_data=0;B_data=0;
    for(j=0;j<20;j++)//绿色渐强条
	{
        for(i=0;i<240;i++)
            {G_data=i/4;send_data(R_data<<11|G_data<<5|B_data);}
	}
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<20;j++)
	{
        for(i=0;i<240;i++)
            {
			R_data=0x1f-(i/8);
			B_data=0x1f-(i/8);
			send_data(R_data<<11|G_data<<5|B_data);}
	}
//----------------------------------
	R_data=0;G_data=0;B_data=0;
    for(j=0;j<20;j++)//蓝色渐强条
	{
        for(i=0;i<240;i++)
            {B_data=i/8;send_data(R_data<<11|G_data<<5|B_data);}
	} 
	B_data=0; 
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<20;j++)
	{
        for(i=0;i<240;i++)
            {
			G_data=0x3f-(i/4);
			R_data=0x1f-(i/8);
			send_data(R_data<<11|G_data<<5|B_data);}
	}
 //==============================   */             
	while(1)
    {   
        if (touch_INT==0)
        {
            touch_GetAdXY(&T_x, &T_y);
            DispNum(104, 20, T_x);
            DispNum(104, 40, T_y);
        }
    }
}

