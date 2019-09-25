define gameRlsObj =
obj/Game.o \
obj/Grid.o \
obj/GridSector.o \
obj/Level.o \
obj/Main.o \
obj/Program.o \
obj/Program_Factory_Data/Reader.o \
obj/Program_Factory_Data/Writer.o
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

compileFlags = $(standard) $(linkLog) $(linkSFML)

rls: release
release: Spybot.exe
dbg: debug
debug: Spybot-dbg.exe
edit: editor
editor: Spybot-Editor.exe

include $(mkFiles)

Spybot.exe: $(gameRlsObj)
	g++ $(gameRlsObj) -o $@ $(compileFlags)

Spybot-dbg.exe: $(gameDbgObj)
	g++ -g $(gameDbgObj) -o $@ $(compileFlags)

Spybot-Editor.exe: $(editorObj)
	g++ $(editorObj) -o $@ $(compileFlags)

obj/%.o: src/%.cpp
	g++ -c $< -o $@ $(compileFlags)

obj/%-dbg.o: src/%.cpp
	g++ -g -c $< -o $@ $(compileFlags)

make/%.mk: src/%.cpp
	@set -e; rm -f $@; \
	g++ -MM $(stdDir) $< > $@.temp; \
	sed 's,\($*\)\.o[ :]*,obj/\1.o obj/\1-dbg.o $@: ,g' < $@.temp > $@; \
	rm -f $@.temp

clean:
	rm -f Spybot.exe
	rm -f Spybot-dbg.exe
	rm -f Spybot-Editor.exe
	rm -f obj/*.o