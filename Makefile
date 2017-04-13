all: main.cpp
	g++ -o main main.cpp -IC:\Python27\include -LC:\Python27\libs -lpython27
