#####################################################################################
# Variables																		
#####################################################################################

# Executable name
EXEC = app

# Precompiled headers
PCH_SRC = src/headers.h
PCH_OUT = src/headers.h.gch

# Source files
SRC_FOLDER = src
SRC = $(shell find $(SRC_FOLDER) -name "*.cpp")

# Header files
INC = $(shell find $(SRC_FOLDER) -name "*.h")

# Binary files
BIN_FOLDER = bin

# Object files
OBJ_DEP = $(SRC:$(SRC_FOLDER)/%.cpp=$(BIN_FOLDER)/%.o)

# Compiler
C = gcc
CXX = g++

# Compile flags
DEBUG = -g -ggdb3
CFLAGS = 
CXXFLAGS = -std=c++17 -Wall -Wpedantic -Wextra -Wconversion -pthread $(DEBUG)

# Linking flags
LDFLAGS = -lpthread

# Libraries to link
LIB_FOLDER = libs
LIBS = $(wildcard $(LIB_FOLDER)/*.so) $(wildcard $(LIB_FOLDER)/*.a)
LIBSNAME = $(subst lib,, $(notdir $(basename $(LIBS))))

# Libraries flag
LIBFLAGS = $(addprefix -l, $(LIBSNAME))

# Name file by default
NAME = default
FOLDER = 

#####################################################################################
# 									Targets																		
#####################################################################################

# Phony target
.PHONY : all clean

# Base target
all : $(EXEC)

# Debug mode

# Execute target
$(EXEC) : $(OBJ_DEP)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LIBFLAGS)

# Function to make .o files from cpp files
$(BIN_FOLDER)/%.o : $(SRC_FOLDER)/%.cpp $(PCH_OUT)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Function to make .o files from c files
$(BIN_FOLDER)/%.o : $(SRC_FOLDER)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Function to compile precompiled headers
$(PCH_OUT) : $(PCH_SRC)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

create :
	@mkdir -p $(SRC_FOLDER)/$(FOLDER)
	@touch $(SRC_FOLDER)/$(FOLDER)/$(NAME).h
	@touch $(SRC_FOLDER)/$(FOLDER)/$(NAME).cpp
	@mkdir -p $(BIN_FOLDER)/$(FOLDER)

delete :
	@$(shell rm -f include/$(FOLDER)/$(NAME).h && rm -f src/$(FOLDER)/$(NAME).cpp)

# Target to clean every files that was created during the make command
clean :
	@rm -rf $(OBJ_DEP) $(EXEC)

help :
	@echo "Learn to code"