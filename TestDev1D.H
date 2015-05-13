
// This is a very simple Glue interactor to test a 1D device like the
// ICubeX system.


#ifndef TESTDEV1D_H
#define TESTDEV1D_H

// gluebase includes
#define OUTSIDE_GLUE_CORE
#include <fsa/fsa.H>
#include <dev/dev1d.H>
#include <mlib/points.H>


class TestDev1D : public Interactor<TestDev1D>
{
public:
  
  TestDev1D(str_ptr devName) : Interactor<TestDev1D>("TestDev1D") {
    _devName = devName;
    EVENT1dptr testevent = new EVENT1d(_devName);
    _entry += Arc(this, Gd(testevent), &TestDev1D::change1D);
    EVENTmgr::add_handler(new FSA(&_entry));
  }

  virtual ~TestDev1D() {}

  void change1D(cEVENT1dptr &evt, STATE* &next) {
    cout << "1D event (" << _devName << "): " << evt->cur() << endl;
  }

protected:

  str_ptr _devName;

};

#endif
