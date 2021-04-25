CC       = gcc
PROG     = dF-terminal
CFLAGS   = -Wall
SRC      = $(wildcard *.c)
BUILDDIR = build/
SHELL    = /bin/bash

ifneq ($(DEBUG),)
	CFLAGS := $(CFLAGS) -g
endif

ifeq ($(DESTDIR),)
	DESTDIR := /usr/local/bin/
endif

.PHONY: clean
all: $(PROG)

$(PROG):
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BUILDDIR)$@

%.o: %.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	git clean -Xfq
	rm -rf build/$(PROG)

install:
	cp $(BUILDDIR)$(PROG) $(DESTDIR)/