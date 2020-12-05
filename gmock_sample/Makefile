# コンパイラの指定
CC := g++
LDLIBS := -lgtest_main -lgtest -lgmock -lpthread
SRC := main.cc namespace_method.cc
TESTSRC := ./test/namespace_gtest.cpp

build:
	# Build with main
	$(CC) $(SRC) -o out.exe

public:
	# コンパイル&リンク
	$(CC) $(TESTPUB) $(LDLIBS) -o test.exe

private:
	mkdir -p ./pre
	# コンパイル&リンク
	$(CC) $(TESTPRI) $(LDLIBS) -o test.exe
	# プリコンパイルで不正な関数呼び出しになってしまうため
	# 常にビルド失敗する

functions:
	mkdir -p ./pre
	# プリコンパイル&関数呼び出し修正
	python3 ./preprocess_and_fix.py
	# コンパイル&リンク
	$(CC) $(PREFILES) $(LDLIBS) -o test.exe

clean:
	$(RM) *.exe *.o ./pre/*
	$(RM) -r ./pre