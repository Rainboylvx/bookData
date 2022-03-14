all: sam showDot

sam : sam.cpp
	g++ -g -o sam sam.cpp

showDot:
	./sam < in > 1.dot
	dot2png.py
	sxiv 1.png

