CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS := ./src/sort.c ./src/filter.c ./src/IO_file.c ./src/task_processes.c
OBJS := ./out/sort.o ./out/filter.o ./out/IO_file.o ./out/task_processes.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_sort.c ./unit_tests/check_filter.c
CHECK_OBJS := ./out/check_main.o ./out/check_sort.o ./out/check_filter.o

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
	rm rm -f ./*.exe ./out/*.o ./out/*.gcda ./out/*.gcno ./out/*.gcov ./out/*.txt ./out/*.d ./*.gcov

func:
	./collect_coverage.sh

unit:
	./unit_tests.exe

