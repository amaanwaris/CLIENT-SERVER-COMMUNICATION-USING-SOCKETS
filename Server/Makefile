CC = gcc
DFLAGS = -DDEBUG
CFLAGS = -Wall -Wextra -pthread $(DFLAGS) -I../Common

TARGETS = server client vendorAdd vendorSub vendorMul vendorDiv vendorMod

# Define the library name and the objects that go into it
LIBRARY = libcommon.a
LIB_OBJS = recvExact.o sendExact.o

HEADERS = ../Common/headers.h ../Common/dataSt.h declarations.h

.PHONY: all clean

# Build the library first, then the executables 
all: $(LIBRARY) $(TARGETS)

# 1. Generic Pattern Rule: Compiles ANY .c file into a .o file
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
# 2. Archive Rule: Bundles the common object files into a Static Library (.a)
# 'ar' is the achive utility.
# 'r' inserts with replacement, 'c' creates the archive, 's' creates an index.
$(LIBRARY): $(LIB_OBJS)
	ar rcs $@ $^

# 3. Specific Linking Rules for Executables
# We use -L. to tell gcc to look for libraries in the current directory ('.')
# We use -lcommon to tell gcc to link against 'libcommon.a' (the 'lib' and '.a' are implied)

server: mainServer.o clientHandler.o $(LIBRARY)
	$(CC) $(CFLAGS) mainServer.o clientHandler.o -L. -lcommon -o $@

client: clientApp.o $(LIBRARY)
	$(CC) $(CFLAGS) clientApp.o -L. -lcommon -o $@
vendorAdd: vendorAdd.o $(LIBRARY)
	$(CC) $(CFLAGS) vendorAdd.o -L. -lcommon -o $@
vendorSub: vendorSub.o $(LIBRARY)
	$(CC) $(CFLAGS) vendorSub.o -L. -lcommon -o $@
vendorMul: vendorMul.o $(LIBRARY)
	$(CC) $(CFLAGS) vendorMul.o -L. -lcommon -o $@
vendorDiv: vendorDiv.o $(LIBRARY)
	$(CC) $(CFLAGS) vendorDiv.o -L. -lcommon -o $@
vendorMod: vendorMod.o $(LIBRARY)
	$(CC) $(CFLAGS) vendorMod.o -L. -lcommon -o $@

clean:
	rm -f $(TARGETS) $(LIBRARY) *.o
