.PHONY : build

default :
	@echo "======================================="
	@echo "Please use 'make build' command to build it.."
	@echo "======================================="

INCLUDES += -I. -I../ -I../../ -I../../../ -I../../src -I/usr/local/include
LIBS = -L../ -L../../ -L../../../ -L/usr/local/lib

CFLAGS = -Wall -Wno-expansion-to-defined -O3 -fPIC --shared -Wl,-rpath,. -Wl,-rpath,.. -Wl,-rpath,/usr/local/lib

build:
	@$(CC) -o llzf.so lua_lzf.c lzf_c.c lzf_d.c $(CFLAGS) $(INCLUDES) $(LIBS) -lcore
	@mv *.so ../
