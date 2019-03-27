#pragma once
#include "stdafx.h"
#include<iostream>
#include<Windows.h>//GetKeyState 
#include<thread>//线程真好用啊~//移动 鼠标 绘画 
#include <graphics.h>//EasyX库
#include<string>//文件路径 
#include <vector>//STL
#include"Tank's_struct.h"//Some_Thing

using namespace std;//用于测试时cout

//---------------各种声明-----------------


//以下函数不在类中
int Load_Image();
int Draw_Map(int, int, int*, int*, int);
int Draw_Tank(Some_Thing*, MOUSEMSG*);
int DRAW_Bomb(Some_Thing);
int Clean_Old_Thing(Some_Thing);
int Bomb_Move(Some_Thing XY, int Bomb_Num, double dx, double dy, vector<Some_Thing*>, int*, int*, int);
void Fire(Some_Thing* Tank, int Speed, MOUSEMSG* mouse, vector<Some_Thing*>, int*, int*, int);

//---------------类----------------


class TANK//基类
{
public:
	Some_Thing Output_Tank();//返回坦克位置
	int Input_Keyboard(int*, int*, int);
	int Input_Mouse();
	MOUSEMSG Output_Mouse();
	Some_Thing Tank;//为了能够实时获取Tank位置(直接调用) 所以放到public了 (放弃了再写一个函数来调用的想法)
	MOUSEMSG Mouse;//鼠标信息
protected:
	int HP;///还没有相关的函数
	int Speed;
};

class TANK_BASIC :public TANK   //基础坦克
{
public:
	TANK_BASIC(/*const wchar_t*,*/ Some_Thing tank = { 100,100 }, int HP = 100, int Speed = 2);//*图像路径* 默认位置100，100(左上角为原点) ;HP=100;速度 2像素/按一下
	//Some_Thing Output_Tank();//坦克位置
	//int Input_Keyboard();
	//int Input_Mouse();
	//MOUSEMSG Output_Mouse();
//	Some_Thing Tank;//为了能够实时获取Tank位置(直接调用) 所以放到public了 (放弃了再写一个函数来调用的想法)
//	MOUSEMSG Mouse;//同上
//private:
//	int HP;///还没有相关的函数
//	int Speed;
};