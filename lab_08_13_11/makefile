CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS := ./src/matrix_IO.c ./src/matrix_operations.c ./src/main_process.c
OBJS := ./out/matrix_IO.o ./out/matrix_operations.o ./out/main_process.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_matr_multiplication.c ./unit_tests/check_matr_addition.c ./unit_tests/check_matrix_determinant.c
CHECK_OBJS := ./out/check_main.o ./out/check_matr_multiplication.o ./out/check_matr_addition.o ./out/check_matrix_determinant.o

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

