all:header clear
header:headerg.o
	gcc -o compression headerg.o
headerg.o:headerg.c
	gcc -c headerg.c
clear:
	rm -rf headerg.o
next:decompression clean
decompression:decompressiong.o
	gcc -o decompression decompressiong.o
decompressiong.o:decompressiong.c
	gcc -c decompressiong.c
clean:
	rm -rf decompressiong.o
