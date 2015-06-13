BIN = bin/
BUILD = $(BIN)build/
CC = g++
OUT = $(BIN)main
FILE = main.cpp io/IOManager.cpp shader/Shader.cpp util/Util.cpp
OBJS = $(BUILD)main.o \
	   $(BUILD)IOManager.o \
	   $(BUILD)Shader.o \
	   $(BUILD)Window.o \
	   $(BUILD)Util.o
	   
INCLUDE = -I ~/dev/c++/glfw-3.1.1/include/
LIBRARIES = -L/usr/local/lib -lglfw3
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

CMD = $(CC) $< -c -o $@ $(INCLUDE)

CFLAGS = $(FRAMEWORKS) $(LIBRARIES) $(INCLUDE)

all: $(BUILD) $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(CFLAGS)

$(BUILD)%.o: %.cpp shader/Shader.h io/IOManager.h util/Util.h
	$(CMD)
	
$(BUILD)%.o: io/%.cpp
	$(CMD)
	
$(BUILD)%.o: shader/%.cpp io/IOManager.h util/Util.h
	$(CMD)
	
$(BUILD)%.o: util/%.cpp
	$(CMD)

$(BIN):
	mkdir -p $(BIN)

$(BUILD): $(BIN)
	mkdir -p $(BUILD)


clean:
	rm $(OUT)
	rm -r $(BUILD)
