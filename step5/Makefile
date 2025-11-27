CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
AR = ar
ARFLAGS = rcs

LIB_NAME = libcar.a
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

SOURCES = $(SRC_DIR)/Car.cpp
OBJECTS = $(OBJ_DIR)/Car.o

PREFIX = /usr/local

.PHONY: all clean install

all: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME)

install: $(LIB_NAME)
	install -d $(PREFIX)/lib
	install $(LIB_NAME) $(PREFIX)/lib/
	install -d $(PREFIX)/include/library
	install $(INCLUDE_DIR)/library/Car.hpp $(PREFIX)/include/library/