CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS := ./src/my_snprintf.c ./src/specifier_functions.c
OBJS := ./out/my_snprintf.o ./out/specifier_functions.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_pop_front.c ./unit_tests/check_append.c
CHECK_OBJS := ./out/check_main.o ./out/check_my_snprintf.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), gcov)
	CFLAGS += -g3
	CFLAGS += --coverage
	LDFLAGS += --coverage
endif

# Сборка исполняемых файлов
unit_tests.exe: $(CHECK_OBJS) $(OBJS)
	$(CC) $^ -o $@ $(CHECK_FLAGS)

# Сборка объектных файлов
./out/%.o : ./src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

./out/%.o : ./unit_tests/%.c
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $< -c -o $@

.PHONY : clean unit

clean:
	rm rm -f ./*.exe ./out/*.o ./out/*.gcda ./out/*.gcno ./out/*.gcov ./out/*.txt ./out/*.d ./*.gcov

unit:
	./unit_tests.exe

