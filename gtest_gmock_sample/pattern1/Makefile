# コンパイラの指定
CC := g++
LDLIBS := -lgtest_main -lgtest -lgmock -lpthread
CFLAGS := -E
SRC := main.cpp functions.cpp shared_functions.cpp
TESTPUB := ./test/publicMethod_gtest.cpp
TESTPRI := ./test/privateMethod02_gtest.cpp \
           ./test/privateMethod01_gtest.cpp
TESTFUNCTIONS := $(TESTPRI)
TESTFUNCTIONS += $(TESTPUB)

# pre内のプリコンパイル・修正済みファイル
PREDIR := ./pre
PREFILES := $(addprefix $(PREDIR)/, $(notdir $(TESTFUNCTIONS)))

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