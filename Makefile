OS := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
	ARCH = x64
	ARCH_FLAG = -m64
endif
ifneq ($(filter %86,$(UNAME_M)),)
	ARCH = i386
	ARCH_FLAG = -m32
endif
ifneq ($(filter arm%,$(UNAME_M)),)
	ARCH = ARM
	ARCH_FLAG = -m32
endif

ifeq ($(OS), Darwin)
SDL_INCLUDE = -I/Library/Frameworks/SDL2.framework/Headers
SDL_LIB = -framework SDL2
else
SDL_INCLUDE = -I/usr/local/include
SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
endif

CXX = g++
CXXFLAGS = -Wall -pedantic $(ARCH_FLAG) -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB) $(ARCH_FLAG)
EXE = solarHunter

MKDIR_P = mkdir -p
OUT_DIR = bin/$(OS)/$(ARCH)


# Files
OBJS := src/utils.o src/main.o


all: bindist $(EXE) cleanobj

keep: bindist $(EXE)

$(EXE): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(OUT_DIR)/$@

%.o: %.c
	$(CXX) $(CXXFLAGS) $< -o $@

bindist: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

cleanobj:
	rm -f **/*.o

clean: cleanobj
	rm -rf bin
