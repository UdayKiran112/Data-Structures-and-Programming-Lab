CC = gcc
CFLAGS = -Wall -g
TARGET = student_db

# Directories
OBJDIR = obj

# Source and object files
SRCS = main.c parser.c student.c course.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule for building object files in obj/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
