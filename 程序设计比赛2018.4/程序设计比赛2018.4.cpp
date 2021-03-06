// 程序设计比赛2018.4.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<thread>//线程
#include<conio.h>//getch
#include<string>
#include<fstream>//文件输入输出
#include<Windows.h>//GetKeyState system Sleep
#include<ctime> //time_t
#include <graphics.h>//用到了EasyX的图形库
#include<mmsystem.h>//BGM
#pragma comment(lib, "Winmm.lib")//设置BGM的参数

using namespace std;

class Menu //这个是菜单类(包括了|菜单显示| 与 |接收用户选择指令|)
{
public:
	void get_menu();//主菜单
	char send_cmd();//发送命令
private:
	char cmd;//用户的输入
	void get_cmd();//获取用户命令
};
void Menu::get_menu()
{
	cmd = 0;//初始化cmd
	cout << " ···············" << endl;
	cout << " ·" << "(键入序号以进入相应功能)" << "  ·" << endl;
	cout << " ·" << "1.我和ta的那些日子(记事本)" << "·" << endl;
	cout << " ·" << "2.ta和我的那一天(纪念日)" << "  ·" << endl;
	cout << " ·" << "3.Lover Run Run RUN!(游戏)" << "·" << endl;
	cout << " ·" << "4.优雅之蓝" << "                ·" << endl;
	cout << " ·" << "5.离开" << "                    ·" << endl;
	cout << " ···············" << endl;
	thread thr_Get(&Menu::get_cmd, this);//运行线程 以获得用户输入的指令
	thr_Get.join();
}
char Menu::send_cmd()
{
	return cmd;
}
void Menu::get_cmd()//获取用户输入的命令
{
	while (cmd!='1'&&cmd!='2'&&cmd!='3'&&cmd!='4'&&cmd!='5')//接收的命令不为1 2 3 4 则不结束线程
	{
		cmd = _getch();
	}
	return;
}

class Txt//这个类实现了"记书本"功能
{
public:
	Txt(string);//构造函数 传入文件名
	void TxtWirte();//写入信息
	void TxtRead();//读取信息
	//~Txt();
private:
	string pFile;//保存文件路径
	void SaveBack();//保存并返回上一层
	bool back;//是否结束循环
};
Txt::Txt(string f)
{
	pFile = f;
	back = 0;//初始化back
}
void Txt::TxtWirte()
{
	cout << endl << " ·新增记录:(ctrl+s 保存并返回主菜单)" << endl;
	ofstream FWirte(pFile,ios::app);//用输出追加方式打开文件
	string temp;
	thread thr_SB(&Txt::SaveBack, this);//这个线程接收用户保存指令
	
	if (!FWirte)//判断文件是否成功打开
	{
		cout << " ·文件打开失败!" << endl;
		return;
	}
	while (back == 0)//当back被改变时退出循环
	{
		getline(cin, temp);//获取输入
		FWirte << temp;
		FWirte << endl;
	}
	thr_SB.join();
	back = 0;//初始化back
	FWirte.close();
	return;
}
void Txt::TxtRead()
{
	ifstream FRead(pFile);//用输入方式打开文件
	string temp;
	if (!FRead)//判断文件是否成功打开
	{
		ofstream F(pFile);
		cout << " 创建新记录!·" << endl;
		cout << "·······" << endl;
		F.close();
	}
	while (getline(FRead, temp))//逐行读取
	{
		cout << temp;
		cout << endl;
	}
	FRead.close();
	return;
}
void Txt::SaveBack()
{
	int ctrl;
	int s;
	while (1)
	{
		ctrl = GetKeyState(VK_CONTROL);//检测ctrl是否被按下
		s = GetKeyState(83);//检测s是否被按下
		if (ctrl < 0 && s < 0)//ctrl与s同时被按下
		{
			cout << endl << " ·退出?(回车确定)" << endl;//引导用户再按一次回车
			back = 1;//改变back 以退出TxtWrite函数的循环
			return;
		}

	}

}

