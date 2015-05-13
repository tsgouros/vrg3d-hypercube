
#ifndef TESTAPP_H
#define TESTAPP_H

#include "ISApp.H"

// ControlSpace class
#include "ControlSpace.H"

// 4D object classes
#include "Torus.H"
#include "Hopf.H"
#include "Hypercube.H"

// Interactor classes
#include "FlyNavInt.H"
#include "SimpleInt.H"

typedef enum{
  DRAW_HYPERCUBE=0, 
    DRAW_HYPERCUBE_TORUS,
    DRAW_HYPERCUBE_TORUS_HOPF,
    DRAW_TORUS_HOPF,
    DRAW_TORUS,
    DRAW_HOPF,
    } DRAW_MODE;

class TestApp : public ISApp
{

private:
  ControlSpace *control;

  Torus *torus;
  Hypercube *hypercube;
  Hopf *hopf;

  SimpleInt *wandInt;

  char wall_text[128];
  void update_geometry();

  DRAW_MODE draw_mode;

public:
  TestApp();
  virtual ~TestApp();

  void splashScreen();

  void postSplashInit();
  void postSplashGLContextInit();
  
  void draw();
  void draw_text();
  
  void toggle_drawmode();
};


#endif
