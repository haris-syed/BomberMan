CXXFLAGS =	-g3 -Wall -fmessage-length=0 #-Werror

OBJS =		 BomberMan.o util.o Board.o Drawable.o Pacman.o Character.o Ghost.o Inky.o Pinky.o Blinky.o Clyde.o

LIBS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage



TARGET =	BomberMan


$(TARGET):	$(OBJS) 
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)