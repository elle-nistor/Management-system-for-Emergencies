build:
	gcc -o tema1 main.c functions.c
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema1

