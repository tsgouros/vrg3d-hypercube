#ifndef _NEWTOOLS_H_
#define _NEWTOOLS_H_

// gluebase includes
#define OUTSIDE_GLUE_CORE
#include <fsa/fsa.H>
#include <dev/buttons.H>
#include <mlib/points.H>

#include <ObjectInt.H>

#include "Torus.H"

#define cE cEVENTbtnptr
#define cE6 cEVENTroom6dptr
#define WAND_NAME CONFIGval("CAM_DMANIP_MOVE","wand_polhemus",0)


class ToolLeftButton : public Interactor<ToolLeftButton>
{
  
 protected:
	ToolSelect* _tool;
	DataMgr* _mgr;
    public:
	~ToolLeftButton(){}
	ToolLeftButton(Cstr_ptr &n, ToolSelect* tool, DataMgr* mgr) : Interactor<ToolLeftButton>("ToolLeftButton")
	{
	    _tool = tool;
	    _mgr = mgr;
	    str_ptr e = CONFIGval(n + "_button","",0);
	    _entry += Arc(this,Gd(new EVENTbtn(e,1)), &ToolLeftButton::down);
	    EVENTmgr::add_handler(new FSA(&_entry));
	}
	void down(cE &e, STATE *&s)
	{
          cout << "Left button pressed " << endl;
        }

}
