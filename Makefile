# Makefile
all: main

clean: cmake
	rm -r build/*

# for main
build/main/Makefile: build/main/Makefile
	mkdir -p build/main
	cd build/main && cmake ../../src
build/main/libadt-main: lib/*.c include/*.h src/*.c build/main
	cd build/main && make clean && make
main: build/main/libadt-main
	build/main/libadt-main

# for test
build/test/Makefile: test/CMakeLists.txt
	mkdir -p build/test
	cd build/test && cmake ../../test
build/test/libadt-test: lib/*.c include/*.h test/*.cpp build/test/Makefile
	cd build/test/ && make clean && make
test: build/test/libadt-test
	build/test/libadt-test
