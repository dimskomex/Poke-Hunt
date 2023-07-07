ifdef WASM
	SUFFIX = wasm
else ifeq ($(OS),Windows_NT)
	SUFFIX = win
else ifeq ($(shell uname -s),Linux)
	SUFFIX = linux
else
	SUFFIX = macos
endif

all: libraylib.a

# Το ίδιο για το libraylib.a
libraylib.a:
	cp libraylib_$(SUFFIX).a libraylib.a

clean:
	$(RM) k08.a libraylib.a