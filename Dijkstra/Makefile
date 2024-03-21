CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=dijkstra.bin

all: $(TARGET)

$(TARGET): dijkstra.cpp
	$(CXX) $(CXXFLAGS) dijkstra.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)