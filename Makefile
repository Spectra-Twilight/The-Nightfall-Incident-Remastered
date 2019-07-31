source = $(wildcard src/*.cpp)
debugObj = $(source:.cpp=-dbg.o)
debugObj := $(subst src, obj, $(debugObj))
releaseObj = $(debugObj:-dbg.o=.o)
mkFiles = $(source:.cpp=.mk)
mkFiles := $(subst src, make, $(mkFiles))

# Links in the logging library.
linkLog = -lLog

# Links in the SFML library.
linkSFML = -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

# Defines standard directories for headers and libraries.
stdDir = -I'include/' -L'lib/'

compileFlags = $(stdDir) $(linkLog) $(linkSFML)

rls: release
release: Spybot.exe
dbg: debug
debug: Spybot-dbg.exe

include $(mkFiles)

Spybot.exe: $(releaseObj)
	g++ $(releaseObj) -o Spybot.exe $(compileFlags)

Spybot-dbg.exe: $(debugObj)
	g++ -g $(debugObj) -o Spybot-dbg.exe $(compileFlags)

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
	rm -f obj/*.o