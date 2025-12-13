# Compiler
CXX = clang++

CXXFLAGS = --target=x86_64-w64-windows-gnu -std=c++17 \
  -IC:/mingw64/include/c++/15.2.0 \
  -IC:/mingw64/include/c++/15.2.0/x86_64-w64-mingw32 \
  -IC:/mingw64/x86_64-w64-mingw32/include \
  -IC:/mingw64/include


OBJS = src/main.o src/widget.o src/terminal.o src/container.o
TARGET = build/main.exe


all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

widget.o: src/widget.cpp src/widget.h
	$(CXX) $(CXXFLAGS) -c src/widget.cpp -o src/widget.o

terminal.o: src/terminal.cpp src/terminal.h
	$(CXX) $(CXXFLAGS) -c src/terminal.cpp -o src/terminal.o

container.o: src/container.cpp src/container.h
	$(CXX) $(CXXFLAGS) -c src/container.cpp -o src/container.o

clean:
	rm src/*.o build/main.exe
