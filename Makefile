GPP_FLAGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -std=c++17

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
	g++ $(GPP_FLAGS) -Lbuild -lnumber_generator src/main.cc -o bin/main_c
