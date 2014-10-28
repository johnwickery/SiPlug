# Project: sihook
# Makefile created by Dev-C++ 5.5.3

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = msimg32.o
LINKOBJ  = msimg32.o
LIBS     = -L"C:/App/Dev-Cpp/MinGW32/lib" -L"C:/App/Dev-Cpp/MinGW32/mingw32/lib" -static-libgcc  -luser32 -lgdi32 -lcomctl32
INCS     = -I"C:/App/Dev-Cpp/MinGW32/include"
CXXINCS  = -I"C:/App/Dev-Cpp/MinGW32/include" -I"C:/App/Dev-Cpp/MinGW32/lib/gcc/mingw32/4.7.2/include/c++"
BIN      = msimg32.dll
CXXFLAGS = $(CXXINCS) -DBUILDING_DLL=1
CFLAGS   = $(INCS) -DBUILDING_DLL=1
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CC) --share $(LINKOBJ) $(LIBS) -o $(BIN)

msimg32.o: msimg32.c
	$(CC) -c msimg32.c -o msimg32.o $(CFLAGS)
