
BUILDDIR = build/Breakout-SDL2
## Create build directory.
$(shell mkdir -p $(BUILDDIR))
TARGET = $(BUILDDIR)/game
SOURCEDIR=../src
OBJDIR =../obj
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp $(SOURCEDIR)/*/*.cpp $(SOURCEDIR)/*/*/*.cpp $(SOURCEDIR)/*/*/*/*.cpp)
OBJS = $(patsubst $(SOURCEDIR)/%.cpp,$(SOURCEDIR)/%.o,$(SOURCES))
PSP_LARGE_MEMORY = 1

INCDIR = ../include/psp ../src/engine
CFLAGS = -Os -G0 -Wall -DPSP -DLUA_USE_C89 -DLUA_32BITS -DLUA_C89_NUMBERS
CXXFLAGS = $(CFLAGS) -fexceptions -fno-rtti -std=c++14
ASFLAGS = $(CFLAGS)

LIBDIR = libs


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Breakout-SDL2
PSP_EBOOT_ICON = ../resources/psp/ICON.png

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += $(shell $(PSPBIN)/sdl-config --cflags)c
#LIBS += $(shell $(PSPBIN)/sdl-config --libs) 
LIBS += -lSDL2 -lSDL2_mixer -logg -lSDL2  -lvorbisidec  -lz -lm -lSDL2_image -lpng -ljpeg -lSDL2_ttf -lfreetype -lGL -lGLU -lglut -lz -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc \
       -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
	   -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -llua -lm -lpspvram  -lSDLmain
LIBS += -lstdc++ -lpspirkeyb -lpsppower
include $(PSPSDK)/lib/build.mak
## Copy resources:
copy-all: 
	$(shell cp -r ../resources $(BUILDDIR))
	$(shell mv -f ${EXTRA_TARGETS} $(BUILDDIR))
	$(shell mv  -f PARAM.SFO $(BUILDDIR))

clear-all:
	$(shell rm -rf $(BUILDDIR))
