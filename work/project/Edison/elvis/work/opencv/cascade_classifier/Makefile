CC=g++
src=temp.cpp
try=try.cpp
out_try=try.elf
out=temp.elf
necessary=`pkg-config --cflags --libs opencv` -lstdc++ -O3

all :
	make demo
	make try
demo :
	${CC} ${necessary} ${src} -o ${out}
try :
	${CC} ${necessary} ${try} -o ${out_try}
clean :
	rm ${out_try} ${out}
