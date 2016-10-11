UFLAG = -g  -Xcompiler -v \
		-gencode=arch=compute_20,code=sm_20\
		-gencode=arch=compute_20,code=compute_20\
		-O2
IFLAGS = -I$(CUDA_DIR)/include -I$(CUDA_SDK_DIR)/C/common/inc -I../include
LFLAGS = -L$(CUDA_DIR)/lib64 -L$(CUDA_SDK_DIR)/C/lib
PRG = cuda_test
$(PRG) : main.cu
	nvcc main.cu -o $(PRG) $(CUFLAG) $(IFLAGS) $(LFLAGS)
