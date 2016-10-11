src_read=read.cpp
out_read=-o read
opt_read=`pkg-config --libs --cflags opencv`
debug_read=-g
cc_train=g++

src_contours=contours.cpp
out_contours=-o contours
opt_contours=`pkg-config --libs --cflags opencv`
debug_contours=-g
cc_contours=g++
all:
	make read
	make contours
read:
	${cc_train} ${src_read} ${opt_read} ${debug_read} ${out_read}
contours:
	${cc_train} ${src_contours} ${opt_contours} ${debug_contours} ${out_contours}
clean:
	rm $(word 2 , ${out_read})
	rm $(word 2 , ${out_contours})
