# Executable
main: list.o test.o
	gcc -o $@ $^

# Compile source files
%.o: %.c list.h
	gcc -c $<

# Clean rule
clean:
	rm -f main *.o
