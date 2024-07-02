CC    	?= cc
AR   	?= ar
RM    	?= rm
MKDIR 	?= mkdir
INSTALL ?= install
PREFIX	?= /usr/local

OBJECTS := 	intensities.o \
		jpeg.o \
		png.o \
		main.o

.PHONY: all clean

all: image-intensities

install: image-intensities
	$(INSTALL) image-intensities $(PREFIX)/bin/image-intensities

uninstall:
	$(RM) -rf $(PREFIX)/bin/image-intensities

image-intensities: $(OBJECTS)
	$(CC) $^ -lpng -lmagic -lturbojpeg -o $@

%.o: %.c
	$(CC) $< -c -o $@ -O3

clean:
	$(RM) -rf $(JPEG_OBJECTS)
	$(RM) -rf $(OBJECTS)
	$(RM) -rf image-intensities
