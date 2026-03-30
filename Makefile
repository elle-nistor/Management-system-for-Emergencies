build:
	gcc -o structs main.c functions.c
run:
	./structs
clean:
	rm structs
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./structs

