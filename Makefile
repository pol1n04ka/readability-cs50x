readability: readability.c 
	gcc -Wall -Wextra -std=c11 -o readability readability.c -lcs50

clean:
	rm -f readability
