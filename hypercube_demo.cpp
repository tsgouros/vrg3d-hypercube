//  Copyright Regents of the University of Minnesota and Brown
//  University, 2010-2014.  All rights are reserved.

/*
 * \author Daniel Keefe (dfk)
 *
 * \file  vrg3d-chess.cpp
 *
 * Adapted from vrg3d_demo.cpp.
 */


#include <vrg3d/VRG3D.h>
#include <GL/glut.h>
using namespace G3D;

// ControlSpace class
#include "ControlSpace.h"

// 4D object classes
#include "Torus.h"
#include "Hopf.h"
#include "Hypercube.h"

// Interactor classes
//#include "FlyNavInt.h"
//#include "SimpleInt.h"

typedef enum{
  DRAW_HYPERCUBE=0,
  DRAW_HYPERCUBE_TORUS,
  DRAW_HYPERCUBE_TORUS_HOPF,
  DRAW_TORUS_HOPF,
  DRAW_TORUS,
  DRAW_HOPF,
} DRAW_MODE;


//extern void draw_pieces(), init_pieces();

/** This is a port of the inspace-2.0 version of hypercube **/


class MyVRApp : public VRApp
{
private:
    ControlSpace *control;

    Torus *torus;
    Hypercube *hypercube;
    Hopf *hopf;

    //    SimpleInt *wandInt;

    char wall_text[128];

    DRAW_MODE draw_mode;

public:
  MyVRApp(const std::string &mySetup) : VRApp()
  {

    // initialize the VRApp
     Log  *demoLog = new Log("demo-log.txt");
     init(mySetup, demoLog);

     _mouseToTracker = new MouseToTracker(getCamera(), 2);

     // Initialize the coordinate frame for the display.
    _virtualToRoomSpace = CoordinateFrame();

    // The default starting point has the eye level with the chess
    // board, which is confusing for the viewer on startup, and
    // renders poorly too. Let's move the virtual space up a few units
    // for a more sensible view.
    _virtualToRoomSpace = CoordinateFrame(Vector3(0,2.0,0)) * _virtualToRoomSpace;

    // This is the background -- the color that appears where there is
    // nothing to render, and we'll use a nice soothing blue.
    _clearColor = Color3(0.25, 0.25, 0.55);



    // initialize hypercube app
    torus = new Torus();
    hypercube = new Hypercube();
    hopf = new Hopf();

    //  control = new ControlSpace(torus, hypercube, hopf);
    control = new ControlSpace();

    //    wandInt = new SimpleInt(control, this);

    draw_mode = DRAW_HYPERCUBE_TORUS_HOPF;

#if 0
    // TODO: figure out how interaction is done in VRG3D....

    // default inspace interactors for the world and objects
    new WorldInt();
    new ObjectInt();

    //  new FlyNavInt();

    new IVRFlyGrab();
#endif

  }

  virtual ~MyVRApp() {
    if (torus)
      delete torus;
    if (hypercube)
      delete hypercube;
    if (hopf)
      delete hopf;


    //    if (wandInt)
    //      delete wandInt;
    if (control)
      delete control;
  }

