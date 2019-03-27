#include "stdafx.h"
#include"Tank's_Class.h"

//���º���������

//------TANK--------------
Some_Thing TANK::Output_Tank()//����λ����Ϣ
{
	return Tank;
}
int TANK::Input_Keyboard(int* x,int* y,int Ws)//�޸�λ����Ϣ  ����ǽ��λ��
{

	int W, A, S, D;//�����
	bool HitWall;
	while (1)//���������ж�
	{
		HitWall = 0;
		Sleep(30);//������while��ѭ��̫�� ���°�һ�� tank�ͳ�����Ļ 
		W = GetKeyState(87);
		A = GetKeyState(65);
		S = GetKeyState(83);
		D = GetKeyState(68);

		if (W < 0 && A >= 0 && S >= 0 && D >= 0)//ֻ��W
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W >= 0 && A < 0 && S >= 0 && D >= 0)//ֻ��A
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W >= 0 && A >= 0 && S < 0 && D >= 0)//ֻ��S
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W >= 0 && A >= 0 && S >= 0 && D < 0)//ֻ��D
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W < 0 && A < 0 && S >= 0 && D >= 0)//��WA
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W < 0 && A >= 0 && S >= 0 && D < 0)//��WD
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W >= 0 && A < 0 && S < 0 && D >= 0)//��AS
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
		else if (W >= 0 && A >= 0 && S < 0 && D < 0)//��SD
		{
			for (int i = 0; i < Ws; i++)//�ж��Ƿ���ǽ��ײ
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
MOUSEMSG TANK::Output_Mouse()//���������Ϣ
{
	return Mouse;
}
int TANK::Input_Mouse()//�޸������Ϣ
{
	while (1)
	{
		Mouse = GetMouseMsg();//��ȡ������ڻ�ͼ���ڵ���Ϣ
	}
	return 0;
}


//--------TANK_BASIC---------------
TANK_BASIC::TANK_BASIC(/*const wchar_t* path,*/ Some_Thing input_XY, int input_HP, int input_Speed)
{
	Tank = input_XY;
	Tank.If_Not_Over = 1;//����̹�˴��
	HP = input_HP;
	Speed = input_Speed;
	
	//loadimage(&Tank.Shape, path);
}



//���º�����������

IMAGE Tank_Body;//����ͼ��
IMAGE Tank_Tube;//�ڹ�ͼ��
IMAGE Bomb;//�ӵ�ͼ��
IMAGE Map;//��ͼͼ��
IMAGE caidan;//�ʵ�ͼ��
IMAGE Wall;//ǽͼ��

int Load_Image()//����ͼ��(��ʼ��ȫ��IMAGE���ͱ���)
{
	loadimage(&Tank_Body, L"����.BMP");
	loadimage(&Tank_Tube, L"�ڹ�.BMP");
	loadimage(&Bomb, L"�ӵ�.jpg");
	loadimage(&Map, L"��ͼ.jpg");
	loadimage(&caidan, L"caidan.jpg");
	loadimage(&Wall, L"ǽ.jpg");
	return 0;
}
int Draw_Map(int L, int W,int* x,int* y,int Ws)//���Ƶ�ͼ ��������ǽ��λ�� ���һ����ǽ������
{
	initgraph(L, W/*, SHOWCONSOLE*/);//���Ƶ�ͼ����
	putimage(0, 0, L, W, &Map, 0, 0);//������0 ��ʾ�ӵ�ͼ�ļ���0��0��ʼ����������
	//���λ�õ�ǽ
	for (int i = 0; i < Ws; i++)//����ǽ
	{
		//cout << "(" << x << "," << y << ")" << endl;
		putimage(x[i], y[i], 30, 30, &Wall, 0, 0, SRCAND);//��ʾǽͼƬ
	}


	return 0;
}
int Draw_Tank(Some_Thing* tank, MOUSEMSG *mouse)//�߳� ���ڹ��복��
{///TCHAR *a;//������ʽ
	Some_Thing old_tank = *tank;//������һ�ε�̹��λ�� �������ԭλ��ͼ��
	//IMAGE Tank_Body=tank->Shape;//����ͼ��
	while (1)
	{
		double hudu = atan2(mouse->y - tank->Y, mouse->x - tank->X);//atan2(x,y)=y/x(����)
		putimage(tank->X, tank->Y, 30, 30, &Tank_Tube, int((3.1415926535 + hudu) / 0.174532925194) * 30, 0, SRCAND);//��ʾ�ڹ�ͼƬ���ض�λ��
		putimage(tank->X, tank->Y, 30, 30, &Tank_Body, int(tank->Dir * 30), 0, SRCAND);//��ʾ����ͼƬ���ض�λ��
		Sleep(66);//��ֹ��˸
		Clean_Old_Thing(old_tank);//���̹��
		if (tank->If_Not_Over == 0)break;//̹������
		old_tank = *tank;//������һ�ε�̹��λ�� �������ԭλ��ͼ��
						 //putimage(XY.X, XY.Y, &Tank_Tube, SRCPAINT);//������ɫorͼƬ��ɫ///��ɫͼҪ�õ�
						 //putimage(XY.X, XY.Y, &Tank_Body, SRCPAINT);//������ɫorͼƬ��ɫ
	}
	return 0;
}
int Draw_Bomb(Some_Thing bomb)//�����ӵ�λ�á�����
{
	//double hudu = atan2(mouse->y - tank->Y, mouse->x - tank->X);//atan2(x,y)=y/x(����)
	putimage(bomb.X, bomb.Y, 30, 30, &Bomb, 0, 0, SRCAND);
	//putimage(bomb.X, bomb.Y, 30, 30, &Bomb, 0, 0, SRCPAINT);
	//putimage(XY.X, XY.Y, &xxx, SRCPAINT);//������ɫorͼƬ��ɫ
	return 0;
}
int Clean_Old_Thing(Some_Thing old_thing)
{
	clearrectangle(old_thing.X, old_thing.Y, old_thing.X + 30, old_thing.Y + 30);//�������
	//fillrectangle(old_thing.X, old_thing.Y, old_thing.X + 32, old_thing.Y + 32);//����ɫ
	putimage(old_thing.X, old_thing.Y, 32, 32, &Map, old_thing.X, old_thing.Y);//���ϱ���  ���岹�϶��ı���..�д���ȶ
	return 0;
}







int Bomb_Move(Some_Thing XY, int Bomb_Num, double dx, double dy, vector<Some_Thing*>  alltank, //�߳� ��ȡ�ӵ� X Y Dir(����) x�����ٶ�dx y�����ٶ�dy  ��������tank something��Ϣ�ĵ�ַ����
int* x,int* y,int Ws)//ǽλ�� ����
{
	int Num = Bomb_Num;//�����˼����ӵ�///���ܱ�ʾ��ǰ�м����ӵ�
	Some_Thing Old_Bomb = XY;//�����λ�ã�Ϊ������ӵ�׼��
	int i=0;
	while (XY.If_Not_Over)//�ӵ����������ƶ�
	{

		Draw_Bomb(XY);//�����ӵ�
		XY.X += int(dx);//����λ��
		XY.Y += int(dy);
		for (i = 0; i < alltank.size(); i++)
		{
			if (abs(alltank[i]->X - XY.X) < 30 && abs(alltank[i]->Y - XY.Y) < 30)
			{
				XY.If_Not_Over = 0;
				alltank[i]->If_Not_Over = 0;
				alltank[i]->X = -100;//��������̹�˵�λ��
				alltank[i]->Y = -100;//��������̹�˵�λ��
				//if(i==3)
					//putimage(0, 190, &caidan);//�ʵ�
			}
		}
		for (i = 0; i < Ws; i++)
		{
			if (abs(x[i] - XY.X) < 30 && abs(y[i] - XY.Y) < 30)//�ж��ӵ��Ƿ�ײǽ
			{
				XY.If_Not_Over = 0;
				
			}
		}
		if (XY.X > Windows_L || XY.X<0 || XY.Y>Windows_W || XY.Y < 0)//�ӵ�����
		{
			XY.If_Not_Over = 0;//�ӵ�����
		}
		Sleep(50);//�ӵ��ٶ�//��ֹ���ⵯ�Ĳ���
		Clean_Old_Thing(Old_Bomb);//������ӵ�
		Old_Bomb = XY;//�����λ�ã�Ϊ������ӵ�׼��
	}
	return 0;
}

int Bomb_Num = 0;//�����˼����ӵ�///���ܱ�ʾ��ǰ�м����ӵ�//���ڴ���vector
void Fire(Some_Thing* Tank, int Speed, MOUSEMSG* mouse, vector<Some_Thing*>  alltank, int* x, int* y, int Ws)//�߳� ����һ�� ����һ�����ӵ��ܵ��߳�  //���뵱ǰtankλ�� �ӵ��ٶ� tank�������Ϣ ��������tank something��Ϣ�ĵ�ַ����(��Bomb_Move�̵߳Ĳ���)
{
	MOUSEMSG Mouse;
	double hudu;
	Some_Thing XY;
	double dx;
	double dy;
	vector<thread> Moving_Bomb;//���ҵ��ɶ�̬�����//���ڱ����߳�
	vector<Some_Thing> Bomb_vector;//���ҵ��ɶ�̬�����//���ڱ���ÿ��Bomb��Some_Thing��Ϣ
	Bomb_vector.push_back(*Tank);//��ʼ����һ���ӵ�

	while (1)//û���������������������(��Ҫ���� ����Ҫ�Ȱ������߳̽���)
	{
		Mouse = *mouse;
		hudu = atan2(Mouse.y - Tank->Y, Mouse.x - Tank->X);//atan2(x,y)=y/x��б��ת��Ϊ����
		XY = { Tank->X, Tank->Y, hudu };//�����ӵ���ʼλ�á����� 
		dx = Speed * cos(XY.Dir);//�ٶȷֽ⵽x��
		dy = Speed * sin(XY.Dir);//�ٶȷֽ⵽y��
		Bomb_vector[Bomb_Num] = XY;//���µ�ǰ�ӵ���ʼλ��
		Bomb_vector[Bomb_Num].X += int(35 * cos(Bomb_vector[Bomb_Num].Dir));//���ӵ����ֵ�λ��ǰ��
		Bomb_vector[Bomb_Num].Y += int(35 * sin(Bomb_vector[Bomb_Num].Dir));//���ӵ����ֵ�λ��ǰ��
		if (Mouse.mkLButton)//������ �����ӵ�
		{
			Bomb_vector[Bomb_Num].If_Not_Over = 1;//�����ӵ����
			Moving_Bomb.push_back(thread(Bomb_Move, Bomb_vector[Bomb_Num], Bomb_Num, dx, dy, alltank, x, y, Ws));//����̱߳������� Moving_Bomb β��
			++Bomb_Num;//�������ӵ�������һ	
			Bomb_vector.push_back(*Tank);//��ʼ����һ���ӵ�
			Sleep(500);//������
		}
	}
}
