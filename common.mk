# common.mk

# This file allows easy creation of Makefiles with multiple targets
# avoiding repeating the same commands. It is used by making
# one or more Makefiles, and within each Makefile:

# 1. we add for each <foo> executable a <foo>_OBJS variable with
# all objects (.o) needed for the program. E.g
# myprogram_OBJS = main.o module1.o module2.o

# 2. We do: include common.mk

# For each executable <foo> the following targets are generated:
# <foo> Compiles <foo>
# run-<foo> Compiles and runs <foo>
# valgrind-<foo> Compile and run <foo> via valgrind
# coverage-<foo> Compile and run <foo>, and generate a coverage report

# And in addition the following general targets are produced:
# all Makes all <foo> targets dependent
# run Makes all run-<foo> targets dependent
# valgrind Makes all valgrind-<foo> targets dependent
# coverage Executes the run, and produces a nine coverage report
# clean Deletes all files produced by make

# This file uses some advanced features of GNU make, NOT required
# understand all the commands to use it (not that it's hard
# do it if you want). You can also use the simpler ones
# Makefiles we saw in class, if you prefer.


## Variables ##

# Paths
MY_PATH := $(dir $(lastword $(MAKEFILE_LIST)))
MODULES := $(MY_PATH)modules
INCLUDE := $(MY_PATH)include
LIB		:= $(MY_PATH)lib

# Compiler options
# -g Creates an executable suitable for debugging
# -I<dir> Tells the compiler to search the specified directory for include files
# -Wall Enables all warnings
# -Werror Treat warnings as errors, stopping compilation
# -MDD Creates a .d file with the dependencies, which we can include in the Makefile
#
# Override allows additional parameters to be added from the command line: make CFLAGS=...
override CFLAGS += -g -Wall -MMD -I$(INCLUDE)

# Linker options
# -lm == Link with math library
LDFLAGS += -lm

# If the targets with which make has been called (MAKECMDGOALS variable) have any
# coverage*, then we add --coverage to the compile & link flags
ifneq (,$(findstring coverage,$(MAKECMDGOALS)))
	override CFLAGS += --coverage
	override LDFLAGS += --coverage
endif

# compiler
CC = gcc

# List all <foo> executables & libraries for which a <foo>_OBJS variable exists
WITH_OBJS := $(subst _OBJS,,$(filter %_OBJS,$(.VARIABLES)))
PROGS := $(filter-out %.a,$(WITH_OBJS))
LIBS := $(filter %.a,$(WITH_OBJS))

# We collect all the objects in one variable
OBJS := $(foreach target, $(WITH_OBJS), $($(target)_OBJS))

# For each .o gcc produces a .d, we store them here (the filter only keeps the .o, not the .a)
DEPS := $(patsubst %.o, %.d, $(filter %.o, $(OBJS)))

# List of coverage-related files produced when compiling & executing with --coverage (.gcda .gcno)
COV_FILES := $(patsubst %.o,%.gcda,$(OBJS)) $(patsubst %.o,%.gcno,$(OBJS))

# For each target <prog> we create 3 targets run-<prog>, valgrind-<prog>, coverage-<prog>
# In the following variables we make a list of all these targets
# "?=" means "assign if the variable doesn't already have a value". This allows
# in the Makefile specify which targets it wants to be built, before including common.mk
RUN_TARGETS ?= $(addprefix run-, $(PROGS))
VAL_TARGETS ?= $(addprefix valgrind-, $(PROGS))
COV_TARGETS ?= $(addprefix coverage-, $(PROGS))

# For each test (*_test) we set its parameters (<test>_ARGS) from default to --time
$(foreach test, $(filter %_test, $(PROGS)),	\
	$(eval $(test)_ARGS ?= --time)			\
)


## Rules ##

# Default target, compiles all executables & libraries
all: $(PROGS) $(LIBS)

# This is needed to be able to use variables in the list of dependencies.
# This usage requires double "$$" in variables, eg: $$(VAR), $$@
.SECONDEXPANSION:

# For each <program> executable, we create a rule that declares its contents
# <program>_OBJS as dependencies of <program>. $@ contains the name of the target,
# but to use it in the list of dependencies we need $$@ and .SECONDEXPANSION
$(PROGS): $$($$@_OBJS)
	$(CC)  $^ -o $@ $(LDFLAGS)

# For each <lib> library, we create a rule that declares its contents
# <lib>_OBJS as dependencies of <lib>.
$(LIBS): $$($$@_OBJS)
	ar -rcs $@ $^

# Include the .d files produced by gcc (the "-" ignores the command if it fails)
# A file foo.d contains all the files (.c and .h) that gcc needed to compile
# foo.o, in Makefile format. So by including foo.d we declare that if any
# of these files changed, we must recompile foo.o.
-include $(DEPS)

# make clean cleans anything made by this Makefile
clean:
	@$(RM) $(PROGS) $(LIBS) $(OBJS) $(DEPS) $(COV_FILES)
	@$(RM) -r coverage

# For each executable <prog> we create a target run-<prog> that executes it with parameters <prog>_ARGS
# run-% is "pattern rule", creates a rule for each run-<foo>, setting $* to "foo".
run-%: %
	./$* $($*_ARGS)

# Make run executes all run targets
run: $(RUN_TARGETS)

# For each executable <prog> we create a target valgrind-<prog> that executes it via valgrind with parameters <prog>_ARGS
valgrind-%: %
	valgrind --error-exitcode=1 --leak-check=full ./$* $($*_ARGS)

valgrind: $(VAL_TARGETS)

# Helper target that executes lcov. It is used as a dependency in coverage-* targets
lcov:
	@mkdir -p coverage
	lcov --rc lcov_branch_coverage=1 --capture --directory=$(MY_PATH) --output-file coverage/lcov.info
	lcov --rc lcov_branch_coverage=1 --remove coverage/lcov.info '*.h' --output-file coverage/lcov.info
	cd coverage && genhtml --rc lcov_branch_coverage=1 lcov.info
	@echo "To see the report open the file below in your brower:"
	@echo "$$PWD/coverage/index.html"

# For each executable <prog> we create a target coverage-<prog> that executes it and then creates a coverage report
coverage-%: clean run-% lcov
	@true 						# dummy command, because a pattern rule is ignored if there are no commands for the target)
coverage: clean run lcov

# Targets defined by pattern rules (eg foo-%) are not shown in bash auto-complete. The following blank rules
# they don't affect the operation of the Makefile at all, they just allow auto-complete to "see" these targets.
$(RUN_TARGETS):
$(VAL_TARGETS):
$(COV_TARGETS):

# We declare that the following rules are virtual, they do not produce files. That is, we want
# make "make clean" run even if there happens to be a "clean" file in the
# current directory.
.PHONY: clean run valgrind coverage lcov
