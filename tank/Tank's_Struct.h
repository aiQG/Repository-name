#pragma once

#define Windows_L 640//定义窗口的长
#define Windows_W 480//定义窗口的宽

#define Dir_W 0
#define Dir_WA 1
#define Dir_A 2
#define Dir_AS 3
#define Dir_S 4
#define Dir_SD 5
#define Dir_D 6
#define Dir_DW 7

struct Some_Thing//坐标 + 方向 + 存活状态
{
	int X;//物体X坐标
	int Y;//物体Y坐标
	double Dir;//方向
	bool If_Not_Over;//这个东西是否存活(是否可见)
	//IMAGE Shape;//保存物体形状(图片)
};

