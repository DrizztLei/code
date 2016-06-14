src = barber.c customer.c
cus = customer.c
bar = barber.c
opt = -g -o
out = out.elf
out_cus = cus.elf
out_bar = bar.elf
cc = clang
all : ${cus} ${bar}
	make cus
	make bar
cus : ${cus}
	${cc} ${cus} ${opt} ${out_cus}
bar : ${bar}
	${cc} ${bar} ${opt} ${out_bar}
clean :
	rm ${out_cus} ${out_bar}
