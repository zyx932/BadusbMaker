#ifndef __BADUSB_H__
#define __BADUSB_H__

#include <STC15F104E.h>
#include "keymap.h"
//#include <intrins.h>

#define TX P31
//#define nil 0x00
typedef unsigned char u8;
u8 cunt_key=0;
u8 cunt_ctl=0;
u8 keys[6]={0x00,0x00,0x00,0x00,0x00,0x00};
u8 ctls=0x00;
// Function Prototypes
void Key_Init();
void HandleTimerZero();
void delay_104us();
void send_data(u8 datas);
void press_key(u8 key);
void press_ctl(u8 key);
void free_all();

void prepare_key(u8 key);
void prepare_ctl(u8 key);
void press_all();
bit flag = 0;

//------------------------------------------------------------------------
void prepare_key(u8 key){
	keys[cunt_key]=key;
	cunt_key+=1;
}
void prepare_ctl(u8 key){
	if (key == KB_CTRL) {
		ctls |= 0x01; // 0000 0001
	}
	if (key == KB_SHIFT) {
		ctls |= 0x02; // 0000 0010
	}
	if (key == KB_ALT) {
		ctls |= 0x04; // 0000 0100
	}
	if (key == KB_GUI) {
		ctls |= 0x08; // 0000 1000
	}
	if (key == KB_CTRL_R) {
		ctls |= 0x10; // 0001 0000
	}
	if (key == KB_SHIFT_R) {
		ctls |= 0x20; // 0010 0000
	}
	if (key == KB_ALT_R) {
		ctls |= 0x40; // 0100 0000
	}
	if (key == KB_GUI_R) {
		ctls |= 0x80; // 1000 0000
	}
}
void press_all(){
	u8 i;
	send_data(ctls);
	send_data(0x00);
	for (i=0;i<6;i++){
		send_data(keys[i]);
		keys[i]=0x00;//reset
	}
	cunt_key=0;//reset
	cunt_ctl=0;//reset
	//keys={0x00,0x00,0x00,0x00,0x00,0x00};//reset
	ctls=0x00;//reset
}
void press_ctl(u8 key){
	u8 i;
	u8 tmp = 0x00;
	if (key == KB_CTRL) {
		tmp |= 0x01; // 0000 0001
	}
	if (key == KB_SHIFT) {
		tmp |= 0x02; // 0000 0010
	}
	if (key == KB_ALT) {
		tmp |= 0x04; // 0000 0100
	}
	if (key == KB_GUI) {
		tmp |= 0x08; // 0000 1000
	}
	if (key == KB_CTRL_R) {
		tmp |= 0x10; // 0001 0000
	}
	if (key == KB_SHIFT_R) {
		tmp |= 0x20; // 0010 0000
	}
	if (key == KB_ALT_R) {
		tmp |= 0x40; // 0100 0000
	}
	if (key == KB_GUI_R) {
		tmp |= 0x80; // 1000 0000
	}
	send_data(tmp);
	for (i = 0; i < 7; i++) {
		send_data(0x00);
	}
}

void free_all(){
	u8 i;
	for (i=0;i<8;i++){
		send_data(0x00);
	}
}

void press_key(u8 key){
	u8 i;
	for (i=0;i<8;i++){
		if(i==4){
			send_data(key);
		}else{
			send_data(0x00);
		}
	}
}
//-------------------------------------------------------------------------
void Key_Init(){
	EA=1;
	ET0=1;
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x82;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
}
void delay_104us(){
	TR0=1;
	while(!flag);
	flag=0;
}
void HandleTimerZero() interrupt 1{
	TL0 = 0x82;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
	flag=1;
}
void send_data(u8 datas){
	int i;
	TX=0;
	delay_104us();
	for (i=0;i<8;i++){
		TX=(datas & 0x01);
		datas=datas>>1;
		delay_104us();
	}
	TX=1;
	delay_104us();
}

#endif // __BADUSB_H__