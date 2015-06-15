BIN = bin/
BUILD = $(BIN)build/
CC = g++
FILE = main
OUT = $(BIN)$(FILE)
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

all: $(BUILD) $(OBJS) shaders
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

shaders:
	cp -R shader/glsl/ bin/shader/

run:
	cd $(BIN); ./$(FILE)

clean:
	rm $(OUT)
	rm -r $(BUILD)
	rm -r $(BIN)
