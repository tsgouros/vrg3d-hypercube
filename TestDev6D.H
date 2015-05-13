
// This is a very simple Glue interactor to test a 6D device like a
// tracker.


#ifndef TESTDEV6D_H
#define TESTDEV6D_H

// gluebase includes
#define OUTSIDE_GLUE_CORE
#include <fsa/fsa.H>
#include <dev/dev1d.H>
#include <mlib/points.H>

#include <DrawMgr.H>
#include <DrawObj.H>
#include <FontMgr.H>
#include "Arrow.H"


class TestDev6D : public Interactor<TestDev6D>, public DrawObj
{
public:
  
  TestDev6D(str_ptr devName) : Interactor<TestDev6D>("TestDev6D"),
    DrawObj("Axis_" + devName) {
    _devName = devName;
    EVENTroom6dptr testevent = new EVENTroom6d(_devName);
    _entry += Arc(this, Gd(testevent), &TestDev6D::change6D);
    EVENTmgr::add_handler(new FSA(&_entry));

    _arrows += new Arrow(Wpt(), Color::red);
    _arrows += new Arrow(Wpt(), Color::green);
    _arrows += new Arrow(Wpt(), Color::blue);
    for (int i=0;i<_arrows.num();i++) {
      DRAWMGR::registerObj(_arrows[i]);
      _arrows[i]->setRoomObj(1);
    }

    _xforms += Wtransf::translation(Wvec(0.75,0,0)) * 
      Wtransf::rotation(Wvec(0,1,0),M_PI/2.0);
    _xforms += Wtransf::translation(Wvec(0,0.75,0)) * 
      Wtransf(Wvec(1,0,0), Wvec(0,0,-1), Wvec(0,1,0));
    _xforms += Wtransf::translation(Wvec(0,0,0.75));

    cout << "Tracking 6DOF device: " << _devName << endl;

    DRAWMGR::registerObj(this);
  }

  virtual ~TestDev6D() {}

  void change6D(cEVENTroom6dptr &evt, STATE* &next) {
    //    cout << "6D event (" << _devName << "): " << evt->cur() << endl;
    for (int i=0;i<_arrows.num();i++) {
      _arrows[i]->setXform(evt->cur() * _xforms[i]);
    }
    setXform(evt->cur());
  }

  
  void draw() {  
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixd((Wtransf::translation(Wvec(0,-0.3,0)) *
		   Wtransf::align(Wpt(0,0,0),Wvec(1,0,0),Wvec(0,1,0),
				  Wpt(0,0,0),Wvec(1,0,0),Wvec(0,-1,0))*
		   Wtransf::scaling(Wvec(0.05,0.05,0.05))).matrix());

    glColor3f(1,1,1);
    FONTMGR::render(**_devName,0,0,0,0);
    glPopMatrix();    
  }


protected:

  str_ptr _devName;

  ARRAY<Arrow*>  _arrows;
  ARRAY<Wtransf> _xforms;

};

#endif
