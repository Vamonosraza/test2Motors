CC=gcc
CFLAGS=-I.
DEPS = lib/Config/DEV_Config.h lib/PCA9685/PCA9685.h gpioheader.h
OBJ = main.o lib/Config/DEV_Config.o lib/PCA9685/PCA9685.o gpioheader.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core main