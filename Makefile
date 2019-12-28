define gameRlsObj =
obj/Game.o \
obj/Grid.o \
obj/GridSector.o \
obj/Level.o \
obj/Main.o \
obj/Program.o
endef

gameDbgObj = $(gameRlsObj:.o=-dbg.o)

define editorObj = 
obj/Main-Editor.o
endef

allSrc = $(wildcard src/*.cpp)
mkFiles = $(allSrc:.cpp=.mk)
mkFiles := $(subst src, make, $(mkFiles))

# Links in the logging library.
linkLog = -lLog

# Links in the SFML library.
linkSFML = -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

# Defines standard directories for headers and libraries.
standard = -I'include/' -L'lib/' -std=c++17

cxxFlags = $(standard) $(linkLog) $(linkSFML)

rls: release
release: Nightfall.exe
dbg: debug
debug: Nightfall-dbg.exe
edit: editor
editor: Nightfall-Editor.exe

include $(mkFiles)

Nightfall.exe: $(gameRlsObj)
	g++ $^ -o $@ $(cxxFlags)

Nightfall-dbg.exe: $(gameDbgObj)
	g++ -g $^ -o $@ $(cxxFlags)

Nightfall-Editor.exe: $(editorObj)
	g++ $^ -o $@ $(cxxFlags)

obj/%.o: src/%.cpp
	g++ -c $< -o $@ $(cxxFlags)

obj/%-dbg.o: src/%.cpp
	g++ -g -c $< -o $@ $(cxxFlags)

make/%.mk: src/%.cpp
	@set -e; rm -f $@; \
	g++ -MM $(stdDir) $< > $@.temp; \
	sed 's,\($*\)\.o[ :]*,obj/\1.o obj/\1-dbg.o $@: ,g' < $@.temp > $@; \
	rm -f $@.temp

clean:
	rm -f Nightfall.exe
	rm -f Nightfall-dbg.exe
	rm -f Nightfall-Editor.exe
	rm -f obj/*.o