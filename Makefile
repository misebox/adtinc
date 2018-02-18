# Makefile
all: main

clean:
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

# for coverage
cov: profile
	llvm-cov report -use-color=true -instr-profile default.profdata build/test/libadt-test -show-functions=true lib/vec.c >build/cov/report.txt
	less -R build/cov/report.txt
	llvm-cov show -use-color=true -instr-profile=default.profdata build/test/libadt-test  lib/ | less -R
profile: test
	mkdir -p build/cov
	llvm-profdata merge -o default.profdata default.profraw
