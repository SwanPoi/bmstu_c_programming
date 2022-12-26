CC := gcc
LIBC := ar

LIBFLAGS := 
DYNLIBFLAGS := 
CFLAGS := -std=gnu99 -Wall -Werror -Wextra
LDFLAGS := 
LIBLDFLAGS := -lm
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


SRCS_LIB := ./src/sort.c ./src/filter.c ./src/IO_file.c 
SRC_APP := ./src/task_processes.c
OBJS_LIB := ./out/sort.o ./out/filter.o ./out/IO_file.o 
OBJS_APP := ./out/task_processes.o

CHECK_SRCS := ./unit_tests/check_main.c ./unit_tests/check_sort.c ./unit_tests/check_filter.c
CHECK_OBJS := ./out/check_main.o ./out/check_sort.o ./out/check_filter.o

TARGET := ./app.exe

path := $(shell pwd)

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), gcov)
	CFLAGS += -g3
	CFLAGS += --coverage
	LDFLAGS += --coverage
endif

ifeq ($(lib), dynamic)
	TARGET := libarr.so
	LIBC := gcc
	CFLAGS += -fpic
	DYNLIBFLAGS += -shared
	LIBFLAGS += -o

	ifeq ($(dyn_mode), load)
		LDFLAGS += -ldl
		CFLAGS += -D DYN_LOAD=1
	endif

	ifeq ($(dyn_mode), link)
		LDFLAGS += -L . -larr
	endif

endif

ifeq ($(lib), static)
	TARGET := libarr.a
	LIBFLAGS := rc
	LIBLDFLAGS += -shared
	LDFLAGS += -L . -larr
endif

app.exe : $(OBJS_APP) $(TARGET) ./out/main.o
	$(CC) -o $@ $(OBJS_APP) ./out/main.o $(LDFLAGS) -lm

unit_tests.exe: $(CHECK_OBJS) $(TARGET)
	$(CC) $(CHECK_OBJS) -o $@ $(LDFLAGS) $(CHECK_FLAGS)

# Сборка библиотеки
$(TARGET) : $(OBJS_LIB)
	$(LIBC) $(LIBFLAGS) $@ $(DYNLIBFLAGS) $^
 

./out/%.o : ./src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

./out/%.o : ./unit_tests/%.c
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $< -c -o $@

.PHONY : clean func unit

clean:
	rm rm -f ./*.exe ./out/*.o ./out/*.gcda ./out/*.gcno ./out/*.gcov ./out/*.txt ./out/*.d ./*.gcov ./*.a ./*.so

func: ./app.exe 
	$(shell export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../..)
	./collect_coverage.sh

unit: unit_tests.exe
	$(shell export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../..)
	./unit_tests.exe