  void doUserInput(Array<VRG3D::EventRef> &events)
  {
    // MouseToTracker is a really helpful class for testing out VR
    // interactions from the desktop.  This call makes it respond to
    // mouse events and generate new events as if it were a 6DOF
    // tracking device.  We add the new events to the event queue and
    // process them as usual.

    static double joystick_x = 0.0;
    static double joystick_y = 0.0;

    Array<VRG3D::EventRef> newEvents;
    _mouseToTracker->doUserInput(events, newEvents);
    events.append(newEvents);


    for (int i = 0; i < events.size(); i++) {

      if (events[i]->getName() == "kbd_ESC_down") {

	// Exit the program.
        while(glGetError() != GL_NO_ERROR) {  
	  std::cout<<"Flushing gl errors"<<std::endl;
	}

        exit(0);
      }

      // Save all the tracker events that come in so we can use them
      // in the doGraphics routine
      else if (endsWith(events[i]->getName(), "_Tracker"))
      {
        if (_trackerFrames.containsKey(events[i]->getName()))
        {
           _trackerFrames[events[i]->getName()] = events[i]->getCoordinateFrameData();
        }
        else
        {  _trackerFrames.set( events[i]->getName(),
                               events[i]->getCoordinateFrameData() );
        }
      }

      // Respond to events to do some simple navigation
      else if (events[i]->getName() == "kbd_LEFT_down")
      {  _virtualToRoomSpace = CoordinateFrame(Matrix3::fromAxisAngle(Vector3(0,1,0), toRadians(5.0))) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_RIGHT_down")
      {  _virtualToRoomSpace = CoordinateFrame(Matrix3::fromAxisAngle(Vector3(0,1,0), toRadians(-5.0))) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_UP_down")
      {  _virtualToRoomSpace = CoordinateFrame(Matrix3::fromAxisAngle(Vector3(1,0,0), toRadians(5.0))) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_DOWN_down")
      {  _virtualToRoomSpace = CoordinateFrame(Matrix3::fromAxisAngle(Vector3(1,0,0), toRadians(-5.0))) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_SHIFT_LEFT_down")
      {  _virtualToRoomSpace = CoordinateFrame(Vector3(-0.1,0,0)) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_SHIFT_RIGHT_down")
      {  _virtualToRoomSpace = CoordinateFrame(Vector3(0.1,0,0)) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_SHIFT_UP_down")
      {  _virtualToRoomSpace = CoordinateFrame(Vector3(0,0.1,0)) * _virtualToRoomSpace;
      }
      else if (events[i]->getName() == "kbd_SHIFT_DOWN_down")
      {  _virtualToRoomSpace = CoordinateFrame(Vector3(0,-0.1,0)) * _virtualToRoomSpace;
      }


      // Some printouts for other events, just to show how to access other types of event data
      else if (events[i]->getName() == "kbd_SPACE_down")
      {  cout << "Pressed the space key." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn1_down")
      {  cout << "Wand btn 1 pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn2_down")
      {  cout << "Wand btn 2 pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn3_down")
      {  cout << "Wand btn 3 pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn4_down")
      {  cout << "Wand btn 4 pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn6_down")
      {  cout << "Wand btn 6 pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn5_down")
      {  cout << "Wand joystick btn pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Btn6_down")
      {  cout << "Wand trigger btn pressed." << endl;
      }
      else if (events[i]->getName() == "Wand_Joystick_X")
      {   //cout << "Wand Joystick X = " << events[i]->get1DData() << endl;
          joystick_x = events[i]->get1DData();
      }
      else if (events[i]->getName() == "Wand_Joystick_Y")
      {   //cout << "Wand Joystick Y = " << events[i]->get1DData() << endl;
          joystick_y = events[i]->get1DData();
      }
      else if (events[i]->getName() == "Mouse_Pointer")
      {  static Vector2 lastPos;

         if (events[i]->get2DData() != lastPos)
         {  //  cout << "New mouse position = " << events[i]->get2DData() << endl;
            lastPos = events[i]->get2DData();
         }
      }
      else if (events[i]->getName() == "Mouse_Left_Btn_down")
      {  cout << "Mouse left btn pressed at position " << events[i]->get2DData() << endl;
      }
      else if (beginsWith(events[i]->getName(), "kbd_"))
      {  cout << "Keyboard event 1: " << events[i]->getName() << endl;
	cout << getCamera()->getHeadFrame() << endl;
	cout << _virtualToRoomSpace << endl;
      }
      else if (events[i]->getName() == "SpaceNav_Trans")
      {  cout << "Keyboard event 2: " << events[i]->getName()<< events[i]->get3DData() << endl;
      }
      else if (events[i]->getName() == "SpaceNav_Rot")
      {  cout << "Keyboard event 3: " << events[i]->getName()<< events[i]->get3DData() << endl;
      }
      else if (beginsWith(events[i]->getName(), "TNG_An"))
      {  cout << events[i]->getName() << "  " << events[i]->get1DData() << endl;
      }
      else if (events[i]->getName() == "SynchedTime")
      {  continue;
      }
      else
      {  // This will print out the names of all events, but can be too
         // much if you are getting several tracker updates per frame.
         // Uncomment this to see everything..
         cout << events[i]->getName() << endl;
      }

      // For debugging tracker coordinate systems, it can be useful to print out
      // tracker positions, like this:
      //
      if (events[i]->getName() == "Test_Tracker")
      {  cout << events[i]->getName() << " " << events[i]->getCoordinateFrameData().translation << endl;
      }
      
    // Rotate
    if (fabs(joystick_x) > 0.01) {
      //fprintf(stderr, "Joystick x: %lf\n", joystick_x);
      double angle = M_PI/180.0*joystick_x;
      angle /= 20.0;
      CoordinateFrame rotation = CoordinateFrame(Matrix3::fromEulerAnglesXYZ(0,angle,0));
      _virtualToRoomSpace = rotation*_virtualToRoomSpace;
    }

    // Translate
    if (fabs(joystick_y) > 0.0 && _trackerFrames.containsKey("Wand_Tracker") == true) {
      _virtualToRoomSpace.translation -= .005f*joystick_y*_trackerFrames[string("Wand_Tracker")].lookVector();
    }
     
    }  
    Array<std::string> trackerNames = _trackerFrames.getKeys();

    for (int i=0;i<trackerNames.size();i++)
    {  CoordinateFrame trackerFrame = _trackerFrames[trackerNames[i]];
    
        // Draw laser pointer.
        if (trackerNames[i] == "Wand_Tracker") {
            Vector3 lookVector = trackerFrame.lookVector();
            control->do_intersection(trackerFrame.translation, trackerFrame.translation+(1*lookVector));
        }
    }

  }

  void doGraphics(RenderDevice *rd)
  {
    // Load a font for the fps display, findVRG3DDataFile looks first
    // in the current directory and then in $G/src/VRG3D/share/
    //
    while(glGetError() != GL_NO_ERROR)
    {  //std::cout<<"Flushing gl errors"<<std::endl;
    }

    if (_font.isNull())
    {  std::string fontfile = VRApp::findVRG3DDataFile("eurostyle.fnt");

       if ( FileSystem::exists( fontfile ))
       {   std::cout << fontfile << std::endl;
           _font = GFont::fromFile( fontfile );
       }
    }

    Array<std::string> trackerNames = _trackerFrames.getKeys();

    for (int i=0;i<trackerNames.size();i++)
    {  CoordinateFrame trackerFrame = _trackerFrames[trackerNames[i]];
    
        // Draw laser pointer.
        if (trackerNames[i] == "Wand_Tracker") {
            Vector3 lookVector = trackerFrame.lookVector();

            glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT);

            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glLineWidth(4.0f);
            glColor4f(1.0f,0.0f,0.0f,1.0f);
            glBegin(GL_LINES);
            glVertex3f(trackerFrame.translation.x,
                       trackerFrame.translation.y,
                       trackerFrame.translation.z);
            glVertex3f(trackerFrame.translation.x + 1 * lookVector.x,
                       trackerFrame.translation.y + 1 * lookVector.y,
                       trackerFrame.translation.z + 1 * lookVector.z);
            glEnd();

            glPopAttrib();

       }

  }

    // The tracker frames above are drawn with the object to world
    // matrix set to the identity because tracking data comes into the
    // system in the Room Space coordinate system.  Room Space is tied
    // to the dimensions of the room and the projection screen within
    // the room, thus it never changes as your program runs.  However,
    // it is often convenient to move objects around in a virtual
    // space that can change relative to the screen.  For these
    // objects, we put a virtual to room space transform on the OpenGL
    // matrix stack before drawing them, as is done here..
    //
    rd->disableLighting();
    rd->pushState();
    rd->setObjectToWorldMatrix(_virtualToRoomSpace);
    
      /* Paramters for our light, including color and position */
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 3.0, 3.0, 0.0};
    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};

    glLightfv (GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, position);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv (GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    /*  These functions change how the object gets drawn */
    glEnable (GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_CULL_FACE);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);

    //  Use these if you plan to scale an object 
    //glEnable (GL_AUTO_NORMAL);
    //glEnable (GL_NORMALIZE);

    // If you want to do alpha blending:
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // This draws a simple piece of geometry using G3D::Draw at the
    // origin of Virtual Space.
    //
    //    Draw::axes( CoordinateFrame(), rd,
    //          Color3::red(), Color3::green(), Color3::blue(), 0.25 );
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glDisable( GL_COLOR_MATERIAL ); 
    
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glDisable(GL_LIGHTING);

    // BEGIN Hypercube draw
    update_geometry();

    draw_text();

    //    wandInt->drawWand();

 

    switch(draw_mode) {

    case DRAW_HYPERCUBE:
      hypercube->draw();
      break;
    case DRAW_HYPERCUBE_TORUS:
      hypercube->draw();
      torus->draw();
      break;
    case DRAW_HYPERCUBE_TORUS_HOPF:
      hypercube->draw();
      torus->draw();
      hopf->draw();
      break;
    case DRAW_TORUS_HOPF:
      torus->draw();
      hopf->draw();
      break;
    case DRAW_TORUS:
      torus->draw();
      break;
    case DRAW_HOPF:
      hopf->draw();
      break;
    default:
      break;
    }

    // END hypercube draw
        
    rd->popState();

    rd->pushState();
    glTranslatef(0.0, 2.0, 0.0);

       control->draw();
    rd->popState();
  }

  void update_geometry() {
    double a,b,c;
    control->get_abc(a, b, c);

    // go over all the geometry objects
    torus->update_geometry(a,b,c);
    hypercube->update_geometry(a,b,c);
    hopf->update_geometry(a,b,c);

    sprintf(wall_text, "a=%4.2f b=%4.2f c=%4.2f", a,b,c);
  }

  void draw_text()
  {
    //std::cerr << "hypercube_demo.cpp: draw_text not implemented..." << std::endl;
#if 0
    Wtransf myMat = Wtransf::align(Wpt(0,0,0),Wvec(1,0,0),Wvec(0,1,0),
				   Wpt(0,0,0),Wvec(1,0,0),Wvec(0,-1,0))*
      Wtransf::scaling(Wvec(0.08,0.08,0.08));

    glPushMatrix();
    //  glMultMatrixd((Wtransf::translation(Wvec(-2.3,-1.9,0)) *
    //                  myMat).matrix());
    glMultMatrixd((Wtransf::translation(Wvec(-3.5,-3.8,4.0)) *
		   myMat).matrix());

    FONTMGR::render(wall_text, 0.0,0.0,0.0);
    glPopMatrix();
#endif
  }


  void toggle_drawmode() {
    switch(draw_mode) {
    case DRAW_HYPERCUBE:
      draw_mode = DRAW_HYPERCUBE_TORUS;
      break;
    case DRAW_HYPERCUBE_TORUS:
      draw_mode = DRAW_HYPERCUBE_TORUS_HOPF;
      break;
    case DRAW_HYPERCUBE_TORUS_HOPF:
      draw_mode = DRAW_TORUS_HOPF;
      break;
    case DRAW_TORUS_HOPF:
      draw_mode = DRAW_TORUS;
      break;
    case DRAW_TORUS:
      draw_mode = DRAW_HOPF;
      break;
    case DRAW_HOPF:
      draw_mode = DRAW_HYPERCUBE;
      break;
    default:
      draw_mode = DRAW_HYPERCUBE;
      break;
    }
  }


protected:
  Table<std::string, CoordinateFrame> _trackerFrames;
  GFontRef          _font;
  MouseToTrackerRef _mouseToTracker;
  CoordinateFrame   _virtualToRoomSpace;
};




int main( int argc, char **argv )
{
  // The first argument to the program tells us which of the known VR
  // setups to start
  std::string setupStr;
  MyVRApp *app;
  
  if (argc >= 2)
  {  setupStr = std::string(argv[1]);
  }

  // This opens up the graphics window, and starts connections to
  // input devices, but doesn't actually start rendering yet.
  
    app = new MyVRApp(setupStr);

    // This starts the rendering/input processing loop
    app->run();

  return 0;
}


//
////////////////////  end  common/vrg3d/demo/vrg3d_demo.cpp  ///////////////////