class Time
{
public:
	Time(string);
	void get_tmie();
	void get_the_day();
	void set_the_day();//重新设置纪念日
	void display_time();
	void how_long();//计算今天距离下个纪念日还有多久
	char send_cmd();
private:
	char cmd;//取得用户输入的命令
	void get_cmd();	
	int year;
	int month;
	int day;
	string file;
	tm nowtime;//保存当前时间的结构体
};
Time::Time(string f)//构造函数(主要用于保存要打开的文件名)
{
	file = f;
}
void Time::set_the_day()
{
	string y, m, d;//用string是为了防止有形如xxxx.xx.xx的输入
	cout << endl << " ·纪念日是那一年:" << endl;
	cin >> y;
	cout << " ·纪念日是几月份:" << endl;
	cin >> m;
	cout << " ·纪念日是几号:" << endl;
	cin >> d;
	year = stoi(y);
	month = stoi(m);
	day = stoi(d);
	if (year <= 1900 || month > 12 || month < 1 || day>31 || day < 1)
	{
		cout << " ·输入非法 请重新输入" << endl << endl;
		cmd = 'x';//标记cmd
		return;
	}
	ofstream Date(file);//重新编写日期 (这里才打开文件 主要是为了用户有 后悔 的时间)
	Date << y << " " << m << " " << d << endl;
	Date.close();
	cout << " ·设置中..." << endl << endl;//人性化反馈
	Sleep(1000);
	system("cls");
	cout << " ·设置完成!" << endl << endl;
	cmd = 0;//初始化cmd
}
void Time::get_tmie()
{
	__time64_t long_time;
	_time64(&long_time);//获取系统时间
	_localtime64_s(&nowtime, &long_time);//将系统时间存到nowtime结构体
}
void Time::get_the_day()
{
	ifstream Date(file);
	if (!Date)
	{
		cout << " ·请设置纪念日日期" << endl;
		this->set_the_day();
		return;
	}
	Date >> year >> month >> day;//读取保存的日期
	Date.close();
}
void Time::display_time()
{
	cout << " ·今天是 "
		<< nowtime.tm_year + 1900 << "-"
		<< nowtime.tm_mon + 1 << "-"
		<< nowtime.tm_mday 
		<< endl;
	cout << " ·纪念日是 "
		<< year << "-"
		<< month << "-"
		<< day 
		<< endl;
}
void Time::how_long()
{
	int m = month - (nowtime.tm_mon + 1);
	int d = day - nowtime.tm_mday;
	if (m < 0)
	{
		m = 12 + m;
	}
	if (d < 0)
	{
		switch (nowtime.tm_mon + 1)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			d = d + 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			d = d + 30;
			break;
		case 2:
			if (
				((nowtime.tm_year + 1900) % 4 == 0
					&& (nowtime.tm_year + 1900) % 100 != 0)
				|| (nowtime.tm_year + 1900) % 400 == 0
				)//判断是闰年
			{
				d = d + 29;
			}
			else
			{
				d = d + 28;
			}
			break;

		}
	}
	cout << " ·距离下一个纪念日还有:"
		<< m << " 个月"
		<< d << " 天"
		<< endl;
	thread thr_submenu(&Time::get_cmd, this);//这个线程用于接收用户输入的命令
	thr_submenu.join();
}
void Time::get_cmd()
{
	cout << endl << " ············" << endl;
	cout << " ·1.返回主菜单        ·" << endl;
	cout << " ·2.重新设置纪念日    ·" << endl;
	cout << " ············" << endl;
	while (cmd!='1'&&cmd!='2')
	{
		cmd = _getch();
	}
	return;
}
char Time::send_cmd()
{
	return cmd;
}

