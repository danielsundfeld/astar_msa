# msa_astar and msa_pastar Makefile

ASTAR_BIN   = msa_astar
PASTAR_BIN = msa_pastar

TARGET      = $(ASTAR_BIN) $(PASTAR_BIN)

INCDIR       = .

CPPFLAGS   += -W -Wall -std=c++11 -I/usr/include
LDFLAGS    += -lpthread

ifdef THREADS
    CPPFLAGS += -DTHREADS_NUM=$(THREADS)
endif

ifdef HASH_SHIFT
    CPPFLAGS += -DHASH_SHIFT=$(HASH_SHIFT)
endif

ifeq ($(HASH),FZORDER)
    CPPFLAGS += -DHASHFZORDER
else ifeq ($(HASH),PSUM)
    CPPFLAGS += -DHASHPSUM
else
    CPPFLAGS += -DHASHFSUM
endif

ifdef NO_LIB_BOOST
    CPPFLAGS += -DNO_LIB_BOOST
    COMMON_CPP_SRCS += MemoryWatcher.cpp
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

COMMON_CPP_SRCS += \
    backtrace.cpp \
    Coord.cpp \
    CoordHash.cpp \
    Cost.cpp \
    Heuristic.cpp \
    HeuristicHPair.cpp \
    Node.cpp \
    read_fasta.cpp \
    PairAlign.cpp \
    PriorityList.cpp \
    Sequences.cpp \
    SingletonKeep.cpp \

ASTAR_SRCS = \
    AStar.cpp \
    msa_astar_main.cpp \

PASTAR_SRCS = \
    msa_pastar_main.cpp \
    PAStar.cpp \

INCPATH += \
    -I$(INCDIR) \

CPPFLAGS += \
    $(INCPATH) \

COMMON_OBJS = $(COMMON_CPP_SRCS:.cpp=.o)
ASTAR_OBJS  = $(ASTAR_SRCS:.cpp=.o)
PASTAR_OBJS= $(PASTAR_SRCS:.cpp=.o)

all:		$(TARGET)
$(ASTAR_BIN):	$(COMMON_OBJS) $(ASTAR_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
$(PASTAR_BIN):	$(COMMON_OBJS) $(PASTAR_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
clean:
		rm -f $(TARGET) $(COMMON_OBJS) $(ASTAR_OBJS) $(PASTAR_OBJS)
