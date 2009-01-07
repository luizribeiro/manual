SRCS = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp,%,$(SRCS))
CXX = g++
CXXFLAGS = -Wall -lm -lcrypt -O2 -pipe

%: $<.cpp
		$(CXX) $(CXXFLAGS) $< -o $@

all: $(TARGETS)

clean:
		rm $(TARGETS)
