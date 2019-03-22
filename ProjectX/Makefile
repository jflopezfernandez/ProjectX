
#==============================================================
#
#                            PROJECT X
#
# =============================================================

vpath %.cpp src
vpath %.hpp include

.SUFFIXES:
.SUFFIXES: .cpp .hpp

SHELL         = /bin/sh

COMPILERWARN  = -Wall -Wextra -Wpedantic
OPTIMIZATIONS = -Ofast -mtune=intel -march=skylake -mavx2
BUILDFLAGS    =    $(COMPILERWARN) $(OPTIMIZATIONS)

ASM           =  nasm
CC            =  gcc
CXX           =  g++
CFLAGS        = -std=c11   $(BUILDFLAGS)
CXXFLAGS      = -std=c++17 $(BUILDFLAGS)

SOURCES_DIR   = src
INCLUDES_DIR  = include

MKLHEADERS    = -I $(INTELMKLINCLUDEDIR) 
INTELINCLUDES =    $(MKLHEADERS)
SRC_HEADERS   = -I $(INCLUDES_DIR)
INCLUDEDIRS   =    $(SRC_HEADERS)

MATHLIB       = -lm
CPPFILESYSTEM = -lstdc++fs
LIBGMP        = -lgmp
INTEL_MKL     = -L $(INTELMKLLIBDIR) -lmkl
INTEL_LIBS    =    $(IPPLIB) $(IPPCPLIB)
BOOSTOPTS     = -lboost_program_options
BOOSTLIBS     =    $(BOOSTOPTS)
REQLIBS       =    $(MATHLIB) $(CPPFILESYSTEM) $(LIBGMP) $(BOOSTLIBS)

SRCS          = ProjectX.cpp
HDRS          = $(patsubst %.cpp, %.hpp, $(SRCS))
OBJS          = $(patsubst %.cpp, %.o, $(SRCS))
PROGRAM       = x

OUTPUT_OPTION = -o $@
TARGET_ARCH   = 

COMPILE.c     = $(CC)  $(CFLAGS)   $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) -c
LINK.c        = $(CC)  $(CFLAGS)   $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) $(LDFLAGS)
COMPILE.cpp   = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) -c
LINK.o        = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) $(LDFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LINK.o) $(OUTPUT_OPTION) $^ $(REQLIBS)

%.o: %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $^ 

.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROGRAM)
