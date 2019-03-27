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
    cout<<"三个坑 任意选一个 打开一个空的 改选 胜率"<<endl<<endl;


    srand((unsigned)time(NULL));
    int flag=rand()%3;//取一个坑放入奖项
    int sum=0;
    int P[3]={0};
    switch(flag)
    {
        case 0:
            P[0]=1;
            break;
        case 1:
            P[1]=1;
            break;
        case 2:
            P[2]=1;
            break;
    }
    for(int i=0;i<30000;i++)
    {
        int x=rand()%3;//0 1 2任选一个
        if(x!=flag)//中奖
        {
            cout<<flag<<","<<x<<endl;
            sum++;
        }
    }
    cout<<sum<<",30000"<<endl;

    return 0;
}


//#include<ctime>
//#include <iostream>
//using namespace std;
//int main()
//{
//    cout<<"三个坑 任意选一个 打开一个空的 不改选 胜率"<<endl<<endl;
//
//
//    srand((unsigned)time(NULL));
//    int flag=rand()%3;//取一个坑放入奖项
//    int sum=0;
//    int P[3]={0};
//    switch(flag)
//    {
//        case 0:
//            P[0]=1;
//            break;
//        case 1:
//            P[1]=1;
//            break;
//        case 2:
//            P[2]=1;
//            break;
//    }
//    for(int i=0;i<30000;i++)
//    {
//        int x=rand()%3;//0 1 2任选一个
//        if(x==flag)//中奖
//        {
//            cout<<flag<<","<<x<<endl;
//            sum++;
//        }
//    }
//    cout<<sum<<",30000"<<endl;
//
//    return 0;
//}
