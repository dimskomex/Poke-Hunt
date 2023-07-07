# This Makefile is located in the root of the entire project and is used for
# to easily compile several parts of the project together. This Makefile
# calls make on the various directories as
# $(MAKE) -C <dir> <target>
# which is equivalent to running make <target> inside directory <foo>

# All directories inside the programs directory
PROGRAMS = $(subst programs/, , $(wildcard programs/*))

# Compile: all, programs, tests
all: programs tests

# The following line creates a target programs-<foo> for any <foo>. Variable $* contains "foo"
programs-%:
	$(MAKE) -C programs/$*

programs: $(addprefix programs-, $(PROGRAMS)) # depend on programs-<foo> for each element of PROGRAMS

.PHONY: tests
tests:
	$(MAKE) -C tests all

# Execution: all
run: run-programs run-tests

run-programs-%:
	$(MAKE) -C programs/$* run

run-programs: $(addprefix run-programs-, $(PROGRAMS))

run-tests:
	$(MAKE) -C tests run

# Clearing
clean-programs-%:
	$(MAKE) -C programs/$* clean

clean: $(addprefix clean-programs-, $(PROGRAMS))
	$(MAKE) -C tests clean