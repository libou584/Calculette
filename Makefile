# Fichiers
TARGET = main
SRCS = main.c background.c pad.c button.c sound.c screen.c texture.c
OBJS = $(SRCS:.c=.o)

# Compilation
CC = clang
CFLAGS = -std=gnu11 -O2
LDFLAGS = -lm

# Debug 
CFLAGS += -g -Wall -Wextra -pedantic
# CFLAGS += -fsanitize=address -fno-omit-frame-pointer
# LDFLAGS += -fsanitize=address


#Libs
CFLAGS += $(shell pkg-config --cflags sdl2)
LDFLAGS += $(shell pkg-config --libs sdl2)
CFLAGS += $(shell pkg-config --cflags SDL2_image)
LDFLAGS += $(shell pkg-config --libs SDL2_image)
CLAGS += $(shell pkg-config --cflags SDL2_mixer)
LDFLAGS += $(shell pkg-config --libs SDL2_mixer)
# CFLAGS += $(shell pkg-config --cflags SDL2_ttf)
# LDFLAGS += $(shell pkg-config --libs SDL2_tff)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -lSDL2_ttf -lOpenCL -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: 
	make
	./main

ready:
	make
	rm -f $(OBJS)