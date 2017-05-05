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

ifeq ($(OS), Darwin)
SDL_INCLUDE = -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers
SDL_LIB = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
SDL_INCLUDE = -I/usr/include/SDL2
SDL_LIB = -L/usr/local/lib -lSDL2_image -lSDL2_ttf -lSDL2main -lSDL2
endif

CXX = g++
CXXFLAGS = -Wall -pedantic $(ARCH_FLAG) -fpermissive -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB) $(ARCH_FLAG)
EXE = solarHunter

MKDIR_P = mkdir -p
OUT_DIR = bin/$(OS)/$(ARCH)

# Files
O_STATE := src/engine/state/stateEngine.o
O_GRAPHICS := src/engine/graphics/graphics.o src/engine/graphics/textures.o
O_GUI := src/engine/gui/kiss_general.o src/engine/gui/kiss_posix.o src/engine/gui/kiss_widgets.o src/engine/gui/kiss_draw.o
O_ENGINE := $(O_GRAPHICS) $(O_GUI) $(O_STATE)

OBJS := src/main.o


all: bindir $(EXE) mediadir cleanobj

keep: bindir $(EXE) mediadir

$(EXE): $(O_ENGINE) $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(OUT_DIR)/$@

%.o: %.c
	$(CXX) $(CXXFLAGS) $< -o $@

mediadir:
	cp -rvp ./media $(OUT_DIR)/

bindir: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

cleanobj:
	find . -type f -name '*.o' -exec rm {} +

clean: cleanobj
	rm -rf bin
