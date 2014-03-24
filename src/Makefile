# msa_a_star bin Makefile

TARGET       = msa_a_star

INCDIR       = .

CPPFLAGS   += -W -Wall -std=c++11 -I/usr/include
LDFLAGS    += -lpthread

ifdef NO_LIB_BOOST
    CPPFLAGS += -DNO_LIB_BOOST
endif

ifdef RELEASE
    OPTIMIZE = yes
    LDFLAGS += -s
else
    CPPFLAGS += -g
endif

ifdef OPTIMIZE
    CPPFLAGS += -O2
else
    CPPFLAGS += -O0
endif

ifdef PROFILE_GENERATE
    CPPFLAGS += -fprofile-generate
    LDFLAGS  += -fprofile-generate
endif

ifdef PROFILE_USE
    CPPFLAGS += -fprofile-use
    LDFLAGS += -fprofile-use
endif

ifdef PROFILE_INFORMATION
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
    PFA2DDD.cpp \
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
