
// This is a very simple Glue interactor to test a button device like the
// keyboard, mouse buttons, vr wand buttons, etc..


#ifndef TESTDEVBTN_H
#define TESTDEVBTN_H

// gluebase includes
#define OUTSIDE_GLUE_CORE
#include <fsa/fsa.H>
#include <dev/buttons.H>
#include <mlib/points.H>

#include <DrawObj.H>
#include <DrawMgr.H>
#include <StatusBar.H>

#include "Torus.H"

class TestDevBtn : public Interactor<TestDevBtn>
{
public:
  
  TestDevBtn(str_ptr devName, cXYpt screenLoc, Torus* torus) : 
    Interactor<TestDevBtn>("TestDevBtn") {
    _devName = devName;
    EVENTbtnptr btndown = new EVENTbtn(_devName,true);
    EVENTbtnptr btnup   = new EVENTbtn(_devName,false);
    _entry += Arc(this, Gd(btndown), &TestDevBtn::btnDown);
    _entry += Arc(this, Gd(btnup),   &TestDevBtn::btnUp);
    EVENTmgr::add_handler(new FSA(&_entry));

    _statusBar = new StatusBar(screenLoc,false);
    _statusBar->setMessage(_devName);

    _torus = torus;
  }

  virtual ~TestDevBtn() {}

  void btnDown(cEVENTbtnptr &evt, STATE* &next) {
    str_ptr s = _devName + str_ptr(": DOWN");
    cout << s << endl;
    _statusBar->setMessage(s);
    
    if (!strcmp(**_devName,"wanda_but_blue"))
      _torus->manual_increment(1);
    else if (!strcmp(**_devName,"wanda_but_yellow"))
      _torus->manual_increment(2);
    else if (!strcmp(**_devName,"wanda_but_red"))
      _torus->manual_increment(3);


  }
  
  void btnUp(cEVENTbtnptr &evt, STATE* &next) {
    str_ptr s = _devName;
    cout << s << endl;
    _statusBar->setMessage(s);
  }
  
protected:

  str_ptr _devName;
  StatusBar *_statusBar;
  
  Torus *_torus;
  
};

#endif
