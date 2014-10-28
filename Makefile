# Project: sihook
# Makefile created by Dev-C++ 5.5.3

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = mdiclient.o siframe.o sihook.o sisw.o tabctl.o utils.o
LINKOBJ  = mdiclient.o siframe.o sihook.o sisw.o tabctl.o utils.o
LIBS     = -L"C:/App/Dev-Cpp/MinGW32/lib" -L"C:/App/Dev-Cpp/MinGW32/mingw32/lib" -static-libgcc  -luser32 -lgdi32 -lcomctl32
INCS     = -I"C:/App/Dev-Cpp/MinGW32/include"
CXXINCS  = -I"C:/App/Dev-Cpp/MinGW32/include" -I"C:/App/Dev-Cpp/MinGW32/lib/gcc/mingw32/4.7.2/include/c++"
BIN      = sihook.dll
CXXFLAGS = $(CXXINCS) -DBUILDING_DLL=1
CFLAGS   = $(INCS) -DBUILDING_DLL=1
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CC) --share $(LINKOBJ) $(LIBS) -o $(BIN)

mdiclient.o: mdiclient.c
	$(CC) -c mdiclient.c -o mdiclient.o $(CFLAGS)

siframe.o: siframe.c
	$(CC) -c siframe.c -o siframe.o $(CFLAGS)

sihook.o: sihook.c
	$(CC) -c sihook.c -o sihook.o $(CFLAGS)

sisw.o: sisw.c
	$(CC) -c sisw.c -o sisw.o $(CFLAGS)

tabctl.o: tabctl.c
	$(CC) -c tabctl.c -o tabctl.o $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c -o utils.o $(CFLAGS)
