BIN = bin/
BUILD = $(BIN)build/
THIRD_PARTY = 3rd_party/
CC = g++
FILE = main
OUT = $(BIN)$(FILE)
OBJS = $(BUILD)main.o \
	   $(BUILD)IOManager.o \
	   $(BUILD)Shader.o \
	   $(BUILD)Window.o \
	   $(BUILD)Util.o \
	   $(BUILD)SpriteBatch.o \
	   $(BUILD)Camera.o \
	   $(BUILD)TextureCache.o \
	   $(BUILD)InputManager.o \
	   $(BUILD)ImageLoader.o \
	   $(BUILD)ResourceManager.o \
	   $(BUILD)Error.o \
	   $(BUILD)Agent.o \
	   $(BUILD)Bullet.o \
	   $(BUILD)Gun.o \
	   $(BUILD)Human.o \
	   $(BUILD)Level.o \
	   $(BUILD)MainGame.o \
	   $(BUILD)Player.o \
	   $(BUILD)Zombie.o

INCLUDE = -I ~/dev/c++/glfw-3.1.1/include/ \
		  -I/usr/local/include/ \
		  -I ~/dev/c++/glm/ \
		  -I ~/dev/c++/rapidjson/include/
LIBRARIES = -L/usr/local/lib -lglfw3 -lz -lpng -lc
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

CMD = $(CC) $< -c $(OUTPUT_FLAG) -o $@ $(INCLUDE) -std=c++11

CFLAGS = $(FRAMEWORKS) $(LIBRARIES) $(INCLUDE) -std=c++11

all: OUTPUT_FLAG = -g -og
all: $(BUILD) $(OBJS) resources
	$(CC) $(OBJS) $(OUTPUT_FLAG) -o $(OUT) $(CFLAGS)

opt: OUTPUT_FLAG = -o3
opt: clean $(BUILD) $(OBJS) resources
	$(CC) $(OBJS) $(OUTPUT_FLAG) -o $(OUT) $(CFLAGS)

debug: all
	dsymutil -o $(OUT).dSYM $(OUT)

$(BUILD)%.o: %.cpp shader/Shader.h io/IOManager.h util/Util.h
	$(CMD)
	
$(BUILD)%.o: io/%.cpp
	$(CMD)
	
$(BUILD)%.o: shader/%.cpp io/IOManager.h util/Util.h
	$(CMD)
	
$(BUILD)%.o: util/%.cpp
	$(CMD)

$(BUILD)%.o: drawing/%.cpp
	$(CMD)

$(BUILD)%.o: zombie/%.cpp
	$(CMD)

$(BIN):
	mkdir -p $(BIN)

$(BUILD): $(BIN)
	mkdir -p $(BUILD)

.PHONY: resources
resources: 
	cp -R shader/glsl/ $(BIN)shader/
	cp -R resources/images/ $(BIN)images/
	cp -R resources/level/ $(BIN)level/

run:
	cd $(BIN); ./$(FILE)

d:
	cd $(BIN); lldb $(FILE)

clean:
	rm -r $(BIN)
