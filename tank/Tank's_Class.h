#pragma once
#include "stdafx.h"
#include<iostream>
#include<Windows.h>//GetKeyState 
#include<thread>//�߳�����ð�~//�ƶ� ��� �滭 
#include <graphics.h>//EasyX��
#include<string>//�ļ�·�� 
#include <vector>//STL
#include"Tank's_struct.h"//Some_Thing

using namespace std;//���ڲ���ʱcout

//---------------��������-----------------


//���º�����������
int Load_Image();
int Draw_Map(int, int, int*, int*, int);
int Draw_Tank(Some_Thing*, MOUSEMSG*);
int DRAW_Bomb(Some_Thing);
int Clean_Old_Thing(Some_Thing);
int Bomb_Move(Some_Thing XY, int Bomb_Num, double dx, double dy, vector<Some_Thing*>, int*, int*, int);
void Fire(Some_Thing* Tank, int Speed, MOUSEMSG* mouse, vector<Some_Thing*>, int*, int*, int);

//---------------��----------------


class TANK//����
{
public:
	Some_Thing Output_Tank();//����̹��λ��
	int Input_Keyboard(int*, int*, int);
	int Input_Mouse();
	MOUSEMSG Output_Mouse();
	Some_Thing Tank;//Ϊ���ܹ�ʵʱ��ȡTankλ��(ֱ�ӵ���) ���Էŵ�public�� (��������дһ�����������õ��뷨)
	MOUSEMSG Mouse;//�����Ϣ
protected:
	int HP;///��û����صĺ���
	int Speed;
};

class TANK_BASIC :public TANK   //����̹��
{
public:
	TANK_BASIC(/*const wchar_t*,*/ Some_Thing tank = { 100,100 }, int HP = 100, int Speed = 2);//*ͼ��·��* Ĭ��λ��100��100(���Ͻ�Ϊԭ��) ;HP=100;�ٶ� 2����/��һ��
	//Some_Thing Output_Tank();//̹��λ��
	//int Input_Keyboard();
	//int Input_Mouse();
	//MOUSEMSG Output_Mouse();
//	Some_Thing Tank;//Ϊ���ܹ�ʵʱ��ȡTankλ��(ֱ�ӵ���) ���Էŵ�public�� (��������дһ�����������õ��뷨)
//	MOUSEMSG Mouse;//ͬ��
//private:
//	int HP;///��û����صĺ���
//	int Speed;
};