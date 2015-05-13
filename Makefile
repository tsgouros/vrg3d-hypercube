CPP = g++
CPPFLAGS = -Wall -g
LDFLAGS = 

TARGET = chess demo hypercube


### These lines are for access to the VRG3D and G3D installation
### directories. All other necessary software is assumed to be
### installed in the system-wide directories.

ifeq ($(shell if [ -d /research/graphics ] ; then echo 1; fi),1)
  # CS Dept
  EXTRA_INCLUDES = -I$(G)/install_linux/include -I$(G)/install_linux/include/vrg3d
  EXTRA_LIBS = -L$(G)/install_linux/lib -L$(G)/install_linux/lib/vrg3d
else
  # CCV - Granoff
  EXTRA_INCLUDES = -I/share/cave/include
  EXTRA_LIBS = -L/share/cave/lib
endif


OBJDIR = obj

SRCS = $(shell ls *.cpp)

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

INCLUDE_DIRS = -I. $(EXTRA_INCLUDES)

LIB_DIRS = $(EXTRA_LIBS)

LIBS = -Xlinker --start-group  -Xlinker -ldl  -Xlinker -lX11 -Xlinker \
	-lXext  -Xlinker -lpthread  -Xlinker -lz  -Xlinker -ljpeg  -Xlinker \
	-lpng  -Xlinker -lzip  -Xlinker -lSDL -Xlinker -lvrg3d  -Xlinker \
	-lavutil  -Xlinker -lavformat  -Xlinker -lavcodec  -Xlinker -lGLG3Dd \
	-Xlinker -lG3Dd -Xlinker -lGLU -Xlinker -lGL -Xlinker --end-group \
	-lvrpn -lglut -lXmu

all: chess demo hypercube

chess: obj/chess.o obj/chess_demo.o
	$(CPP) $(LDFLAGS) -o chess $^ $(LIB_DIRS) $(LIBS)

demo: obj/vrg3d_demo.o
	$(CPP) $(LDFLAGS) -o demo $^ $(LIB_DIRS) $(LIBS)

#hypercube: obj/hypercube.o obj/hypercube_demo.o obj/Utility.o obj/Tetrahedron.o obj/ControlSpace.o
hypercube: obj/hypercube_demo.o obj/Utility.o obj/Tetrahedron.o obj/ControlSpace.o \
           obj/Hopf.o obj/Hypercube.o obj/Torus.o obj/SimpleInt.o
	$(CPP) $(LDFLAGS) -o hypercube $^ $(LIB_DIRS) $(LIBS)


#$(TARGET) : $(OBJS) 
#	$(CPP) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIB_DIRS) $(LIBS)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIRS)

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o demo-log.txt
	rm -rf $(OBJDIR)
