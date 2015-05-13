
#ifndef _TETRA_H
#define _TETRA_H

//#include "ISMesh.H"
#include "Utility.h"

class Tetrahedron {

private:
  Vector3 top, left, right, tip, origin;
  float tetra_height;
  Vector3 center;

  Vector3 world_offset;
  Vector3 intersection_point;
  Vector3 intersection_point_color;
  
  Vector3 last_abc;
  Vector3 last_intersection_point;

  void initialize_coordinates();

  int line_intersect(Vector3, Vector3, Vector3&);

  Utility *_u;


public:
  Tetrahedron();
  ~Tetrahedron();
  
  // abc_result has the a,b,c values for control space
  bool intersect(Vector3 start, Vector3 end, Vector3* abc_result);
  
  // check if point is inside or outside and return abc value
  int inside_outside_test(Vector3 P, int project, Vector3* abc_result);
  
  void draw();

};

#endif
