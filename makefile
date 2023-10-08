
all: dirs bin/ut_all

bin/ut_all: test/ut_all.cpp test/folder_test.h test/file_test.h src/folder.h src/file.h src/node.h 
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp -o bin/ut -lgtest -lpthread

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
