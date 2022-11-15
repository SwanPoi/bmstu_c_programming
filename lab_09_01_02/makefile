CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS := ./src/process.c ./src/struct_IO.c
OBJS := ./out/process.o ./out/struct_IO.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_copy_names_startswith.c ./unit_tests/check_sort_container.c
CHECK_OBJS := ./out/check_main.o ./out/check_copy_names_startswith.o ./out/check_sort_container.o

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

