SHELL=/bin/sh

PROJECT_NAME = test-inspace
PROJECT_VER =-2.0
OBJDIR = obj

# specify project files
SRC = main.C Torus.C Hypercube.C Hopf.C TestApp.C SimpleInt.C ControlSpace.C Utility.C Tetrahedron.C
DOC = $(PROJECT_NAME).txt
CONFIG = glueconfig glueconfig-cave-devices glueconfig-icubex-test \
	 glueconfig-cave-btntest glueconfig-cave-devtest cloth1.rgb

DEFINES = USE_GLUT 

# library version numbers
GLUE_VER =      -double-2.0
INSPACE_VER = 	-2.0

G_INCLUDE_DIRS =	. gluebase$(GLUE_VER) inspace$(INSPACE_VER)
INCLUDE_DIRS =		.  ../gluebase-2.0 ../inspace-2.0 ..



# subdirs of $G/lib to include in the lib path
#G_LIB_DIRS = ../src/inspace-2.0/obj/ . gluebase$(GLUE_VER)
LIB_DIRS = ../lib

ifneq ($(findstring USE_OPENAL,$(DEFINES)),) 
  G_LIB_DIRS := $(G_LIB_DIRS) openal
endif

# static libs to link in in debugging/opt/profiling cases
DEBUG_LIBS =   	ggargs-d inspace$(INSPACE_VER)-d ivrnav-1.0-d
OPT_LIBS =      ggargs inspace$(INSPACE_VER) ivrnav-1.0
PROF_LIBS =     ggargs-p inspace$(INSPACE_VER)-p ivrnav-1.0-p

# shared libs to link in in debugging/opt/profiling cases
DEBUG_SHLIBS =  gluebase$(GLUE_VER)-sd
OPT_SHLIBS =    gluebase$(GLUE_VER)-s
PROF_SHLIBS =   gluebase$(GLUE_VER)-sp

# sometimes, there are architecture specific libs to link or 
# directories to include in the link path..
ifeq ($(GARCH),linux)
#  LIB_DIRS = /usr/X11R6/lib
  LIBS := $(LIBS) GLU GL glut X11 Xext Xmu pthread 
  ifneq ($(findstring USE_OPENAL,$(DEFINES)),) 
    LIBS := $(LIBS) openal
  endif
endif



all:	     progg
debug dbg:   progg 
opt:	     progo 
prof:	     progp

install:     inst-doc inst-config inst-prog
	gfxinstall3 -q cavebtntest   	    bin/cavebtntest
	gfxinstall3 -q cavebtntest-window   bin/cavebtntest-window
	gfxinstall3 -q cavedevtest   	    bin/cavedevtest
	gfxinstall3 -q cavedevtest-window   bin/cavedevtest-window

relink:	     FORCE
	     rm -f $(PROGO) $(PROGG) $(PROGP)
	     $(MAKE) debug


include $(G)/Make.gfxtools.rules
-include Makefile.depend

