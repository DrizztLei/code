src_train=train.cpp
out_train=-o train
opt_train=`pkg-config --libs --cflags opencv`
debug_train=-g
cc_train=g++

src_dnn=dnn.cpp
out_dnn=-o dnn
opt_dnn=`pkg-config --libs --cflags opencv`
debug_dnn=-g
cc_dnn=g++


all: ${src_train} ${src_dnn}
	make train
	make dnn
train: ${src_train}
	${cc_train} ${src_train} ${opt_train} ${debug_train} ${out_train}
dnn: ${src_dnn}
	${cc_dnn} ${src_dnn} ${opt_dnn} ${debug_dnn} ${out_dnn}
clean:
	rm $(word 2 , ${out_train})
	rm $(word 2 , ${out_dnn})
