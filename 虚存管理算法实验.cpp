#include <time.h>
#include <iostream>
#include <queue>

#define N 10000 //任务总数
#define X 11    //总空闲块数

using namespace std;

unsigned int times = 0;

struct mession
{
    unsigned int index; //任务序号
    unsigned int need;  //需要的页
};

mession waitList[N];

queue<mession *> block;

void messionInit()
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++)
    {
        waitList[i].index = i;
        waitList[i].need = rand() % (X + 1);
    }
    return;
}
//-------------------------------

void FIFO()
{
    bool isUsing = false;
    mession *checkBuffer = NULL;
    for (int i = 0; i < N; i++)
    {
        isUsing = false;
        checkBuffer = NULL;
        if (block.empty())
        {
            block.push(waitList + i);
            cout << "1" << endl;
        }
        else
        {
            //是否已正在使用
            for (int j = 0; j < block.size(); j++)
            {
                checkBuffer = block.front();
                block.pop();
                block.push(checkBuffer);
                if (checkBuffer->need == waitList[i].need)
                {
                    isUsing = true;
                }
            }
            //正在使用
            if (isUsing)
            {
                cout << "isUsing" << endl;
                isUsing = false;
                checkBuffer = NULL;
                continue;
            }
            //没有正在使用
            else
            {
                cout << "Aaaa" << block.size() << endl;
                //没满
                if (block.size() < X)
                {
                    block.push(waitList + i);
                    cout << "美满" << endl;
                }
                //满了
                else if (block.size() == X)
                {
                    cout << "aaa" << block.size() << endl;
                    block.pop();
                    block.push(waitList + i);
                    cout << "满了" << endl;
                    times++;
                }
                else
                {
                    cout << "ERROR!" << endl;
                }
            }
        }
    }
    cout << N << "  " << times << endl;
    return;
}
//-------------------------------
struct blockLRU
{
    unsigned int index;     //下标
    unsigned int usingWhat; //当前是页标
    unsigned int weight;    //权值
};

blockLRU LRUList[X];
void LRUListrInit()
{
    for (int i = 0; i < X; i++)
    {
        LRUList[i].index = i;
        LRUList[i].usingWhat = -1;
        LRUList[i].weight = 0; //最低权值
    }
    return;
}

void LRU()
{
    bool isUsing = false;
    unsigned int checkWeight = 0;
    int checkWeightIndex = 0;
    for (int i = 0; i < N; i++)
    {
        cout << "----------------------" << endl;
        //检查是否正在使用
        for (int j = 0; j < X; j++)
        {
            if (waitList[i].need == LRUList[j].usingWhat && LRUList[j].weight != 0)
            {
                cout << "using" << endl;
                isUsing = true;
                LRUList[j].weight = i + 1;
            }
        }
        if (isUsing)
        {
            //正在使用
            isUsing = false;
            checkWeight = 0;
            checkWeightIndex = 0;
            continue;
        }
        else
        {
            checkWeight = LRUList[0].weight;
            checkWeightIndex = 0;
            for (int j = 0; j < X; j++)
            {
                //找权值小的
                if (LRUList[j].weight < checkWeight)
                {
                    checkWeight = LRUList[j].weight;
                    checkWeightIndex = j;
                }
            }
            LRUList[checkWeightIndex].weight = i + 1;
            LRUList[checkWeightIndex].usingWhat = waitList[i].need;
            cout << "替换" << endl;
            times++;
        }
        isUsing = false;
        checkWeight = 0;
        checkWeightIndex = 0;
    }
    cout << N << " " << times << endl;
    return;
}

//-------------------------------
struct CLOCKBlock
{
    unsigned int index;
    unsigned int Need; //正在使用的页号
    bool isUsing;      //是否被引用
};

CLOCKBlock clockList[X];

void CLOCKBlockInit()
{
    for (int i = 0; i < X; i++)
    {
        clockList[i].index = i;
        clockList[i].isUsing = false;
        clockList[i].Need = -1;
    }
    return;
}

void CLOCK()
{
    unsigned int index = 0; //计数用
    bool isUsing = false;
    for (int i = 0; i < N; i++)
    {
        //检查是否正在使用
        for (int j = 0; j < X; j++)
        {
            if (clockList[j].Need == waitList[i].need)
            {
                clockList[j].isUsing = true;
                isUsing = true;
            }
        }
        //正在使用
        if (isUsing)
        {
            cout << "using" << endl;
            isUsing = false;
            continue;
        }
        //没在使用
        else
        {
            while (true)
            {
                if (clockList[index % X].isUsing)
                {
                    clockList[index % X].isUsing = false;
                    cout << "next" << endl;
                }
                else
                {
                    cout << "替换" << endl;
                    clockList[index % X].Need = waitList[i].need;
                    clockList[index % X].isUsing = true;
                    index++;
                    times++;
                    break;
                }
                index++;
                index %= X;
            }
        }
    }
    cout << N << " " << times << endl;
    return;
}

int main()
{
    messionInit();
    //------------------------
    FIFO();

    //------------------------

    //LRUListrInit();
    //LRU();

    //------------------------

    // CLOCKBlockInit();
    //CLOCK();

    return 0;
}
