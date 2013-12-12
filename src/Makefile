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
  main.cpp \
  Coord.cpp \
  Node.cpp \
  AStar.cpp \
  Sequences.cpp \
  SequencesKeep.cpp \
  read_fasta.cpp \
  backtrace.cpp \

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
