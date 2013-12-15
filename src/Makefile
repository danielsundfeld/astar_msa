# msa_a_star bin Makefile

TARGET       = msa_a_star

INCDIR       = .

CPPFLAGS   += -Wall

ifdef RELEASE
    CPPFLAGS   += -O2
    LDFLAGS  += -s
else
    CPPFLAGS   += -O0 -g
endif

CPP_SRCS = \
    AStar.cpp \
    backtrace.cpp \
    Coord.cpp \
    Cost.cpp \
    HeuristicAllP2.cpp \
    main.cpp \
    Node.cpp \
    read_fasta.cpp \
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
