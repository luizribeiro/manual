S = $(wildcard *.cpp)
T = $(S:.cpp=)

%: $<.cpp
		g++ -Wall -lm $< -o $@

all: $(T)

clean:
		rm $(T)
