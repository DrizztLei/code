src = provider.c smoker.c
pro = provider.c
smo = smoker.c
opt = -g -o
out = out.elf
out_pro = pro.elf
out_smo = smo.elf
cc = clang

pro : ${pro}
	${cc} ${pro} ${opt} ${out_pro}
smo : ${smo}
	${cc} ${smo} ${opt} ${out_smo}
clean :
	rm ${out_pro} ${out_smo}
