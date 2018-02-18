# Makefile
all: main

clean: cmake
	rm -r build/*

# for main
main: build/main/libadt-main
	build/main/libadt-main
build/main/libadt-main: lib/*.c include/*.h src/*.c build/main/Makefile
	cd build/main && make clean && make
build/main/Makefile: src/CMakeLists.txt
	mkdir -p build/main
	cd build/main && cmake ../../src

# for test
test: build/test/libadt-test
	build/test/libadt-test
build/test/libadt-test: lib/*.c include/*.h test/*.cpp build/test/Makefile
	cd build/test/ && make clean && make
build/test/Makefile: test/CMakeLists.txt
	mkdir -p build/test
	cd build/test && cmake ../../test
