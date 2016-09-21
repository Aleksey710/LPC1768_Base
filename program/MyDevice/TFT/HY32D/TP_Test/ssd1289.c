

//=================================
void send_command(uint out_data)              
{
RS=0;
DATA_H=out_data>>8;
DATA_L=out_data;
RW=0;
CS=0;
RW=1;
CS=1;
}
//=================================
void send_data(uint out_data)           
{
RS=1;
CS=0;
DATA_H=out_data>>8;
DATA_L=out_data;
RW=0;
RW=1;
CS=1;
}
/*
//=================================
uint rece_command(void)              
{
uint i;
RS=0;
DATA_H=0xff;
DATA_L=0xff;

CS=0;
rd=0;
i=(uint)DATA_H<<8+DATA_L;
rd=1;
CS=1;
return i;
}			*/
//=================================
/*
uint rece_data(void)              
{
uint i;
RS=1;
DATA_H=0xff;
DATA_L=0xff;
CS=0;
rd=0;
i=DATA_H;
i<<=8;
i|=DATA_L;
rd=1;
CS=1;
return i;
}*/
//=================================
void write_com(uint address,uint num)
{
    send_command(address);
    send_data(num);
}
//=================================  
/*
Display Type:4
BPP setting:3
USB Speed:2
Bus Mode:1
Seg:240
Com:320
interval:0000
*/   
void ssd1289_init(void)
{

    write_com(0x0000,0x0001);    DelayNS(1000);  //打开晶振
    write_com(0x0003,0xA8A4);    DelayNS(1000);   //0xA8A4
    write_com(0x000C,0x0000);    DelayNS(1000);   
    write_com(0x000D,0x080C);    DelayNS(1000);   
    write_com(0x000E,0x2B00);    DelayNS(1000);   
    write_com(0x001E,0x00B0);    DelayNS(1000);   
    write_com(0x0001,0x2B3F);    DelayNS(1000);   //驱动输出控制320*240  0x6B3F
    write_com(0x0002,0x0600);    DelayNS(1000);
    write_com(0x0010,0x0000);    DelayNS(1000);
    write_com(0x0011,0x6070);    DelayNS(1000);        //0x4030           //定义数据格式  16位色 
    write_com(0x0005,0x0000);    DelayNS(1000);
    write_com(0x0006,0x0000);    DelayNS(1000);
    write_com(0x0016,0xEF1C);    DelayNS(1000);
    write_com(0x0017,0x0003);    DelayNS(1000);
    write_com(0x0007,0x0233);    DelayNS(1000);        //0x0233       
    write_com(0x000B,0x0000);    DelayNS(1000);
    write_com(0x000F,0x0000);    DelayNS(1000);        //扫描开始地址
    write_com(0x0041,0x0000);    DelayNS(1000);
    write_com(0x0042,0x0000);    DelayNS(1000);
    write_com(0x0048,0x0000);    DelayNS(1000);
    write_com(0x0049,0x013F);    DelayNS(1000);
    write_com(0x004A,0x0000);    DelayNS(1000);
    write_com(0x004B,0x0000);    DelayNS(1000);
    write_com(0x0044,0xEF00);    DelayNS(1000);
    write_com(0x0045,0x0000);    DelayNS(1000);
    write_com(0x0046,0x013F);    DelayNS(1000);
    write_com(0x0030,0x0707);    DelayNS(1000);
    write_com(0x0031,0x0204);    DelayNS(1000);
    write_com(0x0032,0x0204);    DelayNS(1000);
    write_com(0x0033,0x0502);    DelayNS(1000);
    write_com(0x0034,0x0507);    DelayNS(1000);
    write_com(0x0035,0x0204);    DelayNS(1000);
    write_com(0x0036,0x0204);    DelayNS(1000);
    write_com(0x0037,0x0502);    DelayNS(1000);
    write_com(0x003A,0x0302);    DelayNS(1000);
    write_com(0x003B,0x0302);    DelayNS(1000);
    write_com(0x0023,0x0000);    DelayNS(1000);
    write_com(0x0024,0x0000);    DelayNS(1000);
    write_com(0x0025,0x8000);    DelayNS(1000);
    write_com(0x004f,0);        //行首址0
    write_com(0x004e,0);        //列首址0
}

/**************************************************************************************
* 名    称: DispOneColor
* 功    能: 全屏显示某种颜色
* 参    数: Color   : 颜色值
* 返 回 值: 无
*
* 修改历史:
*   版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*   1.0   2007.6.13  lcf       基本的功能完成
**************************************************************************************/
void DispOneColor(uint Color)
{
    int i,j;
    write_com(0x004f,0);        //行首址0
    write_com(0x004e,0);        //列首址0
    send_command(0x22);
    for(j=0;j<320;j++)
        for(i=0;i<240;i++)
            send_data(Color);
}
/**************************************************************************************
* 名    称: DispClear
* 功    能: 清除显示屏的显示内容
* 参    数: 无
* 返 回 值: 无
*
* 修改历史:
*   版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*   1.0   2006.8.13  lcf       基本的功能完成
**************************************************************************************/
void DispClear(void)
{
    DispOneColor(BLUE);
}
//==============================================
void Set_ramaddr(uint x,uint y)
{
    write_com(0x004f,y);        //行首址
	write_com(0x004e,x);        //列首址
}/**************************************************************************************
* 名    称: DrawSingleAscii
* 功    能: 在指定的位置单个字符
* 参    数: x           : x坐标
*           y           : y坐标
*           LineColor   : 字符的颜色
*           FillColor   : 字符背景颜色
* 返 回 值: 无
*
* 修改历史:
*   版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*   1.0   2007.6.13  lcf       基本的功能完成
**************************************************************************************/

