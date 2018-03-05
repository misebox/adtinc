# Makefile
all: main

clean:
	rm -r build/*

main: sample
# for sample executables
sample: lib/*.c include/*.h sample/*.c build/sample/Makefile
	cd build/sample && make clean && make && cd -
	@ for x in $$(ls build/sample/*_sample); do echo ---- $$x; $$x; done
build/sample/Makefile: sample/CMakeLists.txt
	mkdir -p build/sample
	cd build/sample && cmake ../../sample

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
	llvm-cov report -use-color=true -instr-profile default.profdata build/test/libadt-test -show-functions=true lib/*.c >build/cov/report.txt
	less -R build/cov/report.txt
	llvm-cov show -use-color=true -instr-profile=default.profdata build/test/libadt-test  lib/ | less -R
profile: test
	mkdir -p build/cov
	llvm-profdata merge -o default.profdata default.profraw
