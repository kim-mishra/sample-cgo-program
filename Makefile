GPP_FLAGS=-g -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -std=c++17

build: build-c-lib
	go build -o bin/main_go

clean:
	@rm -rf bin build

build-setup:
	@mkdir -p bin build

build-c-lib: build-setup 
	gcc $(GPP_FLAGS)  -c src/number_generator.cc -o build/number_generator.o
	ar rcs build/libnumber_generator.a build/number_generator.o

build-c-exe: build-c-lib
	g++ $(GPP_FLAGS) src/main.cc -Lbuild -lnumber_generator -o bin/main_c

# Linux only
setup-debug: 
	sudo apt install -y valgrind gdb

test-c-exe: build-c-exe
	valgrind --error-exitcode=1 --leak-check=full -s bin/main_c 1 10
