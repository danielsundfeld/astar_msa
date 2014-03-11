# msa_a_star bin Makefile

TARGET       = msa_a_star

INCDIR       = .

CPPFLAGS   += -W -Wall -std=c++11 -I/usr/include

ifdef NO_LIB_BOOST
    CPPFLAGS += -DNO_LIB_BOOST
endif
ifdef RELEASE
    CPPFLAGS   += -O2
    LDFLAGS  += -s
else
    CPPFLAGS   += -O0 -g
endif

ifdef PROFILE
    CPPFLAGS += -pg
    LDFLAGS += -pg
endif

CPP_SRCS = \
    AStar.cpp \
    backtrace.cpp \
    Coord.cpp \
    Cost.cpp \
    Heuristic.cpp \
    HeuristicHPair.cpp \
    main.cpp \
    MemoryWatcher.cpp \
    Node.cpp \
    read_fasta.cpp \
    PairAlign.cpp \
    PriorityList.cpp \
    Sequences.cpp \
    SingletonKeep.cpp \

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
