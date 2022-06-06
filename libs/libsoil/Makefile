# SOIL makefile for linux (based on the AngelScript makefile)
# Type 'make' then 'make install' to complete the installation of the library

# For 'make install' to work, set LOCAL according to your system configuration
PREFIX = /usr/local
LOCAL = $(PREFIX)

LIB = libSOIL.a
INC = SOIL.h

SRCDIR = src
LIBDIR = lib
INCDIR = src
OBJDIR = obj

CXX = gcc
DELETER = rm -f
COPIER = cp

SRCNAMES = \
  image_helper.c \
  stb_image_aug.c  \
  image_DXT.c \
  SOIL.c \

OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRCNAMES:.c=.o)))
BIN = $(LIBDIR)/$(LIB)

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p $(LIBDIR)
	$(DELETER) $(BIN)
	ar r $(BIN) $(OBJ)
	ranlib $(BIN)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CXX) -o $@ -c $<


clean:
	$(DELETER) $(OBJ) $(BIN)

fclean: clean
	@rm -rf lib obj

$(LOCAL)/lib/:
	mkdir $(LOCAL)/lib

$(LOCAL)/include/:
	mkdir $(LOCAL)/include

.PHONY: all clean
