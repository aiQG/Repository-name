#include "stdafx.h"
#include"Tank's_Class.h"

//以下函数在类中

//------TANK--------------
Some_Thing TANK::Output_Tank()//返回位置信息
{
	return Tank;
}
int TANK::Input_Keyboard(int* x,int* y,int Ws)//修改位置信息  传入墙的位置
{

	int W, A, S, D;//方向键
	bool HitWall;
	while (1)//操作方向判断
	{
		HitWall = 0;
		Sleep(30);//！！！while的循环太快 导致按一下 tank就出了屏幕 
		W = GetKeyState(87);
		A = GetKeyState(65);
		S = GetKeyState(83);
		D = GetKeyState(68);

		if (W < 0 && A >= 0 && S >= 0 && D >= 0)//只按W
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (Tank.Y - y[i] < 33 && Tank.Y - y[i] >0 && abs(Tank.X - x[i]) < 33)
				{
					cout << Tank.Y - y[i] << " jump " << Tank.X - x[i] << endl;
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.Y -= Speed;
			Tank.Dir = Dir_W;
		}
		else if (W >= 0 && A < 0 && S >= 0 && D >= 0)//只按A
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (Tank.X - x[i] < 33 && Tank.X - x[i] >0 && abs(Tank.Y - y[i]) < 33)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.X -= Speed;
			Tank.Dir = Dir_A;
		}
		else if (W >= 0 && A >= 0 && S < 0 && D >= 0)//只按S
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (y[i] - Tank.Y < 33 && y[i] - Tank.Y>0 && abs(Tank.X - x[i]) < 33)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.Y += Speed;
			Tank.Dir = Dir_S;
		}
		else if (W >= 0 && A >= 0 && S >= 0 && D < 0)//只按D
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (x[i] - Tank.X < 33 && x[i] - Tank.X >0 && abs(Tank.Y - y[i]) < 33)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.X += Speed;
			Tank.Dir = Dir_D;
		}
		else if (W < 0 && A < 0 && S >= 0 && D >= 0)//按WA
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (Tank.Y - y[i] < 33 && Tank.Y - y[i] >0 && Tank.X - x[i] < 33)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.X -= Speed / 2;
			Tank.Y -= Speed / 2;
			Tank.Dir = Dir_WA;
		}
		else if (W < 0 && A >= 0 && S >= 0 && D < 0)//按WD
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (Tank.Y - y[i] < 33 && Tank.Y - y[i] >0 && x[i] - Tank.X < 33 && x[i] - Tank.X>0)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.X += Speed / 2;
			Tank.Y -= Speed / 2;
			Tank.Dir = Dir_DW;
		}
		else if (W >= 0 && A < 0 && S < 0 && D >= 0)//按AS
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (y[i] - Tank.Y < 33 && y[i] - Tank.Y>0 && Tank.X - x[i] < 33 && Tank.X - x[i]>0)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.X -= Speed / 2;
			Tank.Y += Speed / 2;
			Tank.Dir = Dir_AS;
		}
		else if (W >= 0 && A >= 0 && S < 0 && D < 0)//按SD
		{
			for (int i = 0; i < Ws; i++)//判断是否与墙相撞
			{
				if (y[i] - Tank.Y < 33 && y[i] - Tank.Y>0 && x[i] - Tank.X < 33 && x[i] - Tank.X>0)
				{
					HitWall = 1;
					break;
				}
			}
			if (HitWall)
				continue;
			Tank.X += Speed / 2;
			Tank.Y += Speed / 2;
			Tank.Dir = Dir_SD;
		}
	}

	return 0;
}
MOUSEMSG TANK::Output_Mouse()//返回鼠标信息
{
	return Mouse;
}
int TANK::Input_Mouse()//修改鼠标信息
{
	while (1)
	{
		Mouse = GetMouseMsg();//获取在鼠标在绘图窗口的信息
	}
	return 0;
}


//--------TANK_BASIC---------------
TANK_BASIC::TANK_BASIC(/*const wchar_t* path,*/ Some_Thing input_XY, int input_HP, int input_Speed)
{
	Tank = input_XY;
	Tank.If_Not_Over = 1;//设置坦克存活
	HP = input_HP;
	Speed = input_Speed;
	
	//loadimage(&Tank.Shape, path);
}



