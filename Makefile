# msa_astar and msa_pastar Makefile

# Choose -std=c++11 or -std=c++0x
CXXVERSION = $(shell $(CXX) -dumpversion | cut -b 1-3)
ifneq "$(filter g++,$(CXX))" ""
ifeq "$(CXXVERSION)" "4.6"
CPPSTD = -std=c++0x
endif
ifeq "$(CXXVERSION)" "4.4"
$(error Bad $(CXX) version $(CXXVERSION). Atomic operations are required)
endif
endif

ifeq "$(CPPSTD)" ""
CPPSTD = -std=c++11
endif

BIN_DIR     = ./bin
ASTAR_BIN   = $(BIN_DIR)/msa_astar
PASTAR_BIN  = $(BIN_DIR)/msa_pastar

TARGET      = $(PASTAR_BIN) $(ASTAR_BIN)

SRC_DIR     = ./src
INC_DIR     = ./src
OBJ_DIR     = ./obj
CPPFLAGS   += -W -Wall $(CPPSTD)
LDFLAGS    += -pthread -lstdc++ -lm -lboost_program_options -lboost_system -lboost_filesystem

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

ifdef PAIRALIGN
    CPPFLAGS += -D PAIRALIGN_SCORE
endif

VERSION_FILE = src/version.h

COMMON_CPP_SRCS += \
    $(SRC_DIR)/backtrace.cpp \
    $(SRC_DIR)/Coord.cpp \
    $(SRC_DIR)/CoordHash.cpp \
    $(SRC_DIR)/Cost.cpp \
    $(SRC_DIR)/HeuristicHPair.cpp \
    $(SRC_DIR)/msa_options.cpp \
    $(SRC_DIR)/Node.cpp \
    $(SRC_DIR)/read_fasta.cpp \
    $(SRC_DIR)/PairAlign.cpp \
    $(SRC_DIR)/Sequences.cpp \
    $(SRC_DIR)/TimeCounter.cpp \

ASTAR_SRCS = \
    $(SRC_DIR)/AStar.cpp \
    $(SRC_DIR)/msa_astar_main.cpp \

PASTAR_SRCS = \
    $(SRC_DIR)/msa_pastar_main.cpp \
    $(SRC_DIR)/PAStar.cpp \

INC_PATH += \
    -I$(INC_DIR)\
    -I/usr/include

CPPFLAGS += $(INC_PATH)

COMMON_OBJS = $(COMMON_CPP_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
ASTAR_OBJS  = $(ASTAR_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
PASTAR_OBJS = $(PASTAR_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all:	$(VERSION_FILE) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<
$(COMMON_OBJS):	| $(OBJ_DIR)
$(ASTAR_OBJS):	| $(OBJ_DIR)
$(PASTAR_OBJS):	| $(OBJ_DIR)

$(VERSION_FILE):
	@utils/version.sh

$(ASTAR_BIN):	$(COMMON_OBJS) $(ASTAR_OBJS) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
$(PASTAR_BIN):	$(COMMON_OBJS) $(PASTAR_OBJS) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(COMMON_OBJS) $(PASTAR_OBJS) $(ASTAR_OBJS)
