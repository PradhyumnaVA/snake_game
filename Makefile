# file names
FILE := snake_game.c
HEADER := s_header
OUTPUT := snake_game

snake_game: ${OUTPUT}.o ${HEADER}.o
	gcc -o ${OUTPUT} *.o

snake_game.o: ${FILE} ${HEADER}.h
	gcc -Wall -Wextra -pedantic -c -g ${FILE}

s_header.o: ${HEADER}.c ${HEADER}.h
	gcc -Wall -Wextra -pedantic -c -g ${HEADER}.c

run: ${OUTPUT}
	./${OUTPUT}

clean:
	rm *.o ${OUTPUT}

# main : main.o ll_lib.o
# 	gcc -o main main.o ll_lib.o
# main.o : main.c ll_lib.h
# 	gcc -c -g main.c
# ll_lib.o : ll_lib.c ll_lib.h
# 	gcc -c -g ll_lib.c
# run : 
# 	./main > output.txt
# 	less output.txt
# clean : 
# 	rm main main.o ll_lib.o
