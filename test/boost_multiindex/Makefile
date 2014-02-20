# msa_a_star bin Makefile

TARGET       = multiindex

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
    Coord.cpp \
    Cost.cpp \
    multiindex.cpp \
    Heuristic.cpp \
    HeuristicHPair.cpp \
    Node.cpp \
    PairAlign.cpp \
    Sequences.cpp \
    read_fasta.cpp \
#    backtrace.cpp \
    SingletonKeep.cpp \

INCPATH += \
    -I$(INCDIR) \
    -I/usr/include \

CPPFLAGS += \
    $(INCPATH) \

CPP_OBJS  = $(CPP_SRCS:.cpp=.o)

all:		$(TARGET)
$(TARGET):	$(CPP_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
clean:
		rm -f $(TARGET) $(CPP_OBJS)
		+make -C $(VPATH) $@
