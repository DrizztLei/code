src = Train.cpp Ann.cpp
opt = -fpermissive -lstdc++ -lm
primary = -O2
radical = -O3
debug = -g
cc = gcc
out_primary = -o out_o2.elf
out_radical = -o out_o3.elf
out_debug = -o out_debug.elf
target = out.elf
all : ${src}
	make O2;
	make O3;
	make debug;
clean :
	rm ${target}
O2 :
	${cc} ${opt} ${primary} ${src} ${out_primary}
O3 :
	${cc} ${opt} ${radical} ${src} ${out_radical}
debug :
	${cc} ${opt} ${debug} ${src} ${out_debug}