class Game
{
public:
	void start();//完成开始游戏的一系列初始化
	void StartAndEnd();//后台 接收用户开始与结束命令
	void get_P1();//取得P1的操作
	void get_P2();//取得P2的操作
	void display_score();//更新与显示分数
	void End_Game();
	void star_GO();//开始需要改变GO的值
	void game_instructions();//游戏说明
	~Game();//遗忘过去吧!!!
private:
	bool GO;//接收可以倒数命令
	bool end;//游戏是否结束
	bool back;//退出游戏命令
	bool Run_BGM;//播放音乐
	int P1_Step;//P1_步数
	int P1_Score;//分数
	int P2_Step;//P2_步数
	int P2_Score;//分数
};
void Game::start()
{
	end = 0;//初始化end
	back = 0;//初始化back
	P1_Step = 0;//初始化P1步数
	P1_Score = 0;//分数
	P2_Step = 0;//初始化P2步数
	P2_Score = 0;//分数
	TCHAR sEsc1[] = _T("按Esc键");
	TCHAR sEsc2[] = _T(" →退出游戏");
	TCHAR sEnter1[] = _T("按回车键");
	TCHAR sEnter2[] = _T(" →重新开始");
	TCHAR sP1[] = _T("P1");
	TCHAR sP2[] = _T("P2");
	TCHAR sP1_score[] = _T("P1分数:");
	TCHAR sP2_score[] = _T("P2分数:");
	TCHAR sP1_step[] = _T("P1步数:");
	TCHAR sP2_step[] = _T("P2步数:");
	TCHAR sGO[] = _T("GO!");


	//画界面的基本框架
	initgraph(640, 480);   // 创建绘图窗口，大小为 640x480 像素	
	clearrectangle(0, 0, 640, 480);//清空矩形区域
	setlinecolor(RED);
	setlinestyle(PS_DASHDOT);
	line(0, 40, 640, 40);
	setlinestyle(PS_SOLID);
	setlinecolor(WHITE);
	line(270, 0, 270, 480);//画线 分开P1与P2
	line(540, 0, 540, 480);//画线 分开游戏区与分数区	
	outtextxy(0, 0, sEsc1);//按Esc键 退出游戏 标识
	outtextxy(0, 20, sEsc2);
	outtextxy(0, 40, sEnter1);//按回车键  重新开始 标识
	outtextxy(0, 60, sEnter2);
	outtextxy(133, 5, sP1);//P1 标识
	outtextxy(403, 5, sP2);//P2 标识
	outtextxy(550, 20, sP1_step);//P1步数 标识
	outtextxy(550, 120, sP1_score);//P1分数 标识
	outtextxy(550, 220, sP2_step);//P2步数 标识
	outtextxy(550, 320, sP2_score);//P2分数 标识

	if (GO == 1)//可以开始倒数
	{
		GO = 0;//初始化GO
		for (int i = 3; i >= 0; i--)//倒数3 2 1 GO!
		{
			clearrectangle(280, 200, 360, 280);//清空矩形区域
			if (i == 3)
			{
				outtextxy(280, 200, '3');
				Sleep(1000);
			}
			else if (i == 2)
			{
				outtextxy(280, 200, '2');
				Sleep(1000);
			}
			else if (i == 1)
			{
				outtextxy(280, 200, '1');
				Sleep(1000);
			}
			else if (i == 0)
			{
				outtextxy(280, 200, sGO);//开始				
				thread thr_StartAndEnd(&Game::StartAndEnd, this);//这个线程用于接收用户的 esc 和 enter命令
				thread thr_get_P1(&Game::get_P1, this);//用于接收P1的操作
				thread thr_get_P2(&Game::get_P2, this);//用于接收P2的操作
				thread thr_display_score(&Game::display_score, this);//用于更新分数
				thread thr_End_Game(&Game::End_Game, this);//用于判断是否分出胜负
				Sleep(1000);
				clearrectangle(280, 200, 360, 280);
				thr_StartAndEnd.join();//等候线程结束
				thr_get_P1.join();
				thr_get_P2.join();
				thr_display_score.join();
				thr_End_Game.join();
			}
		}
	}

}
void Game::StartAndEnd()
{
	int space;
	int enter;
	int esc;
	while (1)
	{
		enter = GetKeyState(VK_RETURN);
		if (enter < 0)//回车被按下
		{
			GO = 1;
			this->start();//调用start 开始游戏
		}
		esc = GetKeyState(VK_ESCAPE);
		if (esc < 0)//esc被按下
		{
			closegraph();  // 关闭绘图窗口
			back = 1;//返回菜单
			return;
		}
		space = GetKeyState(VK_SPACE);
		if (end == 1 && space < 0)//空格被按下
		{
			waveOutSetVolume(0, 0x5201314);//设置音量
			sndPlaySound(L"BGMafterGame.wav", SND_ASYNC);//播放BGM
		}
	}
}
void Game::get_P1()
{
	int y = 480;//脚印的y坐标
	int left;
	int right;
	bool num_L,num_R;//用于判断左右键是否被按下
	num_L = 0;
	num_R = 0;
	while (1)
	{
		left = GetKeyState(65);
		right = GetKeyState(68);
		if (left < 0)//A被按下
		{
			num_L = 1;
		}
		else if (right < 0)//D被按下  ///这里如果不用 else if 可能出错
		{
			num_R = 1;
		}
		if (num_L == 1 && num_R == 1)
		{
			if (P1_Step % 2 == 0)
			{
				outtextxy(135, y, 'd');
				y = y - 5;
			}
			else
			{
				outtextxy(140, y, 'b');
				y = y - 5;
			}
			P1_Step++;//步数加一
			num_L = 0;//初始化 
			num_R = 0;
		}
		if (back == 1 || end == 1)//back或end=1时退出
		{
			return;
		}
	}
}
void Game::get_P2()
{
	int y = 480;
	int left;
	int right;
	bool num_L, num_R;//用于判断左右键是否被按下
	num_L = 0;
	num_R = 0;
	while (1)
	{
		left = GetKeyState(VK_LEFT);
		right = GetKeyState(VK_RIGHT);
		if (left < 0)//左箭头被按下
		{
			num_L = 1;
		}
		else if (right < 0)//右箭头被按下  ///这里不用else if可能会出错
		{
			num_R = 1;
		}
		if (num_L == 1 && num_R == 1)
		{
			if (P2_Step % 2 == 0)
			{
				outtextxy(405, y, 'o');
				y = y - 5;
			}
			else
			{
				outtextxy(410, y, 'o');
				y = y - 5;
			}
			P2_Step++;//步数加一
			num_L = 0;//初始化 
			num_R = 0;
		}
		if (back == 1 || end == 1)//back或end=1时退出
		{
			return;
		}
	}
}
void Game::display_score()
{
	TCHAR sP1_Score[100];//保存分数、步数的数组
	TCHAR sP2_Score[100];
	TCHAR sP1_Step[100];
	TCHAR sP2_Step[100];
	while (1)
	{
		Sleep(100);
		P1_Score = 100 * (P1_Step / 3);//计算分数
		P2_Score = 100 * (P2_Step / 3);
		_stprintf_s(sP1_Score, _T("%d"), P1_Score);//数字转换成字符串
		_stprintf_s(sP2_Score, _T("%d"), P2_Score);
		_stprintf_s(sP1_Step, _T("%d"), P1_Step);
		_stprintf_s(sP2_Step, _T("%d"), P2_Step);
		clearrectangle(580, 70, 600, 100);//清空矩形区域
		clearrectangle(580, 170, 600, 200);//清空矩形区域
		clearrectangle(580, 270, 600, 300);//清空矩形区域
		clearrectangle(580, 370, 600, 400);//清空矩形区域
		outtextxy(580, 70, sP1_Step);//P1步数
		outtextxy(580, 170, sP1_Score);//分数
		outtextxy(580, 270, sP2_Step);//P2步数
		outtextxy(580, 370, sP2_Score);//分数
		if (back == 1 || end == 1)
		{
			return;
		}
	}
}
void Game::End_Game()
{
	TCHAR P1_Win[] = _T("P1 获胜!");
	TCHAR P2_Win[] = _T("P2 获胜!");
	TCHAR BGM[] = _T("按下 空格 播放胜利音乐!");
	while (1)
	{
		if (back == 1)
		{
			return;
		}
		if (P1_Score >= 3000)
		{
			outtextxy(280, 200, P1_Win);
			outtextxy(280, 230, BGM);
			end = 1;
			return;
		}
		else if (P2_Score >= 3000)
		{
			outtextxy(280, 200, P2_Win);
			outtextxy(280, 230, BGM);
			end = 1;
			return;
		}
	}
}
void Game::star_GO()
{
	GO = 1;
}
void Game::game_instructions()
{
	TCHAR instructions1[] = _T("P1:疯狂连击AD 向前奔跑!");
	TCHAR instructions2[] = _T("P2:疯狂连击←→ 向前奔跑!");
	TCHAR instructions3[] = _T("首先到达3000分的玩家获胜!");
	TCHAR instructions4[] = _T("(按下回车开始)");
	initgraph(640, 480);   // 创建绘图窗口，大小为 640x480 像素	
	outtextxy(188, 126, instructions1);
	outtextxy(188, 146, instructions2);
	outtextxy(188, 166, instructions3);
	outtextxy(188, 186, instructions4);
	getchar();
	closegraph();          // 关闭绘图窗口
}
Game::~Game()
{}


