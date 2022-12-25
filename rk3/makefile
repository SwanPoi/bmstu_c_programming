CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm


SRCS := ./matrix_IO.c ./battle.c 
OBJS := ./matrix_IO.o ./battle.o


ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), gcov)
	CFLAGS += -g3
	CFLAGS += --coverage
	LDFLAGS += --coverage
endif

# Сборка исполняемых файлов
app.exe : $(OBJS) ./sea.o
	$(CC) $^ -o $@ $(LDFLAGS)


# Сборка объектных файлов
./%.o : ./%.c
	$(CC) $(CFLAGS) $< -c -o $@


.PHONY : clean func

clean:
	rm rm -f ./*.exe ./*.o 

