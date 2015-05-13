
#ifndef _TETRA_H
#define _TETRA_H

//#include "ISMesh.H"
#include "Utility.H"

class Tetrahedron {

private:
  Wpt top, left, right, tip, origin;
  float tetra_height;
  Wpt center;

  Wpt world_offset;
  Wpt intersection_point;
  Wpt intersection_point_color;
  
  Wpt last_abc;
  Wpt last_intersection_point;

  void initialize_coordinates();

  int line_intersect(Wpt, Wpt, Wpt&);

  Utility *_u;


public:
  Tetrahedron();
  ~Tetrahedron();
  
  // abc_result has the a,b,c values for control space
  bool intersect(Wpt start, Wpt end, Wpt* abc_result);
  
  // check if point is inside or outside and return abc value
  int inside_outside_test(Wpt P, int project, Wpt* abc_result);
  
  void draw();

};

#endif
