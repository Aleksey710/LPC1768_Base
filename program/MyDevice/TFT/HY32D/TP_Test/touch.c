//================================= 
void touch_Init(void)
{
    touch_CS=1;
    touch_DCLK=1;
    touch_DIN=1;
}
//================================= 
static unsigned short RD_AD(void) 
{
	uint temp=0;
    uchar i;
    touch_DIN=0;
    touch_DCLK=1;
    for(i=0;i<12;i++) 
    {
        touch_DCLK=0;         
 		temp<<=1;
        if(touch_DOUT==1) temp++;
        touch_DCLK=1;
    }
    touch_CS=1;
    return(temp);
}
//================================= 
uint read_trouch (unsigned char cmd) 
{
    unsigned char i;
    touch_CS=1;
    touch_DIN=0;
    touch_DCLK=0;
    touch_CS=0;
    for(i=0;i<8;i++) 
    {
        if(cmd&0x80)touch_DIN=1;
        else touch_DIN=0;
        cmd=cmd<<1;
        touch_DCLK=1;
        touch_DCLK=0;
    }
	return RD_AD();
}
//================================= 
 void touch_GetAdXY(uint *x,uint *y) 
{
    *x=read_trouch(CHX);
    *y=read_trouch(CHY);
}