void DrawSingleAscii(uint x, uint y, uchar *pAscii, uint LineColor,uint FillColor, uchar Mod)
{
    uchar i, j;
    uchar str;
    uint OffSet;

    OffSet = (*pAscii - 32)*16;

    for (i=0;i<16;i++)
    {
        Set_ramaddr(x,y+i);
        send_command(0x22);
        str = *(AsciiLib + OffSet + i);  
        for (j=0;j<8;j++)
        {
            if ( str & (0x80>>j) )     //0x80>>j
            {
                send_data((uint)(LineColor&0xffff));
            }
            else
            {
                if (NORMAL == Mod) 
                    send_data((uint)(FillColor&0xffff));
                else
                {
                    Set_ramaddr(x+j+1,y+i);
                    send_command(0x22);  
                }
            }               
        } 
    }
}
/**************************************************************************************
* 名    称: DrawSingleHz
* 功    能: 在指定的位置显示汉字
* 参    数: x           : x坐标
*                       y       : y坐标
*               LineColor : 汉字的颜色
*           FillColor   : 汉字背景颜色
* 返 回 值: 无
*
* 修改历史:
*   版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*   1.0   2007.6.13  lcf       基本的功能完成
**************************************************************************************/

void DrawSingleHz(uint x, uint y, uchar *pHz, uint LineColor,uint FillColor, uchar Mod)
{
uint j=0,i=0,k=0;
uint str,len;
//---------------------------统计是否在字库中出现 
len=sizeof(HzLib)/sizeof(HzLib[0]);
for(j=0;j<sizeof(HzLib)/sizeof(HzLib[0]);j++)   
    if((uchar)HzLib[j].Index[0]==pHz[0]&&(uchar)HzLib[j].Index[1]==pHz[1])break;
//--------------------------      
    if(j<len)
    {
        for (i=0;i<HZ_column;i++)
        {
            Set_ramaddr(x,y+i);
            send_command(0x22);

            str = (uchar)HzLib[j].Msk[i*2]<<8|(uchar)HzLib[j].Msk[i*2+1]; 

            for (k=0;k<HZ_column;k++)
            {
                if ( str & (0x8000>>k) )     //0x8000>>k
                {
                    send_data((uint)(LineColor&0xffff));
                }
                else
                {
                    if (NORMAL == Mod) 
                        send_data((uint)(FillColor&0xffff));
                    else
                    {
                        Set_ramaddr(x+k+1,y+i);
                        send_command(0x22);  
                    }
                }               
            } 
        }
    }
}

/**************************************************************************************
* 名    称: DrawString
* 功    能: 在指定的位置显示多个字符
* 参    数: x           : x坐标
*                       y         : y坐标
*               LineColor : 字符的颜色
*           FillColor   : 字符背景颜色
* 返 回 值: 无
*
* 修改历史:
*   版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*   1.0   2007.6.13  lcf       基本的功能完成
**************************************************************************************/

void DrawString(uint x, uint y, uchar *pStr, uint LineColor,uint FillColor, uchar Mod)
{

    while(1)
    {
        if (*pStr == 0)
        {
            return;
        }

        if (*pStr > 0x80)           //汉字
        {
            DrawSingleHz(x, y, pStr, LineColor, FillColor, Mod);
            x += HZ_column;
            pStr += 2;              
        }
        else                        //英文字符
        {
            DrawSingleAscii(x, y, pStr, LineColor, FillColor, Mod);
            x += 8;
            pStr += 1;              
        }
    }   
}
//================================= 

void DispNum(unsigned int x, unsigned int y, unsigned short num)
{
    unsigned char str[5];

    str[0] = num/1000+0x30;
    str[1] = (num%1000)/100+0x30;
    str[2] = (num%1000)%100/10+0x30;
    str[3] = (num%1000)%100%10+0x30;
    str[4] = '\0';

    DrawString(x, y, str, BLACK, YELLOW, NORMAL);
}
/**************************************************************************************
* 名    称: DispSmallPic
* 功    能: 在指定的位置显示一张65K色的图片
* 参    数: str     : 图片数组名
* 返 回 值: 无
*
* 修改历史:
*   版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*   1.0   2007.6.13  lcf       基本的功能完成
**************************************************************************************/
/*
void DispSmallPic(uint x, uint y, uint w, uint h, const uchar *str)
{
    uint i,j,temp;
    for(j=0;j<h;j++)
    {
        Set_ramaddr(x,y+j);
        send_command(0x22); 
        for(i=0;i<w;i++)
        {   //send_data(*(unsigned short *)(&str[(j*w+i)*2]));       //高位在前
            temp=str[(j*w+i)*2+1]<<8;     //低位在前
            temp|=str[(j*w+i)*2];
            send_data(temp);
        }
    }
}*/

