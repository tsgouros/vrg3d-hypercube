
#ifndef _HYPERCUBE_H
#define _HYPERCUBE_H

//#include "ISMesh.H"
#include <vrg3d/VRG3D.h>
#include <vector>

using namespace G3D;

class Hypercube {

private:
  
  int _slices, _stacks; //how many subdivisions for the geometry

  double _a, _b, _c; // the 4D co-ordinates on the tetrahedron; d = 1 - (a+b+c)

  double _colorArray[16][3]; // fixed set of colors for slices..

  void initialize_colors();
  
  void calculate_geometry(); // this will calculate the geometry for _a,_b,_c

  std::vector<Vector3> _face_vertices; 
  std::vector<Vector3> _line_vertices;
  std::vector<Vector3> _normals;

  std::vector<Vector3> _line_colors;
  std::vector<Vector3> _face_colors;

  int first; // for first time flag
public:
  
  Hypercube();
  ~Hypercube() {};
  
  void update_geometry(double a, double b, double c);

  void manual_increment(int code);

  void draw();

};


#endif
