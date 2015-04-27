all:header decompression clean clear
header:header.o
	gcc -o compression header.o
header.o:header.c
	gcc -c header.c
clean:
	rm -rf header.o 
#next:decompression clear
decompression:decompression3.o
	gcc -o decompression decompression3.o
decompression3.o:decompression3.c
	gcc -c decompression3.c
clear:
	rm -rf decompression3.o
