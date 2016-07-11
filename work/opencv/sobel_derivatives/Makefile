CC=g++
src=s_d.cpp
out=s_d.elf
necessary=`pkg-config --cflags --libs opencv`
all : 
	make demo
demo :
	${CC} ${necessary} ${src} -o ${out}
