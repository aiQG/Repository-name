import requests
import os


path='/Users/zc/Desktop/try3/'
main='https://nhentai.net/g/'
main2='https://nhentai.net/search/?q=' #搜索
Dnumber=241736 #递减 (数字文件夹)
No=1 #(第几张)

#获取搜索关键字
flag=0
key=''
temp=input('输入一个搜索关键词(结束直接按回车):')
while temp!='':
    if flag!=0:
        key+='+'
    temp.replace(' ','-') #去除空格
    key+=temp
    flag=1
    temp=input('输入一个搜索关键词:')

main2=main2+key #组合key 

page=1 #设置起始页码
DNo=1 #当页第几个Dnumber (<=25)

for i in range(0,30): #循环30本 
    print(DNo)
    while 1: #下载图片
        
        url=main2+'&page='+str(page) #搜索结果页面
        r=requests.get(url) #连接网页
        strDnumber=r.text.split('href="/g/')[DNo].split('/" class="cover"')[0] #找Dnumber
        RealName=r.text.split('<div class="caption">')[DNo].split('</div></a></div>')[0] #找名称
        strNo=str(No) #转字符串 (第几张)
        url=main+strDnumber+'/'+strNo+'/' #组合(第几张)
        r=requests.get(url) #连接网页
        
        try:#连接200!
            r.raise_for_status()
                
            theJPG=r.text.split('"https://i.nhentai.net/galleries/')[-1].split('"')[0] #图片地址
            #theJPG=theJPG.encode('utf-8') #转成字符串
            theJPG='https://i.nhentai.net/galleries/'+theJPG
            #theD=theJPG.split('/')[-2] #文件夹名称
            theF=theJPG.split('/')[-1] #文件名称
            r=requests.get(theJPG) #连接图片
            
            #创建路径
            if No==1:
                print(RealName)
                os.makedirs(path+RealName)
            #保存
            with open(path+RealName+'/'+theF,'wb') as f:
                f.write(r.content)
            f.close()
            print(theF+' ok')
            No=No+1 #下一张

        except:#连接非200!
            break #结束下载
        
    No=1 #初始化No
    DNo+=1 #下一个 Dnumber
    if DNo>25: 
        DNo=1 #初始化DNo
        page+=1 #下一页
            

    



    
