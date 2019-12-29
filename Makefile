define game_rls_obj =
obj/Nightfall/Game.o \
obj/Nightfall/Grid.o \
obj/Nightfall/GridSector.o \
obj/Nightfall/Level.o \
obj/Nightfall/Main.o \
obj/Nightfall/Program.o
endef

game_dbg_obj = $(game_rls_obj:.o=-dbg.o)
game_dbg_obj := $(patsubst obj/Nightfall/%, obj/Nightfall-dbg/%, $(game_dbg_obj))

define editor_obj = 
obj/Main-Editor.o
endef

all_src = $(wildcard src/Nightfall/*.cpp)
mk_files = $(all_src:.cpp=.mk)
mk_files := $(patsubst src%, make%, $(mk_files))

# Links in the SFML library.
linkSFML = -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

# Defines standard directories for headers and libraries.
standard = -I'include/' -L'lib/' -std=c++17

cxxflags = $(standard) -lLog $(linkSFML)

r: release
rls: release
release: Nightfall.exe
d: debug
dbg: debug
debug: Nightfall-dbg.exe
e: editor
edit: editor
editor: Nightfall-Editor.exe

include $(mk_files)

Nightfall.exe: $(game_rls_obj)
	g++ -O3 $^ -o $@ $(cxxflags)

Nightfall-dbg.exe: $(game_dbg_obj)
	g++ -g $^ -o $@ $(cxxflags)

Nightfall-Editor.exe: $(editor_obj)
	g++ $^ -o $@ $(cxxflags)

obj/Nightfall/%.o: src/Nightfall/%.cpp obj/Nightfall/dummy
	g++ -O3 -c $< -o $@ $(cxxflags)

obj/Nightfall-dbg/%-dbg.o: src/Nightfall/%.cpp obj/Nightfall-dbg/dummy
	g++ -g -c $< -o $@ $(cxxflags)

make/Nightfall/%.mk: src/Nightfall/%.cpp make/Nightfall/dummy
	@set -e; rm -f $@; \
	g++ -MM $(stdDir) $< > $@.temp; \
	sed 's,\($*\)\.o[ :]*,obj/\1.o obj/\1-dbg.o $@: ,g' < $@.temp > $@; \
	rm -f $@.temp

# The dummy pattern will ensure the creation of a 
# directory if it does not exist already.
%/dummy:
	mkdir -p $*
	touch $@

clean:
	rm -f Nightfall.exe
	rm -f Nightfall-dbg.exe
	rm -f Nightfall-Editor.exe
	rm -f -r obj/**
	rm -f -r make/**