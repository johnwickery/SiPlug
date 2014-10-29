# Makefie by sharmer

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = siutf8.o
LINKOBJ  = siutf8.o
LIBS     = -L"C:/App/Dev-Cpp/MinGW32/lib" -L"C:/App/Dev-Cpp/MinGW32/mingw32/lib" -static-libgcc  -luser32 -lgdi32 -lcomctl32
INCS     = -I"C:/App/Dev-Cpp/MinGW32/include"
CXXINCS  = -I"C:/App/Dev-Cpp/MinGW32/include" -I"C:/App/Dev-Cpp/MinGW32/lib/gcc/mingw32/4.7.2/include/c++"
BIN      = siutf8.dll
CXXFLAGS = $(CXXINCS) -DBUILDING_DLL=1
CFLAGS   = $(INCS) -DBUILDING_DLL=1
LIB      = ../lib/
RM       = rm -f
CP       = cp -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CC) --share $(LINKOBJ) $(LIBS) -o $(BIN)
	$(CP) $(BIN) $(LIB)

msimg32.o: siutf8.c
	$(CC) -c siutf8.c -o siutf8.o $(CFLAGS)
