ffserver -f /etc/ffserver.conf 1>server_info 2>server_err &
ffmpeg -an -i  rtsp://admin:123456@192.168.1.10:554/ch1/sub/av_stream -vcodec copy http://localhost:8080/feed1.ffm 1>ffmpeg_info 2>ffmpeg_err &
#ffmpeg -an -i  rtsp://admin:123456@192.168.1.10:554/ch1/main/av_stream -vcodec copy http://localhost:8080/feed1.ffm 1>ffmpeg_info 2>ffmpeg_err &
