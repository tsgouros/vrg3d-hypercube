
#include "ControlSpace.h"
#include "assert.h"

//ControlSpace::ControlSpace(Torus *t, Hypercube *h, Hopf *hf) 
ControlSpace::ControlSpace()
{
  //  _torus = t;
  //  _hypercube = h;
  //  _hopf = hf;

  _a = 0.0;
  _b = 0.0;
  _c = 0.0;

  _tetra = new Tetrahedron();
  
  show_control_space = true;

}

ControlSpace::~ControlSpace() 
{
  if (_tetra)
    delete _tetra;
}

// get the 4d co-ordinates from the control space
void ControlSpace::get_abc(double& oa, double& ob, double& oc) 
{
  //  assert(_a+_b+_c<=1.0);

  oa = _a;
  ob = _b;
  oc = _c;
}

// Wand provides the world space line and uses that to set the internal
// a,b,c values
void ControlSpace::do_intersection(Vector3 start, Vector3 end) 
{
  start.x -= _x;
  start.y -= _y;
  start.z -= _z;
  end.x -= _x;
  end.y -= _y;
  end.z -= _z;


  Vector3 result;
  Vector3 pos;

  //cout<<"ControlSpace::do_intersection"<<start << "::" << end << endl;
  assert(_tetra);
  if (_tetra->intersect(start, end, &result)) {
    _a = result[0]; // get the result from tetrahedron
    _b = result[1];
    _c = result[2];
    //    assert(_a+_b+_c<=1.0);
    //    assert(_a+_b+_c>=0);
  }
  
}

// intersect line with the control space
//Wpt ControlSpace::line_intersect(Wpt start, Wpt end) 
//{
//  return Wpt(0,0,0);
//}

//draw the tetrahedral control space at a fixed offset from the user head position
void ControlSpace::draw() 
{
  glPushMatrix();
  glTranslatef(_x,_y,_z);

  if (show_control_space)
    _tetra->draw();

  glPopMatrix();
}

bool ControlSpace::getVisibility() 
{
  return show_control_space;
}

void ControlSpace::toggle_visibility() 
{
  show_control_space = !show_control_space;
}

void ControlSpace::set_position(double x, double y, double z)
{
  _x = x;
  _y = y;
  _z = z;
}

