all: ghcdump ascii1.txt ascii4.txt ascii8.txt ascii12.txt ascii16.txt ascii.txt

ghcdump: ghcdump.c
	clang -g ghcdump.c -o ghcdump

ascii: ascii.c
	clang -g ascii.c -o ascii

ascii1.txt: ascii
	./ascii 1 > ascii1.txt

ascii4.txt: ascii
	./ascii 4 > ascii4.txt

ascii8.txt: ascii
	./ascii 8 > ascii8.txt

ascii12.txt: ascii
	./ascii 12 > ascii12.txt

ascii16.txt: ascii
	./ascii 16 > ascii16.txt

ascii.txt: ascii
	./ascii > ascii.txt

clean:
	rm -rf ghcdump ascii ascii1.txt ascii4.txt ascii8.txt ascii12.txt ascii16.txt ascii.txt
