CUDA_PATH = /opt/cuda-10.2

CFLAGS = -I$(CUDA_PATH)/include
LDLIBS = -lcuda

libcuda.so.1: lib.c
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -fPIC -o libcuda.so.1 lib.c \
	    $(LDLIBS)

test: test.c libcuda.so.1
	$(CC) $(CFLAGS) $(LDFLAGS) -o test test.c $(LDLIBS)
	LD_LIBRARY_PATH=. ./test
