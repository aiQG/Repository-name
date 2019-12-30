#!/usr/bin/env python
#-*- coding:utf-8 -*-
import popen2,string

INFILE = "test"
creakfile = "./tinyELF"
pintool = "source/tools/ManualExamples/obj-intel64/inscount1.so"
CMD = "./pin -t " + pintool + " -- " + creakfile + " <" + INFILE#运行后输入参数#
choices = "ababcdefghijklmnopqrstuvwxyz0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&'()*+,-./:;<=>?@[\]^`{|}~"#自定义爆破字典顺序
input_length = 45#可能不会检查长度
flag = ''
threshold = 10#阀值设置很关键

def execlCommand(command):
    global f
    fin,fout = popen2.popen2(command)
    result1 = fin.readline()#获取程序打印信息
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


f = 1
while(f):
    l = 0#初始化计数器
    for i in choices:
        key = flag + i + '-'*(input_length-len(flag))#测试字符串
        print ">",key
        writefile(key)
        #CMD = "./pin -t " + pintool + " -- " + creakfile +' '+ key + " <" + INFILE #带参数运行
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
        if(n-l > threshold and l):#阀值设置很关键, l!=0
            print '+++++++'+'\n'
            flag += i
            break
        else:
            l = n
        print '---------------------------------------------'
    if len(flag) == input_length:
        break
print flag

