#!/usr/bin/env python
# coding=utf-8
import socket
def check_tcp_status(ip , port):
    sock = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
    server_address = (ip , port)
#   print "connection to %s,%s" % server_address
    sock.connect(server_address)
    message = "TCP INFO FROM CLIENT"
#   print "sending the message to server %s ." % ip
    sock.sendall(message)
#   print "closing socket . "
    sock.close()

if __name__ == "__main__":
   check_tcp_status("192.168.1.2" , 7274)
