src_dnn=dnn.cpp
out_dnn=-o dnn
opt_dnn=`pkg-config --libs --cflags opencv`
debug_dnn=-g
cc_dnn=g++

all: ${src_dnn}
	make dnn
dnn: ${src_dnn}
	${cc_dnn} ${src_dnn} ${opt_dnn} ${debug_dnn} ${out_dnn}
clean:
	rm $(word 2 , ${out_dnn})
