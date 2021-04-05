all: queue

.PHONY: cpputest queue clean

cpputest/.git:
	git submodule update --init --recursive

cpputest/configure: cpputest/.git
	cd cpputest && autoreconf . -i

cpputest/Makefile: cpputest/configure
	cd cpputest && ./configure

cpputest/lib/CppUTestExt cpputest/lib/CppUTest &: cpputest/Makefile
	$(MAKE) -C cpputest

cpputest: cpputest/lib/CppUTestExt cpputest/lib/CppUTest

queue: cpputest
	$(MAKE) -C source

clean:
	$(MAKE) clean -C cpputest
	$(MAKE) clean -C source
