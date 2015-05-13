
// This is a very simple Glue interactor to test a 2D device like a
// joystick.


#ifndef TESTDEV2D_H
#define TESTDEV2D_H

// gluebase includes
#define OUTSIDE_GLUE_CORE
#include <fsa/fsa.H>
#include <dev/dev1d.H>
#include <mlib/points.H>

#include <DrawMgr.H>
#include <StatusBar.H>

class TestDev2D : public Interactor<TestDev2D>
{
public:
  
  TestDev2D(str_ptr devName, cXYpt screenLoc) : 
    Interactor<TestDev2D>("TestDev2D") {
    _devName = devName;
    EVENT2dptr testevent = new EVENT2d(_devName);
    _entry += Arc(this, Gd(testevent), &TestDev2D::change2D);
    EVENTmgr::add_handler(new FSA(&_entry));

    _statusBar = new StatusBar(screenLoc,false);
    _statusBar->setMessage(_devName + str_ptr(": (,)"));
  }

  virtual ~TestDev2D() {}

  void change2D(cEVENT2dptr &evt, STATE* &next) {
    char s[100];
    sprintf(s,"%s: (%1.2f,%1.2f)",**_devName,(float)evt->cur()[0],
	    (float)evt->cur()[1]);
    _statusBar->setMessage(str_ptr(s));
  }

protected:

  str_ptr _devName;
  StatusBar *_statusBar;

};

#endif
