TARGET := Dictionary

SRC := src
BUILD := build

SRCS := $(shell find $(SRC) -type f -name '*.cpp')
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))

all: clean $(TARGET)

$(TARGET): $(OBJS)
ifeq ($(OS),Windows_NT)
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -lraylib
endif

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	g++ -std=c++14 -Iinclude -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BUILD)