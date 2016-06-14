src = provider.cpp smoker.cpp
pro = provider.cpp
smo = smoker.cpp
opt = -fpermissive -g -o
out = out.elf
out_pro = pro.elf
out_smo = smo.elf
cc = gcc 
all : ${pro} ${smo}
	make pro
	make smo
pro : ${pro}
	${cc} ${pro} ${opt} ${out_pro}
smo : ${smo}
	${cc} ${smo} ${opt} ${out_smo}
clean :
	rm ${out_pro} ${out_smo}
