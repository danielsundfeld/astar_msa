# msa_astar and msa_pfa2dd Makefile

ASTAR_BIN   = msa_astar
PFA2DDD_BIN = msa_pfa2ddd

TARGET      = $(ASTAR_BIN) $(PFA2DDD_BIN)

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

COMMON_CPP_SRCS = \
    backtrace.cpp \
    Coord.cpp \
    Cost.cpp \
    Heuristic.cpp \
    HeuristicHPair.cpp \
    MemoryWatcher.cpp \
    Node.cpp \
    read_fasta.cpp \
    PairAlign.cpp \
    PriorityList.cpp \
    Sequences.cpp \
    SingletonKeep.cpp \

ASTAR_SRCS = \
    AStar.cpp \
    msa_astar_main.cpp \

PFA2DDD_SRCS = \
    msa_pfa2ddd_main.cpp \
    PFA2DDD.cpp \

INCPATH += \
    -I$(INCDIR) \

CPPFLAGS += \
    $(INCPATH) \

COMMON_OBJS = $(COMMON_CPP_SRCS:.cpp=.o)
ASTAR_OBJS  = $(ASTAR_SRCS:.cpp=.o)
PFA2DDD_OBJS= $(PFA2DDD_SRCS:.cpp=.o)

all:		$(TARGET)
$(ASTAR_BIN):	$(COMMON_OBJS) $(ASTAR_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
$(PFA2DDD_BIN):	$(COMMON_OBJS) $(PFA2DDD_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
clean:
		rm -f $(TARGET) $(COMMON_OBJS) $(ASTAR_OBJS) $(PFA2DDD_OBJS)
