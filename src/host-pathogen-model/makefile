all: main

SOURCES := $(wildcard *.cc)

OBJECTS = $(SOURCES:cc=o) # essa parte vai ter que mudar

OBJDIR := build

$(OBJDIR)/%.o: %.cc \
    g++ -c -std=c++11 -I/usr/include/python3.8 -lpython3.8 -o \
    ${OBJDIR}/$@ $<

main: $(OBJECTS) \
    g++ $(OBJECTS) -o $@

clean: \
    rm main \