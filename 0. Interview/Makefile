all: build

targets = main.cpp command.cpp
flags = -lpthread -std=c++17
binary_name = conveyor

build:
	g++ $(targets) $(flags) -o $(binary_name)

clean:
	rm $(binary_name)