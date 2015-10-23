
CC = g++
CFLAGS = 

INCDIR = include
SRCDIR = src
BINDIR = bin
OBJDIR = obj
INC = $(wildcard $(INCDIR)**/*.h)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
LIB = -lv8

TARGET = $(BINDIR)/FancyBox

$(TARGET): $(OBJ)
	@echo "Compiling" $(OBJ)
	$(CC) -o $@ $^ $(LIB)

$(OBJ): $(SRC) $(INC)
	@echo "Building" $(SRC) $(INC)
	$(CC) -c -o $@ $<

filelist:
	@echo $(INC)
	@echo $(SRC)

.PHONY: clean
clean:
	@echo "Cleaning"
	@rm -rf $(OBJDIR)/*
	@rm -rf $(BINDIR)/*

.PHONY: debug
debug:
	@$(TARGET)
