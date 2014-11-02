# Makefie by sharmer

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = charsetdect.o
LINKOBJ  = charsetdect.o
LIBS     = -L"C:/App/Dev-Cpp/MinGW32/lib" -L"C:/App/Dev-Cpp/MinGW32/mingw32/lib" -L. -static-libgcc -luchardet
INCS     = -I"C:/App/Dev-Cpp/MinGW32/include" -I.
CXXINCS  = -I"C:/App/Dev-Cpp/MinGW32/include" -I"C:/App/Dev-Cpp/MinGW32/lib/gcc/mingw32/4.7.2/include/c++"
BIN      = charsetdect.exe
CXXFLAGS = $(CXXINCS)
CFLAGS   = $(INCS)
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CC) $(LINKOBJ) $(LIBS) -o $(BIN)

charsetdect.o: charsetdect.c
	$(CC) -c charsetdect.c -o charsetdect.o $(CFLAGS)
# DO NOT DELETE
