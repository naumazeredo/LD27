# C++ Compiler
CXX=g++
CXXFLAGS=-c -O -Wall -std=c++11
LDFLAGS = $(addprefix -L,$(LIBSSOURCE)) $(addprefix -l,$(LIBS))

SOURCES := $(wildcard src/*.cpp) \
	$(wildcard src/render/*.cpp)
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = nafw

vpath %.cpp src/
vpath %.cpp src/render/

LIBS := mingw32 SDL2main SDL2 SDL2_image SDL2_net
LIBSSOURCE := "C:\SDL-2.0.0-mingw\lib"

debug: CXX += -DDEBUG
debug: $(SOURCES) $(EXECUTABLE)
release: CXX += -DSDL_ASSERT_LEVEL=1
release: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJECTS): | obj

obj:
	mkdir $@

obj/%.o: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	- $(RM) -R obj $(addsuffix .exe,$(EXECUTABLE))

rebuild:
	make clean
	make
