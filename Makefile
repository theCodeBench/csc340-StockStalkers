SOURCE = main.cpp LoggingHelper.cpp macd.cpp yearlyHighAnalysis.cpp stosc.cpp support_resistance.cpp

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
INC = -Iinclude
CFLAGS = -Wall -O3 -std=c++11 $(INC)
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = -lPlatform -Llib

.PHONY: clean

# Targets include all, clean, debug, tar

all : ProgramTrader

ProgramTrader: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core ProgramTrader

debug: CXXFLAGS += -DDEBUG -g
debug: ProgramTrader

tar: clean
	tar zcvf ProgramTrader.tgz $(SOURCE) *.h Makefile

help:
	@echo "	make ProgramTrader  - same as make all"
	@echo "	make all   - builds the ProgramTrader target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core ProgramTrader"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

