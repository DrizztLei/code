src = OneWay.cpp
opt = -lstdc++ -fpermissive -g -o
out = out.elf
cc = gcc
all : ${src}
	make out
out : ${src}
	${cc} ${src} ${opt} ${out}
clean :
	rm ${out}
