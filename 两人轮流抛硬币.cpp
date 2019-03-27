//
//  main.cpp
//  123
//
//  Created by 周测 on 2018/8/25.
//  Copyright © 2018年 周测. All rights reserved.
//
#include<ctime>
#include <iostream>
using namespace std;
int main()
{
    cout<<"两个人抛硬币 先抛出正面的女装 问先抛的人女装概率"<<endl<<endl;
    
    
    srand((unsigned)time(NULL));
    int x=rand()%2;//1为正面
    int A=0;//A人(the first)
    int B=0;//B人
    int flag=1;
    
    for(int i=0;i<100;i++)
    {
        flag=1;//下一次实验 从A开始
        while(1)//没抛到正面
        {
            cout<<x<<endl;
            x=rand()%2;//随机正反面
            if(x==1&&flag==1)
            {
                A++;//A 抛到正面
                break;
            }
            if(x==1&&flag==2)
            {
                B++;//B 抛到正面
                break;
            }
            if(flag==1) flag=2;//下一个人抛
            else if(flag==2) flag=1;//下一个人抛
        }
        
    }
 
    cout<<A<<","<<B<<endl<<endl;
    return 0;
}
