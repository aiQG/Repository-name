#!/usr/bin/env python
#-*- coding:utf-8 -*-
import popen2,string

INFILE = "test"
creakfile = "./move"
pintool = "source/tools/ManualExamples/obj-ia32/inscount1.so"
CMD = "./pin -t " + pintool + " -- " + creakfile + " <" + INFILE

maxLength = 40

def execlCommand(command):
    global f
    fin,fout = popen2.popen2(command)
    result1 = fin.readline()#获取程序自带打印信息，wrong或者correct
    #print result1
#可以根据程序输出
#    if(result1 != 'Input : Wrong\n'):#输出Correct时终止循环
#        f = 0
    result2 = fin.readline()#等待子进程结束,结果输出完成
    fin.close()


#写出结果
def writefile(data):
    fi = open(INFILE,'w')
    fi.write(data)
    fi.close()

l = 0#初始化计数器
for i in range(maxLength):
    key = 'A'*i #'flag{'+i * 'A'+'}'#测试字符串
    print str(i),">",key
    writefile(key)
    execlCommand(CMD)
    fi = open('inscount.out')
    while(1):
        try:
            n = int(fi.read().split(' ')[1], 10)
            break
        except IndexError:
            continue
    fi.close()
    print str(n)+'---->'+str(n-l)
    if n-l>100 :
        print '++++++++++++++++++'
    l = n
    print '----------------------------------------------'
        
