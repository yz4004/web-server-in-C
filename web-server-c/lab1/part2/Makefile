# This Makefile should be used as a template for future Makefiles.
# It's heavily commented, so hopefully you can understand what each
# line does.

# We'll use gcc for C compilation and g++ for C++ compilation

CC  = gcc
CXX = g++

# Let's leave a place holder for additional include directories

INCLUDES =

# Compilation options:
# -g for debugging info and -Wall enables all warnings

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)


LDFLAGS = -g

LDLIBS =


convert:  convert.o

convert.o: convert.c

.PHONY: clean
clean:
	rm -f *.o a.out core main


# "all" target is useful if your Makefile builds multiple programs.
# Here we'll have it first do "clean", and rebuild the main target.

.PHONY: all
all: clean main
