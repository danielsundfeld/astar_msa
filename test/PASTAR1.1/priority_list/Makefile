TARGET       = priority_ops

BASEDIR      = ../..
INCDIR       = ../../src/
VPATH        = ../../src/

CPPFLAGS   += -Wall -std=c++11

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
    TimeCounter.cpp \

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