//以下函数不在类中

IMAGE Tank_Body;//车体图像
IMAGE Tank_Tube;//炮管图像
IMAGE Bomb;//子弹图像
IMAGE Map;//地图图像
IMAGE caidan;//彩蛋图像
IMAGE Wall;//墙图像

int Load_Image()//加载图像(初始化全局IMAGE类型变量)
{
	loadimage(&Tank_Body, L"车体.BMP");
	loadimage(&Tank_Tube, L"炮管.BMP");
	loadimage(&Bomb, L"子弹.jpg");
	loadimage(&Map, L"地图.jpg");
	loadimage(&caidan, L"caidan.jpg");
	loadimage(&Wall, L"墙.jpg");
	return 0;
}
int Draw_Map(int L, int W,int* x,int* y,int Ws)//绘制地图 后两个是墙的位置 最后一个是墙的数量
{
	initgraph(L, W/*, SHOWCONSOLE*/);//绘制地图窗口
	putimage(0, 0, L, W, &Map, 0, 0);//后两个0 表示从地图文件的0，0开始画到窗口内
	//随机位置的墙
	for (int i = 0; i < Ws; i++)//生成墙
	{
		//cout << "(" << x << "," << y << ")" << endl;
		putimage(x[i], y[i], 30, 30, &Wall, 0, 0, SRCAND);//显示墙图片
	}


	return 0;
}
int Draw_Tank(Some_Thing* tank, MOUSEMSG *mouse)//线程 画炮管与车体
{///TCHAR *a;//车体样式
	Some_Thing old_tank = *tank;//保存上一次的坦克位置 用于清除原位置图像
	//IMAGE Tank_Body=tank->Shape;//车体图像
	while (1)
	{
		double hudu = atan2(mouse->y - tank->Y, mouse->x - tank->X);//atan2(x,y)=y/x(弧度)
		putimage(tank->X, tank->Y, 30, 30, &Tank_Tube, int((3.1415926535 + hudu) / 0.174532925194) * 30, 0, SRCAND);//显示炮管图片的特定位置
		putimage(tank->X, tank->Y, 30, 30, &Tank_Body, int(tank->Dir * 30), 0, SRCAND);//显示车体图片的特定位置
		Sleep(66);//防止闪烁
		Clean_Old_Thing(old_tank);//清除坦克
		if (tank->If_Not_Over == 0)break;//坦克死亡
		old_tank = *tank;//保存上一次的坦克位置 用于清除原位置图像
						 //putimage(XY.X, XY.Y, &Tank_Tube, SRCPAINT);//背景颜色or图片颜色///彩色图要用到
						 //putimage(XY.X, XY.Y, &Tank_Body, SRCPAINT);//背景颜色or图片颜色
	}
	return 0;
}
int Draw_Bomb(Some_Thing bomb)//传入子弹位置、方向
{
	//double hudu = atan2(mouse->y - tank->Y, mouse->x - tank->X);//atan2(x,y)=y/x(弧度)
	putimage(bomb.X, bomb.Y, 30, 30, &Bomb, 0, 0, SRCAND);
	//putimage(bomb.X, bomb.Y, 30, 30, &Bomb, 0, 0, SRCPAINT);
	//putimage(XY.X, XY.Y, &xxx, SRCPAINT);//背景颜色or图片颜色
	return 0;
}
int Clean_Old_Thing(Some_Thing old_thing)
{
	clearrectangle(old_thing.X, old_thing.Y, old_thing.X + 30, old_thing.Y + 30);//清空区域
	//fillrectangle(old_thing.X, old_thing.Y, old_thing.X + 32, old_thing.Y + 32);//填充白色
	putimage(old_thing.X, old_thing.Y, 32, 32, &Map, old_thing.X, old_thing.Y);//补上背景  具体补上多大的背景..有待商榷
	return 0;
}







