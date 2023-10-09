
all: dirs bin/ut_all

bin/ut_all: test/ut_all.cpp test/folder_test.h test/file_test.h src/folder.h src/file.h src/node.h src/iterator.h iterator.o src/dfs_iterator.h
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.h src/iterator.cpp
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
