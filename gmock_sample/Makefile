# コンパイラの指定
CC := g++
LDLIBS := -lgtest_main -lgtest -lgmock -lpthread -g
SRC := main.cc namespace_method.cc namespace_interface.cc
TESTSRC := test_target.cc \
           namespace_interface.cc \
		   namespace_method.cc \
           ./test/test_target_gtest.cc \

build:
	# Build with main
	$(CC) $(SRC) -o out.exe

gtest:
	# コンパイル&リンク
	$(CC) $(TESTSRC) $(LDLIBS) -o test.exe

clean:
	$(RM) *.exe *.o
