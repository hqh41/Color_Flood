GCC= gcc -Wall -Wextra

ini_flood.o:ini_flood.c
	$(GCC) -c $<

ini_flood:ini_flood.o
	$(GCC) $< -o $@


