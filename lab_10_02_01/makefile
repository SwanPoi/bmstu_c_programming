CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS := ./src/list_functions.c ./src/struct_IO.c ./src/polynomial_func.c ./src/polynomial_process.c
OBJS := ./out/list_functions.o ./out/struct_IO.o ./out/polynomial_func.o ./out/polynomial_process.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_pop_front.c ./unit_tests/check_pop_back.c ./unit_tests/check_append.c ./unit_tests/check_front_back_split.c ./unit_tests/check_sort.c  ./unit_tests/check_sorted_merge.c
CHECK_OBJS := ./out/check_main.o ./out/check_pop_front.o ./out/check_pop_back.o ./out/check_append.o ./out/check_front_back_split.o ./out/check_sort.o ./out/check_sorted_merge.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), gcov)
	CFLAGS += -g3
	CFLAGS += --coverage
	LDFLAGS += --coverage
endif

# Сборка исполняемых файлов
app.exe : $(OBJS) ./out/main.o
	$(CC) $^ -o $@ $(LDFLAGS)

unit_tests.exe: $(CHECK_OBJS) $(OBJS)
	$(CC) $^ -o $@ $(CHECK_FLAGS)

# Сборка объектных файлов
./out/%.o : ./src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

./out/%.o : ./unit_tests/%.c
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $< -c -o $@

.PHONY : clean func unit

clean:
	rm rm -f ./*.exe ./out/*.o ./out/*.gcda ./out/*.gcno ./out/*.gcov ./out/*.txt ./out/*.d ./*.gcov ./*.txt

func:
	./collect_coverage.sh

unit:
	./unit_tests.exe

