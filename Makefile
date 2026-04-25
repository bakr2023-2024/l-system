.PHONY: clean
main: main.cpp
	g++ --std=c++20 -o lsystem main.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
clean:
	rm -rf *.exe