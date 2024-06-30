CXX = g++
CXXFLAGS = -g -fdiagnostics-color=always
LDFLAGS = -lglfw -ldl -lGL

GLAD_DIR = glad
OBJ_DIR = obj

SOURCES = $(wildcard *.cpp) $(GLAD_DIR)/glad.c
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

EXECUTABLE = app.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(GLAD_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean
