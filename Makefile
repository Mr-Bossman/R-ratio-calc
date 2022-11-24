BUILD_DIR = build
CXX = g++
CXXFLAGS = -O3 -Wall -pedantic
CXX_SOURCES = src/Eseries.cpp src/main.cpp
CXX_INCLUDES = -Iinclude
CXXFLAGS += $(CXX_INCLUDES)

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

all: clean main

run: all
	./main

clean:
	rm -f main

clean-all: clean
	rm -f ${BUILD_DIR}/*

$(BUILD_DIR)/%.o: %.cpp
	${CXX} -c $(CXXFLAGS) $< -o $@

main: $(OBJECTS)
	${CXX} ${CXXFLAGS} -o main $(OBJECTS)
