# CppUTest should live alongside the top level project directory
CPPUTEST_HOME = ../cpputest

CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES += -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
LDFLAGS += $(LD_LIBRARIES)

WARN = -Wall -Werror
CFLAGS += -std=c18 $(WARN)
CXXFLAGS += -std=c++17 $(WARN)

SRC_CXX = $(wildcard *.cpp)
SRC_C   = $(wildcard *.c)
SRC     = $(SRC_CXX) $(SRC_C)
OBJ_CXX = $(patsubst %.cpp,%.o,$(SRC_CXX))
OBJ_C   = $(patsubst %.c,%.o,$(SRC_C))
OBJ     = $(OBJ_CXX) $(OBJ_C)
DEP_CXX = $(patsubst %.cpp,%.d,$(SRC_CXX))
DEP_C   = $(patsubst %.c,%.d,$(SRC_C))
DEP     = $(DEP_CXX) $(DEP_C)

.PHONY : all clean test

all : test

test : AllTests
	./AllTests

AllTests : $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

-include $(DEP)

%.o : %.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $<

%.o : %.c Makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $<

clean : 
	$(RM) $(OBJ) $(DEP) AllTests
