CC = gcc
EXEC = HexEditor
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
OPTIONS = -Werror

all: $(EXEC)

%.o : %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) $(OPTIONS) -o $@ $^

clean :
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