int Bomb_Move(Some_Thing XY, int Bomb_Num, double dx, double dy, vector<Some_Thing*>  alltank, //线程 获取子弹 X Y Dir(方向) x方向速度dx y方向速度dy  保存所有tank something信息的地址数组
int* x,int* y,int Ws)//墙位置 数量
{
	int Num = Bomb_Num;//创建了几个子弹///不能表示当前有几个子弹
	Some_Thing Old_Bomb = XY;//保存旧位置，为清除旧子弹准备
	int i=0;
	while (XY.If_Not_Over)//子弹存活则继续移动
	{

		Draw_Bomb(XY);//画出子弹
		XY.X += int(dx);//更新位置
		XY.Y += int(dy);
		for (i = 0; i < alltank.size(); i++)
		{
			if (abs(alltank[i]->X - XY.X) < 30 && abs(alltank[i]->Y - XY.Y) < 30)
			{
				XY.If_Not_Over = 0;
				alltank[i]->If_Not_Over = 0;
				alltank[i]->X = -100;//重置死亡坦克的位置
				alltank[i]->Y = -100;//重置死亡坦克的位置
				//if(i==3)
					//putimage(0, 190, &caidan);//彩蛋
			}
		}
		for (i = 0; i < Ws; i++)
		{
			if (abs(x[i] - XY.X) < 30 && abs(y[i] - XY.Y) < 30)//判断子弹是否撞墙
			{
				XY.If_Not_Over = 0;
				
			}
		}
		if (XY.X > Windows_L || XY.X<0 || XY.Y>Windows_W || XY.Y < 0)//子弹出界
		{
			XY.If_Not_Over = 0;//子弹死亡
		}
		Sleep(50);//子弹速度//防止激光弹的产生
		Clean_Old_Thing(Old_Bomb);//清除旧子弹
		Old_Bomb = XY;//保存旧位置，为清除旧子弹准备
	}
	return 0;
}

int Bomb_Num = 0;//创建了几个子弹///不能表示当前有几个子弹//用于创建vector
void Fire(Some_Thing* Tank, int Speed, MOUSEMSG* mouse, vector<Some_Thing*>  alltank, int* x, int* y, int Ws)//线程 鼠标点一下 创建一个让子弹跑的线程  //传入当前tank位置 子弹速度 tank的鼠标信息 保存所有tank something信息的地址数组(给Bomb_Move线程的参数)
{
	MOUSEMSG Mouse;
	double hudu;
	Some_Thing XY;
	double dx;
	double dy;
	vector<thread> Moving_Bomb;//暂且当成动态数组吧//用于保存线程
	vector<Some_Thing> Bomb_vector;//暂且当成动态数组吧//用于保存每个Bomb的Some_Thing信息
	Bomb_vector.push_back(*Tank);//初始化下一个子弹

	while (1)//没有让这个函数结束的条件(若要结束 则需要先把所有线程结束)
	{
		Mouse = *mouse;
		hudu = atan2(Mouse.y - Tank->Y, Mouse.x - Tank->X);//atan2(x,y)=y/x的斜率转换为弧度
		XY = { Tank->X, Tank->Y, hudu };//设置子弹起始位置、方向 
		dx = Speed * cos(XY.Dir);//速度分解到x轴
		dy = Speed * sin(XY.Dir);//速度分解到y轴
		Bomb_vector[Bomb_Num] = XY;//更新当前子弹起始位置
		Bomb_vector[Bomb_Num].X += int(35 * cos(Bomb_vector[Bomb_Num].Dir));//将子弹出现的位置前移
		Bomb_vector[Bomb_Num].Y += int(35 * sin(Bomb_vector[Bomb_Num].Dir));//将子弹出现的位置前移
		if (Mouse.mkLButton)//左键点击 创建子弹
		{
			Bomb_vector[Bomb_Num].If_Not_Over = 1;//设置子弹存活
			Moving_Bomb.push_back(thread(Bomb_Move, Bomb_vector[Bomb_Num], Bomb_Num, dx, dy, alltank, x, y, Ws));//这个线程被创建到 Moving_Bomb 尾部
			++Bomb_Num;//创建的子弹总数加一	
			Bomb_vector.push_back(*Tank);//初始化下一个子弹
			Sleep(500);//开火间隔
		}
	}
}
