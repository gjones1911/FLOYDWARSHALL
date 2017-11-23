# Generic makefile

all: FW gmaker gmkr GDFS GDIJ GDFS2 MFW MDFS MDIJ NegativeGraphDiv1

clean:
	rm -f FW  *.o

LIBS = $(HOME)/$(LIB)/libfdr.a
INCLUDE = $(HOME)/include
CC = gcc

.SUFFIXES: .cpp .c .o .out .hist .jgr .jps .eps .nt .bib .tab .tex .dvi .fig .txt .ps .pdf .bin .od .odh .odd .ppm .gif

.cpp.o: 
	g++ -c -I$(INCLUDE) $*.cpp

.c.o: 
	g++ -c -I$(INCLUDE) $*.c


FW: FW.cpp  
	g++ -O2 -o FW FW.cpp

NegativeGraphDiv1: NegativeGraphDiv1.cpp  
	g++ -O2 -o NegativeGraphDiv1 NegativeGraphDiv1.cpp

gmaker: RNDGPH.cpp
	g++ -o gmaker RNDGPH.cpp

gmkr: rdggph.cpp
	g++ -o gmkr rdggph.cpp

MFW: MkFW.cpp
	g++ -o MFW MkFW.cpp

MDFS: MkDFS.cpp
	g++ -o MDFS MkDFS.cpp

MDIJ: MkDIJ.cpp
	g++ -o MDIJ MkDIJ.cpp

GDFS: Ggph.cpp Ggph.h
	g++ -o GDFS Ggph.cpp

GDFS2: GDFS.cpp Ggph.h
	g++ -o GDFS2 GDFS.cpp

GDIJ: GDIJ.cpp Ggph.h
	g++ -o GDIJ GDIJ.cpp
