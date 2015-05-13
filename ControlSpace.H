
#ifndef _CONTROL_H
#define _CONTROL_H

#include "ISMesh.H"

//#include "Torus.H"
//#include "Hypercube.H"
//#include "Hopf.H"

#include "Tetrahedron.H"

class ControlSpace {

private:

  Wpt global_pos;

  double _a,_b,_c; // 4D co-ordinates of the control space; internal

  //  Wpt line_intersect(Wpt start, Wpt end);
  
  //  Torus *_torus;
  //  Hypercube *_hypercube;
  //  Hopf *_hopf;

  Tetrahedron *_tetra;

  bool show_control_space;

public:
  
  //  ControlSpace(Torus *t, Hypercube *h, Hopf* hp);
  ControlSpace();
  ~ControlSpace();

  // get the 4d co-ordinates from the control space
  // pass by reference
  void get_abc(double& a, double& b, double& c);
   
  // wand will provide a World space line segment
  // use this to set the internal a,b,c values
  void do_intersection(Wpt start, Wpt end);
  
  // draw the control space tetrahedron 
  // AND a sphere corresponding to a,b,c
  void draw();

  bool getVisibility();
  void toggle_visibility();

};

#endif
