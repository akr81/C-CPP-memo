# コンパイラの指定
CC := g++
LDLIBS := -lgtest_main -lgtest -lgmock -lpthread
SRC := main.cpp
TESTPUB := ./test/publicMethod_gtest.cpp
TESTFUNCTIONS += $(TESTPUB)

build:
	# Build with main
	$(CC) $(SRC) -o out.exe

gtest:
	# コンパイル&リンク
	$(CC) $(TESTPUB) $(LDLIBS) -o test.exe

clean:
	$(RM) *.exe *.o
