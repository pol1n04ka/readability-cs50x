readability: readability.c 
	gcc -Wall -Wextra -std=c11 -o readability readability.c -lcs50 -lm

clean:
	rm -f readability
