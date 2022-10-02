CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra
LDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS := ./src/sort.c ./src/filter.c ./src/IO_file.c
OBJS := ./out/sort.o ./out/filter.o ./out/IO_file.o

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


## Генерация файлов зависимостей
#out/%.d : inc/%.h src/%.c
#	echo -n "out/" > $@
#	$(CC) -MM $< >> $@

#out/%.d : inc/%.h unit_tests/%.c
#	echo -n "out/" > $@
#	$(CC) -MM $< >> $@
#
#C_DEPS = $(SRCS:./src/%.c=./out/%.d)
#
#include $(wildcard $(C_DEPS))

.PHONY : clean func unit

clean:
	rm rm -f ./*.exe ./out/*.o ./out/*.gcda ./out/*.gcno ./out/*.gcov ./out/*.txt ./out/*.d ./*.gcov

func:
	./collect_coverage.sh

unit:
	./unit_tests.exe

