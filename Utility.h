
#ifndef _UTILITY_H
#define _UTILITY_H

//#include "ISMesh.H"
#include <vrg3d/VRG3D.h>

using namespace G3D;

class Utility {
 
private:

public:
  Utility();
  ~Utility(){};

  float determinant(Vector3 A, Vector3 B, Vector3 C, Vector3 D);
  
  float get_3DTriangle_Area(Vector3, Vector3, Vector3);

  bool line_line_intersect(Vector3, Vector3, Vector3, Vector3, Vector3 &);

  bool same_sign(float, float, float, float, float);
  bool one_zero(float, float, float, float);

  bool delta(float, float);
  bool is_zero(float);
};

#endif
