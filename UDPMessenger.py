# adapted from: https://pymotw.com/2/socket/udp.html

import socket, json, pydb
	
def UDPSend(msg):
	jsonMsg = json.dumps(msg)
	sendS.sendto(jsonMsg.encode('utf-8'), send_address)
	return jsonMsg

def UDPRec(bufMsg):
	return json.loads(bufMsg)
	
listenS = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
listenPort = 3600
listen_address = ('localhost', listenPort)
listenS.bind(listen_address)

sendS = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sendPort = 3601
send_address = ('localhost', sendPort)

while True:
	buf, address = listenS.recvfrom(listenPort)
	if not len(buf):
		break
	buf = buf.decode("utf-8")
	print(buf)
	jsonData = UDPRec(buf)
	
	if jsonData["type"] == "getAlarmTime":
		pydb.dbWrite(jsonData)
		msg = {"type":"notifyOfUpdate", "content":0}
		UDPSend(msg)
		
	elif jsonData["type"] == "timeRequest":
		alarmData = pydb.dbRead(jsonData)
		msg = {"type":"sendAlarmTime", "content":alarmData}
		UDPSend(msg)
		
	elif jsonData["type"] == "ack":
		break
	
	elif jsonData["type"] == "getLEDColour":
		msg = {"type":"setColour", "content":jsonData["content"]}
		UDPSend(msg)
		
	else:
		msg = {"type":"UNKNOWN", "content":0}
		UDPSend(msg)