CC=g++
src=temp.cpp
try=try.cpp
out_try=try.elf
out=temp.elf
necessary=`pkg-config --cflags --libs opencv` -lstdc++
all : 
	make demo
	make try
demo :
	${CC} ${necessary} ${src} -o ${out}
try :
	${CC} ${necessary} ${try} -o ${out_try}

