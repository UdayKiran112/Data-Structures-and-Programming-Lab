# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = ip_reassembly

# Source files
SRCS = main.c datagram.c parser.c

# Object directory
OBJDIR = obj

# Object files (placed in obj/)
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile step (ensure obj/ exists before compiling)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if not exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
