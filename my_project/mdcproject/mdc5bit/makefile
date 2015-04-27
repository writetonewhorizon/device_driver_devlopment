all:header clean
header:header.o
	gcc -o compression5 header.o
header.o:header.c
	gcc -c header.c
clean:
	rm -rf header.o
next:decompression5 clear
decompression5:decompression5.o
	gcc -o decompression5 decompression5.o
decompression5.o:decompression5.c
	gcc -c decompression5.c
clear:
	rm -rf decompression5.o 
