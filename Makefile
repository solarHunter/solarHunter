OS := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
	ARCH = x64
	ARCH_FLAG = -m64
endif
ifneq ($(filter %86,$(UNAME_M)),)
	ARCH = x86
	ARCH_FLAG = -m32
endif
ifneq ($(filter arm%,$(UNAME_M)),)
	ARCH = ARM
	ARCH_FLAG = -m32
endif

VERSION := 0.0.$(shell git rev-list --count origin master)-$(ARCH)

ifeq ($(OS), Darwin)
SDL_INCLUDE = -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers
SDL_LIB = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
SDL_INCLUDE = -I/usr/include/SDL2
SDL_LIB = -L/usr/local/lib -lSDL2_image -lSDL2_ttf -lSDL2main -lSDL2
endif

CXX = g++
CXXFLAGS = -Wall -pedantic -DVERSION="\"$(VERSION)\"" $(ARCH_FLAG) -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB) $(ARCH_FLAG)
EXE = solarHunter

MKDIR_P = mkdir -p
OUT_DIR = bin/$(OS)/v$(VERSION)

# Files
O_STATE := src/engine/state/stateEngine.o
O_GRAPHICS := src/engine/graphics/graphics.o src/engine/graphics/textures.o
O_GUI := src/engine/gui/kiss_general.o src/engine/gui/kiss_posix.o src/engine/gui/kiss_widgets.o src/engine/gui/kiss_draw.o src/engine/gui/gui.o
O_CONFIG := src/engine/config/config.o
O_ENGINE := $(O_CONFIG) $(O_GRAPHICS) $(O_GUI) $(O_STATE) src/engine/engine.o

OBJS := src/main.cpp src/states/initialMenu.cpp src/states/test.cpp src/states/pause.cpp


all: bindir engine build mediadir cleanobj
keep: bindir engine build mediadir

engine: $(O_ENGINE)
	ar cr src/engine/engine.a $^

build:
	g++ $(CXXFLAGS) src/engine/engine.a $(OBJS) $(SDL_LIB) -o $(OUT_DIR)/$(EXE)

debug: 
	g++ -g $(CXXFLAGS) src/engine/engine.a $(OBJS) $(SDL_LIB) -o $(OUT_DIR)/$(EXE)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $< -o $@

mediadir:
	cp -rvp ./media $(OUT_DIR)/

bindir: ${OUT_DIR}

conf:
	cp solarhunter.conf $(OUT_DIR)/

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

cleanobj:
	find . -type f -name '*.o' -exec rm {} +

clean: cleanobj
	rm -rf $(OUT_DIR) src/engine/engine.a

cleanall: cleanobj
	rm -rf bin
