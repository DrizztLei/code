#all : thread_control.cpp
#	gcc -fpermissive -lstdc++ -lpthread thread_control.cpp -o a.out
src = thread_control.cpp
obj = thread_control.o
opt = -g 
all: thread_control:
thread_control: $(obj)
	gcc 	$(obj) -l pthread -o thread_control
thread_control.o: $(src)
	gcc 	$(opt) $(src)
clean:
	rm thread_control *.o
