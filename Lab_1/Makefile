# C compiler
CC = gcc

# Flags
CFLAGS = -Wall -g

# Targets
all: union intersect difference subset membership

union: union.c mylib.c mylib.h
	$(CC) $(CFLAGS) union.c mylib.c -o union

intersect: intersect.c mylib.c mylib.h
	$(CC) $(CFLAGS) intersect.c mylib.c -o intersect

difference: difference.c mylib.c mylib.h
	$(CC) $(CFLAGS) difference.c mylib.c -o difference

subset: subset.c mylib.c mylib.h
	$(CC) $(CFLAGS) subset.c mylib.c -o subset

membership: membership.c mylib.c mylib.h
	$(CC) $(CFLAGS) membership.c mylib.c -o membership

# Cleanup
clean:
	rm -f union intersect difference subset membership
