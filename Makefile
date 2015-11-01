
CC = g++
CFLAGS = -Wall -Werror

INCDIR = include
SRCDIR = src
BINDIR = bin
OBJDIR = obj
INC = $(wildcard $(INCDIR)/*.*)
SRC = $(wildcard $(SRCDIR)/*.*) $(wildcard $(SRCDIR)/*/*.*)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
LIB = -lglfw3 -pthread -lGLEW -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor -lopenal -lshape -lfreeimage -lv8

TARGET = $(BINDIR)/FancyBox

$(TARGET): compile
	@echo "Building"
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIB)

.PHONY: compile
compile:
	@echo "Compiling"
	@$(foreach dir,$(subst $(SRCDIR)/,$(OBJDIR)/,$(dir $(wildcard $(SRCDIR)/*/))),mkdir -p $(dir);)
	@$(foreach target,$(SRC),echo $(target);$(CC) -c -o $(subst $(SRCDIR)/,$(OBJDIR)/,$(subst .cpp,.o,$(target))) $(target) $(CFLAGS);)

.PHONY: filelist
filelist:
	@echo $(INC)
	@echo $(SRC)
	@echo $(OBJ)

.PHONY: clean
clean:
	@echo "Cleaning"
	@rm -rf $(OBJDIR)/*
	@rm -rf $(BINDIR)/*

.PHONY: debug
debug:
	@cp data/*.* bin/
	@$(TARGET)