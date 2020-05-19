build:
	gcc -std=c99 -Wall ./src/*.c -llua -lm -ldl -o ./bin/main

clean:
	rm ./bin/main

run:
	./bin/main