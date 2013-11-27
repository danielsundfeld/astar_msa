# Makefile para geracao do 'msa'

TARGET       = msa_a_star

VDIR         = .
INCDIR       = .

CPPFLAGS   += -pipe -Wall

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
  read_fasta.cpp \

VPATH += \
  $(VDIR)/vpath \

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
