proj:	*.c *.h
	gcc -Wall -Wextra -g -fsanitize=address -o proj1 *.c
	