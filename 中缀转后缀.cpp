//
//  main.cpp
//  123
//
//  Created by 周测 on 2018/11/22.
//  Copyright © 2018 周测. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

void mTob(string& input,string& output)
{
    stack<char> ch;
    
    for(int i=0;i<input.length();i++)
    {
        if(input[i]==')')
        {
            while(ch.top()!='(')
            {
                output+=ch.top();
                //cout<<ch.top();
                ch.pop();
            }
            ch.pop();
        }
        else if(input[i]<='z'&&input[i]>='a')
        {
            output+=input[i];
            //cout<<input[i];
        }
        else
        {
            if(ch.empty())
            {
                ch.push(input[i]);
            }
            else
            {
                switch(input[i])
                {
                    case '+':
                        while((!ch.empty())&&(ch.top()=='*'||ch.top()=='/'||ch.top()=='+'||ch.top()=='-'))
                    {
                        output+=ch.top();
                        //cout<<ch.top();
                        ch.pop();
                    }
                        ch.push(input[i]);
                        break;
                    case '-':
                        while((!ch.empty())&&(ch.top()=='*'||ch.top()=='/'||ch.top()=='+'||ch.top()=='-'))
                    {
                        output+=ch.top();
                        //cout<<ch.top();
                        ch.pop();
                    }
                        ch.push(input[i]);
                        break;
                    case '*':
                        ch.push(input[i]);
                        break;
                    case '/':
                        ch.push(input[i]);
                        break;
                    case '(':
                        ch.push(input[i]);
                        break;
                }
            }
        }
    }
    while(!ch.empty())
    {
        output+=ch.top();
        //cout<<ch.top();
        ch.pop();
    }
    
    //cout<<endl<<output<<endl;
}


int main()
{
    string I="a+b*c+(d*e+f)*g";
    string O="";
    
    mTob(I, O);
    
    cout<<O<<endl;
    return 0;
}
//abc*+de*f+g*+
