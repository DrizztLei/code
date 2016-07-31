import socket
import time
import cv2
import numpy as np
from struct import unpack

def showImage(windowName,array):
    cv2.imshow(windowName,array)

def server(host,port):
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host,port))
    s.listen(5)
    c,addr=s.accept()
    while(1):    
        data=c.recv(4)
        width=unpack('>I', data[0:4])[0]
        data2=c.recv(4)
        height=unpack('>I', data2[0:4])[0]
        totalpixels=width*height
        data3=recvall(c,totalpixels)
        frame=np.fromstring(data3,dtype=np.uint8)   
        frame=frame.reshape(height,width)
        cv2.setUseOptimized(True)
        cv2.namedWindow("Driver", cv2.WINDOW_NORMAL)
        cv2.imshow("Driver",frame)
    cv2.waitKey(0)
    cv2.destroyAllWindows()



    return data
def recvall(sock,n):
    data=''
    while len(data)<n:
        chunk=sock.recv(n-len(data))
        if not chunk:
            return None
        data+=chunk

    return data


if __name__=="__main__":
        server('localhost',9999)
