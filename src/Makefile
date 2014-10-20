# msa_astar and msa_pastar Makefile

ASTAR_BIN   = msa_astar
PASTAR_BIN = msa_pastar

TARGET      = $(ASTAR_BIN) $(PASTAR_BIN)

INCDIR       = .

CPPFLAGS   += -W -Wall -std=c++11 -I/usr/include
LDFLAGS    += -lpthread -lboost_program_options

ifdef THREADS
    CPPFLAGS += -DTHREADS_NUM=$(THREADS)
endif

ifdef HASH_SHIFT
    CPPFLAGS += -DHASH_SHIFT=$(HASH_SHIFT)
endif

ifdef NO_LIB_BOOST
    CPPFLAGS += -DNO_LIB_BOOST
endif

ifndef DEBUG
    OPTIMIZE = yes
    LDFLAGS += -s
else
    CPPFLAGS += -g
endif

ifdef OPTIMIZE
    CPPFLAGS += -O3
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
    HeuristicHPair.cpp \
    msa_options.cpp \
    Node.cpp \
    read_fasta.cpp \
    PairAlign.cpp \
    Sequences.cpp \
    SingletonKeep.cpp \
    TimeCounter.cpp \

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
