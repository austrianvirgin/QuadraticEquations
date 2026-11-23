CXX = g++
TARGET = quadratic

all: $(TARGET)
$(TARGET): main.o Quadratic.o
	$(CXX) -o $(TARGET) main.o Quadratic.o -lm
main: main.o Quadratic.o
	$(CXX) -o $(TARGET) main main.o Quadratic.o
%.o: %.cpp Quadratic.h
	$(CXX) -c $< -o $@
clean:
	rm -f *.o  $(TARGET)
