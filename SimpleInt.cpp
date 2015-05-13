//#include <sys/time.h>
//#include <std/time.H>


// TODO: adapt this whole file to VRG3D stlye of interaction..


#include "SimpleInt.h"
//#include "WorldTranslate.H"


// Font stuff
// #include "FontMgr.H"

//#include "TestApp.H"

// TODO-- move this class definition to a header file, and is consistent with hypercube_demo.cpp
class MyVRApp : public VRApp
{
public:
  MyVRApp(const std::string &mySetup);
  virtual ~MyVRApp();
  void doUserInput(Array<VRG3D::EventRef> &events);
  void doGraphics(RenderDevice *rd);
  void update_geometry();
  void draw_text();
  void toggle_drawmode();
};

//////////////////////////////

//SimpleInt::SimpleInt(ControlSpace *c, TestApp *t) : Interactor<SimpleInt>("SimpleInt")
SimpleInt::SimpleInt(ControlSpace *c, MyVRApp *t)
{
  // static STATE move_s ("SimpleInt_move");

  // // 1. Direct manip navigation
  // _entry += Arc(this, Gd(new EVENTroom6d("wand_tracker")),    &SimpleInt::idle);
  // _entry += Arc(this, Gd(new EVENTbtn   ("wanda_but_blue")), &SimpleInt::toggle_control);
  // _entry += Arc(this, Gd(new EVENTbtn   ("wanda_but_red")), &SimpleInt::toggle_drawn_object);
  // _entry += Arc(this, Gd(new EVENTbtn   ("wanda_but_yellow")), &SimpleInt::down, &move_s);
  // move_s += Arc(this, Gd(new EVENTroom6d("wand_optitrack2")),    &SimpleInt::move);
  // move_s += Arc(this, Gd(new EVENTbtn   ("wanda_but_yellow")), &SimpleInt::up, STATEstart);


  // EVENTmgr::add_handler(new FSA(&_entry));

  activate_wand = 0;
  
  _control = c; // set the pointer to the control space
  _app = t; 

}

// void
// SimpleInt::idle(cEVENTroom6dptr &e, STATE *&)
// {
//   _cur = MathTranslate::instance()->ROOM_TO_WORLD() * e->cur();
// }

// void
// SimpleInt::down(cEVENTbtnptr &e, STATE *&)
// {
//   cerr << "Yellow Down pressed..." << endl;

//   activate_wand = 1;
// }

// void
// SimpleInt::toggle_control(cEVENTbtnptr &e, STATE *&)
// {
//   cerr << "Blue Down pressed..." << endl;
//   if (_control)
//     _control->toggle_visibility();
  
// }

// void
// SimpleInt::toggle_drawn_object(cEVENTbtnptr &e, STATE *&)
// {
//   cerr << "Red Down pressed..." << endl;
//   if (_app)
//     _app->toggle_drawmode();
  
// }



// void
// SimpleInt::move(cEVENTroom6dptr &evt, STATE *&)
// {
//   _cur = evt->cur();
  
//   Wtransf xf       = MathTranslate::instance()->WORLD_TO_ROOM() * _cur;
//   //  Wtransf xf = MathTranslate::instance()->ROOM_TO_WORLD() * _cur;
//   Wvec    wand_dir = xf * Wvec(0,0,1);
  
//   wand_begin = xf.origin();
//   wand_end = wand_begin + wand_dir;
  
//   if ((activate_wand)&&(_control->getVisibility())) { // control space needs to be updated
//     assert(_control);
//     _control->do_intersection(wand_begin, wand_end);
//   }

// }

// void
// SimpleInt::up  (cEVENTbtnptr &e, STATE *&)
// {
//   cerr << "Button released..." << endl;
//   activate_wand = 0;
// }

//draw a laser pointer from the wand
void 
SimpleInt::drawWand()
{

  if (activate_wand) {
    
    glMatrixMode(GL_MODELVIEW);    
    glPushMatrix();
    //glMultMatrixd(MathTranslate::instance()->ROOM_TO_WORLD().matrix());
    std::cerr << "SimpleInt.cpp: VRG3D version of glMultMatrixd(MathTranslate::instance()->ROOM_TO_WORLD().matrix()) not implemented.." << std::endl;

    glLineWidth(10.0);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(wand_begin[0],wand_begin[1],wand_begin[2]);
    glVertex3f(wand_end[0],wand_end[1],wand_end[2]);
    glEnd();    
    glPopMatrix(); 
    
    draw_text();
  }  
}


void SimpleInt::draw_text() 
{
  std::cerr << "SimpleInt.cpp::draw_text() not implemented" << std::endl;

#if 0
  char wall_text[128];
  sprintf(wall_text, "begin=(%4.2f,%4.2f,%4.2f) end=(%4.2f,%4.2f,%4.2f)", 
          wand_begin[0], wand_begin[1], wand_begin[2],
          wand_end[0], wand_end[1], wand_end[2]);
  
  Wtransf myMat = Wtransf::align(Wpt(0,0,0),Wvec(1,0,0),Wvec(0,1,0),
                                 Wpt(0,0,0),Wvec(1,0,0),Wvec(0,-1,0))*
    Wtransf::scaling(Wvec(0.08,0.08,0.08));
  
  glPushMatrix();
  //  glMultMatrixd((Wtransf::translation(Wvec(-2.3,-1.9,0)) *
  //                  myMat).matrix());
  glMultMatrixd((Wtransf::translation(Wvec(-3.5,-3.6,4.0)) *
                 myMat).matrix());
  
  FONTMGR::render(wall_text, 0.0,0.0,0.0);
  glPopMatrix();
#endif
}

