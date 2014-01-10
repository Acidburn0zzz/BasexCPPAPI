CXX=g++
RM=rm -f
CPPFLAGS=
LDFLAGS=
LDLIBS=-lboost_system -lpugixml

SRCS=BaseXExample.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all: BaseXExample

BaseXExample: $(OBJS)
	g++ $(LDFLAGS) -o BaseXExample $(OBJS) $(LDLIBS) 

BaseXExample.o: BaseXExample.cpp BasexExample.h

clean:
	$(RM) BaseXExample

dist-clean: clean
	$(RM) BaseXExample
