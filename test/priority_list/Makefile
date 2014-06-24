TARGET       = priority_ops

INCDIR       = ../../src/
VPATH        = ../../src/

CPPFLAGS   += -Wall -std=c++11 -DHASHFZORDER

ifdef RELEASE
    CPPFLAGS   += -O2
    LDFLAGS  += -s
else
    CPPFLAGS   += -O0 -g
endif

CPP_SRCS = \
    backtrace.cpp \
    Coord.cpp \
    CoordHash.cpp \
    Cost.cpp \
	 HeuristicHPair.cpp \
    Node.cpp \
    priority_ops.cpp \
	 PairAlign.cpp \
    Sequences.cpp \

INCPATH += \
    -I$(INCDIR) \

CPPFLAGS += \
    $(INCPATH) \

CPP_OBJS  = $(CPP_SRCS:.cpp=.o)

all:		$(TARGET)
$(TARGET):	$(CPP_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
clean:
		rm -f $(TARGET) $(CPP_OBJS)
		+make -C $(VPATH) $@
