def huaxingxing(l):
    for i in [1,2,3,4,5]:
        t.forward(l)# 先画左角向右
        t.left(72)
        t.forward(l)
        t.right(144)

def huaxiaoxingxing(x,y,p): #x,y是坐标，p是星星开始画的方向
    t.goto(x,y)
    t.down()#画之前要下笔
    t.begin_fill()#准备好涂色
    t.setheading(p)#调转好方向
    huaxingxing(20)#开始画
    

import turtle as t
import math as m

t.hideturtle()
t.speed(10)#设置画画速度
t.setup(1200,800)#设置窗口大小
#画背景
t.color('red')
t.begin_fill()
t.goto(300,200)
t.goto(300,-200)
t.goto(-300,-200)
t.goto(-300,200)
t.goto(300,200)
t.end_fill()
t.home()
#画大星星
t.goto(-260,120)
t.color('yellow')
t.begin_fill()
huaxingxing(40)
t.end_fill()
#画第一个小星星
t.up()
t.goto(-200,100)
huaxiaoxingxing(-(5*20+1*m.cos(m.degrees(m.atan(3/5)))),8*20-1*m.sin(m.degrees(m.atan(3/5))),36)
t.end_fill()
#画第二个小星星
t.up()
t.goto(-200,100)
huaxiaoxingxing(-(3*20+1*m.cos(m.degrees(m.atan(1/7)))),6*20-1*m.sin(m.degrees(m.atan(1/7))),18)
t.end_fill()
#画第三个小星星
t.up()
t.goto(-200,100)
huaxiaoxingxing(-(3*20+1*m.cos(m.degrees(m.atan(2/7)))),3*20+1*m.sin(m.degrees(m.atan(2/7))),0)
t.end_fill()
#画第四个小星星
t.up()
t.goto(-200,100)
huaxiaoxingxing(-(5*20+1*m.cos(m.degrees(m.atan(4/5)))),1*20+1*m.sin(m.degrees(m.atan(4/5))),-18)
t.end_fill()
#释放内存
t.done()
