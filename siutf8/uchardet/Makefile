# Makefie by sharmer

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
LIBS     = -L"C:/App/Dev-Cpp/MinGW32/lib" -L"C:/App/Dev-Cpp/MinGW32/mingw32/lib" -static-libgcc
INCS     = -I"C:/App/Dev-Cpp/MinGW32/include"
CXXINCS  = -I"C:/App/Dev-Cpp/MinGW32/include" -I"C:/App/Dev-Cpp/MinGW32/lib/gcc/mingw32/4.7.2/include/c++"
BIN      = uchardet.dll
CXXFLAGS = $(CXXINCS) -DBUILDING_DLL=1
CFLAGS   = $(INCS) -DBUILDING_DLL=1
RM       = rm -f
CP       = cp -f
SOURCE   = $(wildcard *.cpp)
OBJ      = $(patsubst %.cpp,%.o,$(SOURCE)) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

%.o: %.cpp
	$(CPP) $(CXXFLAGS) $(CXXINCS) -c $<

$(BIN): $(OBJ)
	echo $(OBJ)
	$(CPP) --share $(OBJ) $(LIBS) -o $(BIN)

