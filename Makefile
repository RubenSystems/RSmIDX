CPPFLAGS += -std=c++17 -fPIC
CC = clang++


SOURCES=$(wildcard sources/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
TARGET = graphite`python3-config --extension-suffix`

.PHONY: all
all: $(OBJECTS) binding.o

# $(TARGET): $(OBJECTS)
# 	$(CC) $(CPPFLAGS) $^ $(LDLIBS) -o $@
#old $(LINK.cpp) $^ $(LDLIBS) -o $@

# $(TARGET): $(OBJECTS)
# 	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

# $(SOURCES):
	
# EXCLUDE dynamic_lookup ON RASPI
binding.o:
	c++ -O3 -Wall -fPIC -shared -std=c++17 -undefined `python3 -m pybind11 --includes` Binding.cpp -o rsmidx`python3-config --extension-suffix` $(OBJECTS) 

# $(OBJECTS): sources/%.o : sources/%.cpp
# 	$(CC) $(CPPFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@



	

.PHONY: clean
clean:
	rm -f $(OBJECTS)
