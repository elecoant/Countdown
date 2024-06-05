CC = gcc
CFLAGS = -Wall

BINDIR = bin
SRCDIR = src
OBJDIR = obj

BINS = $(BINDIR)/countdown
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINS): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(BINS)

clean:
	@rm -rf $(OBJDIR)
	