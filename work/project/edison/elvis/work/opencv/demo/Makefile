all :
	make demo
	make hello
	make display
demo:
	g++  demo.cpp -o demo -lopencv_core  -lopencv_highgui  -lopencv_video
hello:
	g++ hello.cpp -o hello -lopencv_core -lopencv_video -lopencv_highgui
display:
	g++ `pkg-config --libs --cflags opencv` display.cpp -o display
clean:
	rm demo hello display
