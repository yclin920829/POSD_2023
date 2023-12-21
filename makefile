.phony: clean stat

FLAGS = -std=c++11 -Wfatal-errors -Wall

OBJ = obj/shape_iterator.o obj/unit_of_work.o obj/sqlite_drawing_mapper.o obj/painter_mapper.o obj/db_mode.o

SRC = src/sqlite_abstract_mapper.h src/builder.h src/compound.h src/domain_object.h src/sqlite_drawing_mapper.h src/drawing.h src/find_visitor.h src/iterator_factory.h src/painter_mapper.h src/painter.h src/scanner.h src/shape_iterator_factory.h src/shape_iterator.h src/shape_utils.h src/shape.h src/triangle.h src/unit_of_work.h src/visitor.h

TEST = test/ut.cpp test/compound_test.h test/db_test.h test/parser_test.h test/iterator_test.h test/parser_test.h test/triangle_test.h test/visitor_test.h

all: dir u_test 

u_test: clean_db $(SRC) $(TEST) $(OBJ)
	g++ $(FLAGS) test/ut.cpp $(OBJ) -o bin/ut -lsqlite3 -lgtest -lpthread

obj/shape_iterator.o: src/shape_iterator.h src/shape_iterator.cpp
	g++ $(FLAGS) -c src/shape_iterator.cpp -o obj/shape_iterator.o

obj/unit_of_work.o: src/unit_of_work.h src/unit_of_work.cpp
	g++ $(FLAGS) -c src/unit_of_work.cpp -o obj/unit_of_work.o

obj/sqlite_drawing_mapper.o: src/sqlite_drawing_mapper.h src/sqlite_drawing_mapper.cpp src/sqlite_abstract_mapper.h src/parser.h src/builder.h src/scanner.h
	g++ $(FLAGS) -c src/sqlite_drawing_mapper.cpp -o obj/sqlite_drawing_mapper.o

obj/painter_mapper.o: src/painter_mapper.h src/painter_mapper.cpp src/sqlite_abstract_mapper.h src/parser.h src/builder.h src/scanner.h
	g++ $(FLAGS) -c src/painter_mapper.cpp -o obj/painter_mapper.o

obj/db_mode.o: src/db_mode.h src/db_mode.cpp
	g++ $(FLAGS) -c src/db_mode.cpp -o obj/db_mode.o

dir:
	mkdir -p bin obj resource

clean: clean_db
	rm -f bin/* obj/*.o 
	
clean_db:
	rm -f resource/*.db

stat:
	wc -l src/* test/*.h test/*.cpp

clear:
	clear

me: clear clean all
	./bin/ut

git : 
	git add .
	git commit -m "Commit for Test"
	git push origin master