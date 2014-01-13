CXX=g++
RM=rm -f
CPPFLAGS=
LDFLAGS=
LDLIBS=-lboost_system -lpthread

SRCS=BaseXExample.cpp pugi/src/pugixml.cpp md5.c
OBJS=$(subst .cc,.o,$(SRCS))

all: BaseXExample

BaseXExample: $(OBJS)
	g++ $(LDFLAGS) -o BaseXExample $(OBJS) $(LDLIBS) 

BaseXExample.o: BaseXExample.cpp BaseXExample.h BaseXClient.h

clean:
	$(RM) BaseXExample

dist-clean: clean
	$(RM) BaseXExample
