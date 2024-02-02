CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = my_octave.c
OBJS = $(SRCS:%.c=%.o)
TARGET = my_octave

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: pack clean
