

import requests
import os

path='/Users/zc/Desktop/try2/'
main='https://nhentai.net/g/'
Dnumber=241736 #递减 (数字文件夹)
No=1 #(第几张)

for i in range(0,10): #循环 10 本
    while 1:
        
        strDnumber=str(Dnumber) #转字符串 (网页文件夹)
        strNo=str(No) #转字符串 (第几张)
        url=main+strDnumber+'/'+strNo+'/' #组合(第几张)
        r=requests.get(url) #连接网页
        
        try:#连接200!
            
            r.raise_for_status()
            
            theJPG=r.text.split('"https://i.nhentai.net/galleries/')[-1].split('"')[0] #图片地址
            #theJPG=theJPG.encode('utf-8') #转成字符串
            theJPG='https://i.nhentai.net/galleries/'+theJPG
            
            theD=theJPG.split('/')[-2] #文件夹名称
            theF=theJPG.split('/')[-1] #文件名称
            r=requests.get(theJPG) #连接图片
            
            #创建路径
            if No==1:
                os.makedirs(path+theD)
            #保存
            with open(path+theD+'/'+theF,'wb') as f:
                f.write(r.content)
                
            
            f.close()
            print(theD+'/'+theF+' ok')
            No=No+1 #下一张

        except:#连接非200!
            No=1 #初始化No
            Dnumber=Dnumber-1  #上一目录
            break
