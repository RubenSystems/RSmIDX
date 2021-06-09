CPPFLAGS += -std=c++17
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)
TARGET = graphite

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK.cpp) $^ $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
