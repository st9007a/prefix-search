TESTS = \
    test_cpy \
    test_ref

CFLAGS = -Wall -Werror -g

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

GIT_HOOKS := .git/hooks/applied

.PHONY: all clean

all: $(GIT_HOOKS) $(TESTS)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

OBJS_LIB = \
    tst.o \
	bench.o

OBJS := \
    $(OBJS_LIB) \
    test_cpy.o \
    test_ref.o

BIN = \
	test_cpy \
	test_ref

deps := $(OBJS:%.o=.%.o.d)

test_%: test_%.o $(OBJS_LIB)
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

bench: $(BIN)
	@for test in $(BIN); do\
		./$$test --bench; \
	done

plot:
	@gnuplot scripts/runtime.gp

clean:
	$(RM) $(TESTS) $(OBJS)
	$(RM) $(deps)

-include $(deps)
