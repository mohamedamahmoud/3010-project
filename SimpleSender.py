# Source: https://pymotw.com/2/socket/udp.html

import socket, sys, time, json

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 3601)
#msg = { "type":"timeRequest", "content":0}
#data = json.dumps(msg)
data = "1234"


while True:
    if not len(data):
        break
    s.sendto(data.encode('utf-8'), server_address)
    s.shutdown
    
    time.sleep(10)