void Run()
{
	WinExec("Stop.exe", SW_HIDE);//启动屏蔽键盘鼠标操作的程序
	int cx = GetSystemMetrics(SM_CXSCREEN);//获取屏幕长
	int cy = GetSystemMetrics(SM_CYSCREEN);//获取屏幕高
	initgraph(1920, 1080);//随便创建个绘图窗口(大小后面还要调整)
	HWND hWnd = GetHWnd();//获取窗口句柄
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);//去掉标题栏
	MoveWindow(hWnd, 0, 0, cx, cy, 1);//移动窗口
	loadimage(NULL, L"blue.jpg", cx, cy);//打开图片
	_getch();
	closegraph();
}

void Run_Txt(Txt txt)
{
	txt.TxtRead();
	txt.TxtWirte();
}
void Run_Time(Time time)
{
	time.get_tmie();
	time.get_the_day();
	time.display_time();
	time.how_long();
	if (time.send_cmd() == '2')
	{
		time.set_the_day();
		if (time.send_cmd() != 'x')
		{
			Run_Time(time);//再调用一次自己
		}
		else
			time.set_the_day();
	}
}


int main()
{
	Menu menuA;
	Txt txtA("my记事本.txt");
	Time timeA("our纪念日.txt");
	while (1)
	{
		menuA.get_menu();
		system("cls");//选择功能后清屏
		switch (menuA.send_cmd())
		{
		case '1':
			system("cls");
			Run_Txt(txtA);
			break;
		case '2':
			system("cls");
			Run_Time(timeA);
			break;
		case '3':
			Game gameA;//实现额外功能
			gameA.game_instructions();
			gameA.star_GO();
			gameA.start();
			gameA.~Game();
			break;
		case '4':
			Run();
			break;
		case '5':
			exit(1);
			break;
		}
		system("cls");//结束功能后清屏
	}
    return 0;
}

