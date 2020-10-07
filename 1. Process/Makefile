all: build

targets = main.cpp process.cpp
flags = -Wno-pointer-arith -std=c++17
binary_name = process.out

build:
	g++ $(targets) $(flags) -o $(binary_name)

clean:
	rm $(binary_name)