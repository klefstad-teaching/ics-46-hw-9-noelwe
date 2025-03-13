CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

dijkstras: src/dijkstras_main.o src/dijkstras.o
	g++ $(CXXFLAGS) src/dijkstras_main.o src/dijkstras.o -o dijkstras

src/dijkstras_main.o: src/dijkstras_main.cpp
	g++ $(CXXFLAGS) -c src/dijkstras_main.cpp -o src/dijkstras_main.o

src/dijkstras.o: src/dijkstras.cpp
	g++ $(CXXFLAGS) -c src/dijkstras.cpp -o src/dijkstras.o

ladders: src/ladder_main.o src/ladder.o
	g++ $(CXXFLAGS) src/ladder_main.o src/ladder.o -o ladders

src/ladder_main.o: src/ladder_main.cpp
	g++ $(CXXFLAGS) -c src/ladder_main.cpp -o src/ladder_main.o

src/ladder.o: src/ladder.cpp
	g++ $(CXXFLAGS) -c src/ladder.cpp -o src/ladder.o

clean:
	rm -f main src/*.o