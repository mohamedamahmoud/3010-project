# Source: https://pymotw.com/2/socket/udp.html

import socket, sys, time

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
port = 3601
server_address = ('localhost', 3601)
s.bind(server_address)

while True:

    print ("Waiting to receive on port %d : press Ctrl-C or Ctrl-Break to stop " % port)

    buf, address = s.recvfrom(port)
    if not len(buf):
        break
    print ("Received %s bytes from %s %s: " % (len(buf), address, buf ))

s.shutdown(1)
