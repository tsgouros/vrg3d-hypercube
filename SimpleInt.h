#ifndef __SIMPLEINT_H_
#define __SIMPLEINT_H_

#include <vrg3d/VRG3D.h>

using namespace G3D;

//#include "ISApp.H"

/* #include <fsa/fsa.H> */
/* #include <dev/room6d.H> */
/* #include <dev/buttons.H> */
/* #include <dev/dev2d.H> */
/* #include <dev/polled.H> */
/* #include "mlib/points.H" */

#include "ControlSpace.h"

/* class TestApp; */
class MyVRApp;

//class SimpleInt : public Interactor<SimpleInt> {
// TODO: adapt to VRG3D tracker/buttons interactor
class SimpleInt {
 public:
  /* SimpleInt(ControlSpace *c, TestApp* t); */
  SimpleInt(ControlSpace *c, MyVRApp* t);

  /* void idle(cEVENTroom6dptr &, STATE *&); */
  /* void down(cEVENTbtnptr &, STATE *&); */
  /* void move(cEVENTroom6dptr &, STATE *&); */
  /* void up  (cEVENTbtnptr &, STATE *&); */

  /* void toggle_control(cEVENTbtnptr &e, STATE *&); */
  /* void toggle_drawn_object(cEVENTbtnptr &e, STATE *&); */

  void drawWand();
  void draw_text();
  
 protected:
  
  Vector3 wand_begin, wand_end;
  CoordinateFrame _cur;
  int activate_wand; // both draw it and update the control space

  ControlSpace *_control;
  MyVRApp *_app;

};

#endif
