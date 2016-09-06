cvlc -vvv  rtsp://admin:123456@192.168.1.10:554 --sout '#transcode{vcodec=h264,venc=x264{qp=99},scale=Auto,width=1024,acodec=none}:http{mux=ffmpeg{mux=flv},dst=:8080/}'
