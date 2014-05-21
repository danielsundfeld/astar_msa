# msa_a_star bin Makefile

TARGET       = z_order_ops

INCDIR       = ../../src/
VPATH        = ../../src/

CPPFLAGS   += -Wall -std=c++11

ifdef RELEASE
    CPPFLAGS   += -O2
    LDFLAGS  += -s
else
    CPPFLAGS   += -O0 -g
endif

CPP_SRCS = \
    Coord.cpp \
    CoordHash.cpp \
    z_order_ops.cpp \

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
		+make -C $(VPATH) $@
