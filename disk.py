#!python3
import math
global allBlock
allBlock = [
    [0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #FAT表(其他值只能为6~15)
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #目录表1 (8byte-fileName, 4byte-fileSize, 4byte-fileStartBlock)
    [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],      #目录表2 (fileStartBlock 6~15)
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
        # print("Error Name")
        return 0,0,0
    
    for i in range(1,5):
        found = True
        for j in range(0,len(inName)):
            if(ord(inName[j]) != allBlock[i][j]):
                found = False
                break
            if(inName[j+1:] == '' and allBlock[i][j+1] != 0x00):
                found = False
                break

        if(found == True):
            # print("fileName: " + inName)
            # print("fileSize: " + str(allBlock[i][8]*16**0+allBlock[i][9]*16**2+allBlock[i][10]*16**4+allBlock[i][11]*16**6) + " Byte")
            fileSize = allBlock[i][8]*16**0+allBlock[i][9]*16**2+allBlock[i][10]*16**4+allBlock[i][11]*16**6
            # print("fileStart: " +hex(allBlock[i][12]*16**0+allBlock[i][13]*16**2+allBlock[i][14]*16**4+allBlock[i][15]*16**6))
            fileStart = allBlock[i][12]*16**0+allBlock[i][13]*16**2+allBlock[i][14]*16**4+allBlock[i][15]*16**6
            return fileSize,fileStart,i # i表示在第几块目录表
    # print("can not find this file")
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

def typeFile(fileName):
    size, start, m = fileInfo(fileName)
    if( m == 0 ):
        print("can not find this file")
        return False
    assert size != 0
    tempStr = ''
    while(start != 0x00):
        if(start == 0xFF):
            print()
            print(tempStr)
            return True
        if(not (6 <= start <= 15)):
            print(tempStr)
            print("startBlockError")
            print(str(start))
            return False
        for c in allBlock[start]:
            if(c == 0x00):
                break
            tempStr += chr(c)
        
        start = allBlock[0][start]
    print(tempStr)
    print("file not end")
    return False


def mkfile(fileName, fileContent):
    global allBlock
    # 文件目录列表
    mPlace = 0
    for i in range(1, 5):
        if(allBlock[i][0] == 0x00):
            mPlace = i
            break
    if(mPlace == 0):
        print("Files Num Limited")
        return False

    if(not(0<len(fileName)<=7)):
        print("fileName length error")
        return False
    fileContent += '\x00' # 0x00结束
    willUseBlocksNum = math.ceil((len(fileContent))/16.0) 
    unUsedBlocksNum = 0
    emptyList = []
    for i in range(0, len(allBlock[0])):
        if(allBlock[0][i] == 0x00):
            unUsedBlocksNum += 1
            emptyList += [i]
    if(willUseBlocksNum > unUsedBlocksNum or unUsedBlocksNum == 0):
        print("space not enough")
        if(unUsedBlocksNum == 0):
            print("disk full")
        return False
    size, start, m = fileInfo(fileName)
    if(m != 0x00 or start != 0x00):
        print("File exists")
        return False
    assert size == 0x00

    # fileName
    for i in range(0, len(fileName)):
        allBlock[mPlace][i] = ord(fileName[i])
    # fileSize
    allBlock[mPlace][ 8] = (len(fileContent) >>  0) & 0xFF
    allBlock[mPlace][ 9] = (len(fileContent) >>  8) & 0xFF
    allBlock[mPlace][10] = (len(fileContent) >> 16) & 0xFF
    allBlock[mPlace][11] = (len(fileContent) >> 24) & 0xFF
    # fileStart
    allBlock[mPlace][12] = ((emptyList[0]) >>  0) & 0xFF
    allBlock[mPlace][13] = ((emptyList[0]) >>  8) & 0xFF
    allBlock[mPlace][14] = ((emptyList[0]) >> 16) & 0xFF
    allBlock[mPlace][15] = ((emptyList[0]) >> 24) & 0xFF
    # 写内容 + FAT表
    tempEnd = False
    for i in range(0, willUseBlocksNum):
        for j in range(0, min(len(allBlock[emptyList[i]]), len(fileContent[i*len(allBlock[emptyList[i]]): (i+1)*len(allBlock[emptyList[i]])]))):
            allBlock[emptyList[i]][j] = ord(fileContent[i*len(allBlock[emptyList[i]])+j])
            if(ord(fileContent[i*len(allBlock[emptyList[i]])+j]) == 0x00):
                tempEnd = True
        if(tempEnd):
            print("0xFF")
            allBlock[0][emptyList[i]] = 0xFF
            break
        else:
            print(hex(emptyList[i+1]))
            allBlock[0][emptyList[i]] = emptyList[i+1]
    print("write OK")
    return True

def delFile(fileName):
    global allBlock
    size, start, m = fileInfo(fileName)
    assert size!=0
    if(m == 0x00 or start == 0x00):
        print("File does not exist")
        return False
    allBlock[start] = [0x00]*len(allBlock[start])
    nextBlock = allBlock[0][start]
    allBlock[0][start] = 0x00
    while(nextBlock != 0xFF):
        start = nextBlock
        allBlock[start] = [0x00]*len(allBlock[start])
        nextBlock = allBlock[0][start]
        allBlock[0][start] = 0x00
    allBlock[m] = [0x00]*len(allBlock[m])
    return True




print("mkfile (filename) (filecontent): add file")
print("dir: show file list")
print("type (filename): cat file")
print("del (filename): delete file")
print("quit: quit")

while(True):
    userInput = input(">> ")

    cmd = userInput.split(' ')
    try:
        if(cmd[0] == 'mkfile'):
            mkfile(cmd[1], cmd[2])
        if(cmd[0] == 'del'):
            delFile(cmd[1])
        if(cmd[0] == 'type'):
            typeFile(cmd[1])
        if(cmd[0] == 'dir'):
            dir()
        if(cmd[0] == 'quit'):
            exit()
        if(cmd[0] == '?'):
            print(allBlock)
    except:
        print("somethingError")

