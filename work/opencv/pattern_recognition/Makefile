src_train=train.cpp
out_train=-o train
opt_train=`pkg-config --libs --cflags opencv`
debug_train=-g
cc_train=g++

all: ${src_train}
	make train
train: ${src_train}
	${cc_train} ${src_train} ${opt_train} ${debug_train} ${out_train}
clean:
	rm $(word 2 , ${out_train})
