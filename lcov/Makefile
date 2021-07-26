fresh: clean binaries build-case no-trigger trigger cov

clean:
	rm -rf code_coverage
	rm -rf output/
	rm -rf *.cov *.gcov *.gcda *.gcno
	rm -rf nohup.out
	rm -rf simple simple_cov
	rm -rf *.out

binaries:
	clang -fprofile-arcs -ftest-coverage -g -o simple_cov simple.c
	afl-clang-fast -static -fsanitize=address,undefined -Wformat -Werror=format-security -Werror=array-bounds -g -o simple simple.c

build-case:
	dd bs=1 if=/dev/urandom of=in/testcase_1 count=16

no-trigger:
	cat in/testcase_1 | ./simple

trigger:
	echo `perl -e 'print "A"x1000'` | ./simple

cov:
	cat in/testcase_1 | ./simple_cov
	lcov --directory . --base-directory . --gcov-tool /usr/local/bin/llvm-gcov --capture -o code_coverage
	genhtml code_coverage -o output
	firefox output/index.html
