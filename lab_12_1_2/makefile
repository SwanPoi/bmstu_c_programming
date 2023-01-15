CC := gcc
LIBC := ar

LIBFLAGS := -o
DYNLIBFLAGS := -shared
CFLAGS := -std=gnu99 -Wall -Werror -Wextra -fPIC
LDFLAGS := -L . -larr
LIBLDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS_LIB := ./lib_src/arr_lib.c
OBJS_LIB := ./out/arr_lib.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_get_full_squares.c ./unit_tests/check_left_k_shift.c
CHECK_OBJS := ./out/check_main.o ./out/check_get_full_squares.o ./out/check_left_k_shift.o

TARGET := libarr.so

path := $(shell pwd)

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), gcov)
	CFLAGS += -g3
	CFLAGS += --coverage
	LDFLAGS += --coverage
endif

unit_tests.exe: $(CHECK_OBJS) $(TARGET)
	$(CC) $(CHECK_OBJS) -o $@ $(LDFLAGS) $(CHECK_FLAGS)

# Сборка библиотеки
$(TARGET) : $(OBJS_LIB)
	$(CC) $(LIBFLAGS) $@ $(DYNLIBFLAGS) $^
 

./out/%.o : ./lib_src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

./out/%.o : ./unit_tests/%.c
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $< -c -o $@

.PHONY : clean unit py_gui

clean:
	rm rm -f ./*.exe ./out/*.o ./out/*.gcda ./out/*.gcno ./out/*.gcov ./out/*.txt ./out/*.d ./*.gcov ./*.a ./*.so

unit: unit_tests.exe
#	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(path)
	./unit_tests.exe

py_gui:
	python3 ./py_src/main.py



