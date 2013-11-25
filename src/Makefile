# Makefile para geracao do 'msa'

TARGET       = msa_a_star

VDIR         = .
INCDIR       = .

CFLAGS   += -pipe -Wall

ifdef RELEASE
  CFLAGS   += -O2
  LDFLAGS  += -s
else
  CFLAGS   += -O0 -g
endif

CPP_SRCS = \
  main.cpp \
  Coords.cpp \
  Node.cpp \

VPATH += \
  $(VDIR)/vpath \

INCPATH += \
  -I$(INCDIR)/include \

CFLAGS += \
  $(INCPATH) \

CPP_OBJS  = $(CPP_SRCS:.cpp=.o)

all:		$(TARGET)
$(TARGET):	$(CPP_OBJS)
		$(CXX) $(LDFLAGS) $^ -o $@
clean:
		rm -f $(TARGET) $(CPP_OBJS)
