all : HW1

HW1 : hw1.o testcase.o validate_64.o
	gcc -o HW1 hw1.o testcase.o validate_64.o
	
testcase.o : testcase.c hw1.h
	gcc -c testcase.c
	
hw1.o : hw1.c hw1.h
	gcc -c hw1.c hw1.h

clean:
	rm -f testcase.o hw1.o 
