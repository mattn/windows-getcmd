SRCS = \
	main.c

OBJS = $(subst .c,.o,$(SRCS))

CFLAGS = -Wall
LIBS = 
TARGET = windows-getcmd
ifeq ($(OS),Windows_NT)
TARGET := $(TARGET).exe
endif

.SUFFIXES: .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -o $@ $(OBJS) $(LIBS)

.c.o :
	gcc -c $(CFLAGS) -I. $< -o $@

clean :
	rm -f *.o $(TARGET)
