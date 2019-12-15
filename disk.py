#!python3

allBlock = [
    [0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #FAT表
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #目录表1 (8byte-fileName, 4byte-fileSize, 4byte-fileStartBlock)
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #目录表2
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #目录表3
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #目录表4
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #留空
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00]
]




# 输入文件名, 返回文件大小 起始块 目录表
def fileInfo(filename):
    inName = str(filename)
    if(len(inName) > 8):
        print("Error Name")
        return 0,0,0
    
    for i in range(1,5):
        found = True
        for j in range(0,len(inName)):
            if(ord(inName[j]) != allBlock[i][j]):
                found = False
                break

        if(found == True):
            print("fileName: " + inName)
            #print("fileSize: " + str(allBlock[i][8]*16**0+allBlock[i][9]*16**2+allBlock[i][10]*16**4+allBlock[i][11]*16**6) + " Byte")
            fileSize = allBlock[i][8]*16**0+allBlock[i][9]*16**2+allBlock[i][10]*16**4+allBlock[i][11]*16**6
            #print("fileStart: " +hex(allBlock[i][12]*16**0+allBlock[i][13]*16**2+allBlock[i][14]*16**4+allBlock[i][15]*16**6))
            fileStart = allBlock[i][12]*16**0+allBlock[i][13]*16**2+allBlock[i][14]*16**4+allBlock[i][15]*16**6
            return fileSize,fileStart,i
    print("can not find file")
    return 0,0,0

# 列出所有文件的所有信息
def dir():
    for i in range(1,5):
        if(allBlock[i][0] != 0):
            name = ''
            size = 0
            start = 0

            for j in range(0,8):
                if(allBlock[i][j] == 0x00):
                    break
                name += chr(allBlock[i][j])
            size = allBlock[i][8]*16**0+allBlock[i][9]*16**2+allBlock[i][10]*16**4+allBlock[i][11]*16**6
            start = allBlock[i][12]*16**0+allBlock[i][13]*16**2+allBlock[i][14]*16**4+allBlock[i][15]*16**6
            print("Block " + str(i) + ":")
            print("fileName: " + str(name))
            print("fileSize: " + str(size))
            print("fileStart:" + str(start))
            print()








print("mkfile (filename) (filecontent): add file")
print("dir: show file list")
print("type (filename): cat file")
print("del (filename): delete file")
print("quit: quit")


userInput = input(">> ")

if(userInput == 'dir'):
    dir()
if(userInput == 'quit'):
    exit()