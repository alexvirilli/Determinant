all: det

det: det.c
	gcc -g -Wall -Werror -fsanitize=address -std=c11 det.c -o det

clean:
	rm -rf det
