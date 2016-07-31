#!/usr/bin/env python
# coding=utf-8

import socket
sock = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
server = ('192.168.1.2' , 7274)

print "starting up on %s %s" % server

sock.bind(server)

sock.listen(1)

while True:
    print "Waiting for a connection . "
    connection , client_address = sock.accept()
    try:
        print "Connection from : " , client_address
        data = connection.recv(1024)
        print "Receive %s" % data
    finally:
        connection.close();
