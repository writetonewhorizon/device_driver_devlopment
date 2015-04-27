all:header operation clean
header:header.o
	gcc -o compression header.o
header.o:header.c
	gcc -c header.c
operation:
	./compression
clean:
	rm -rf header.o
decompress:decompression output clear
decompression:decompression.o
	gcc -o decompression decompression.o
decompression.o:decompression.c
	gcc -c decompression.c
output:
	./decompression
clear:
	rm -rf decompression.o

