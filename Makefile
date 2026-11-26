CC      ?= gcc
CFLAGS  ?= -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -pedantic -g
CFLAGS  += -Iinclude
SANITIZE = -fsanitize=address,undefined -fno-omit-frame-pointer

SRCS    := dynamic_vector/dynamic_vector.c heap/heap.c pq_heap/pq_heap.c \
           uid/uid.c task/tasker.c scheduler_main/scheduler.c
OBJS    := $(patsubst %.c,build/%.o,$(SRCS))
LIB     := build/libscheduler.a

TESTS   := dynamic_vector heap pq_heap uid tasker scheduler
TEST_SRC_dynamic_vector := dynamic_vector/dynamic_vector_test.c
TEST_SRC_heap           := heap/heap_test.c
TEST_SRC_pq_heap        := pq_heap/pq_heap_test.c
TEST_SRC_uid            := uid/uid_test.c
TEST_SRC_tasker         := task/tasker_test.c
TEST_SRC_scheduler      := scheduler_main/scheduler_test.c
TEST_BINS := $(addprefix build/test_,$(TESTS))

.PHONY: all lib test sanitize clean

all: lib $(TEST_BINS)

lib: $(LIB)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(AR) rcs $@ $^

.SECONDEXPANSION:
build/test_%: $$(TEST_SRC_$$*) $(LIB)
	$(CC) $(CFLAGS) $< $(LIB) $(LDFLAGS) -o $@

test: $(TEST_BINS)
	@status=0; for t in $(TEST_BINS); do ./$$t || status=1; done; exit $$status

# Rebuild with AddressSanitizer + UndefinedBehaviorSanitizer and run the tests.
sanitize: clean
	$(MAKE) test CFLAGS="$(CFLAGS) $(SANITIZE)" LDFLAGS="$(SANITIZE)"

clean:
	rm -rf build
