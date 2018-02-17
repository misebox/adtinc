# Makefile
all:
	clang -g -c vec.c
	clang++ -g test.cpp googletest/src/gtest_main.cc gtest/gtest-all.cc -I. -lpthread vec.o
	./a.out

test/build/libadt-test: lib/*.c include/*.h
	cd test/build && cmake .. && make

test: test/build/libadt-test
	test/build/libadt-test
