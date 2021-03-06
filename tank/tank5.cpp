// tank3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Tank's_Class.h"//包含了所有需要的头文件



int main()
{
	//生成墙的位置
	int x[100];
	int y[100];
	srand((unsigned int)time(NULL));//随机
	int Walls = 12;//12个墙
	for (int i = 0; i < Walls; i++)
	{
		x[i] = rand() % (Windows_L - 30);
		while (fabs(x[i] - 200) < 30 || fabs(x[i] - 300) < 30 || fabs(x[i] - 100) < 30)//避免墙与tank重叠
		{
			x[i] = rand() % (Windows_L - 30);
		}


		y[i] = rand() % (Windows_W - 30);
		while (fabs(y[i] - 200) < 30 || fabs(y[i] - 300) < 30 || fabs(y[i] - 400) < 30 || fabs(y[i] - 100) < 30)//避免墙与tank重叠
		{
			y[i] = rand() % (Windows_W - 30);
		}
	}

	//TCHAR TankImage_P1[] = _T("车体.BMP");

	Load_Image();//加载图像(初始化全局IMAGE类型变量)
	Draw_Map(Windows_L, Windows_W, x, y, Walls);//画地图  窗口大小: Windows_L * Windows_W 墙位置(x,y) 数量Walls

	TANK_BASIC tank_P1/*(L"车体.BMP")*/;//创建坦克 //默认位置100，100(左上角为原点) ;HP=100;速度 2像素/按一下
	TANK_BASIC tank_P2({200,200})/*(L"车体.BMP")*/;//创建坦克 //默认位置100，100(左上角为原点) ;HP=100;速度 2像素/按一下
	TANK_BASIC tank_P3({300,300})/*(L"车体.BMP")*/;//创建坦克 //默认位置100，100(左上角为原点) ;HP=100;速度 2像素/按一下
	TANK_BASIC tank_P4({200,400})/*(L"车体.BMP")*/;//创建坦克 //默认位置100，100(左上角为原点) ;HP=100;速度 2像素/按一下


	vector<Some_Thing*> All_Tank;//这个数组保存了所有坦克的Something信息的地址
	All_Tank.push_back(&tank_P1.Tank);
	All_Tank.push_back(&tank_P2.Tank);
	All_Tank.push_back(&tank_P3.Tank);
	All_Tank.push_back(&tank_P4.Tank);


	//线程+网络 改变P2坦克的位置信息

	thread th_Move(&TANK_BASIC::Input_Keyboard, &tank_P1, x, y, Walls);//线程 更新键盘操作 (如果不是传tank的地址 会无法更改tank里的值)
	thread th_Mouse(&TANK_BASIC::Input_Mouse, &tank_P1);//线程 更新鼠标位置
	
	thread th_Fire(Fire, &tank_P1.Tank, 10, &tank_P1.Mouse, All_Tank, x, y, Walls);//线程 传入tank位置(直接调用)、子弹速度(尽可能大)、tank类的鼠标信息 保存所有tank something信息的地址数组(给Bomb_Move线程的参数)
	
	thread th_Draw_Tank(&Draw_Tank, &tank_P1.Tank, &tank_P1.Mouse);//线程 画tank
	thread th_Draw_Tank2(&Draw_Tank, &tank_P2.Tank, &tank_P2.Mouse);//线程 画tank
	thread th_Draw_Tank3(&Draw_Tank, &tank_P3.Tank, &tank_P3.Mouse);//线程 画tank
	thread th_Draw_Tank4(&Draw_Tank, &tank_P4.Tank, &tank_P4.Mouse);//线程 画tank




	th_Draw_Tank4.join();
	th_Draw_Tank3.join();
	th_Draw_Tank2.join();
	th_Draw_Tank.join();
	th_Move.join();
	th_Mouse.join();
	th_Fire.join();
	return 0;
}
