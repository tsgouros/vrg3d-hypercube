
#include "Utility.h"

#define EPSILON 1e-8

Utility::Utility() {

}

float Utility::determinant(Vector3 A, Vector3 B, Vector3 C, Vector3 D) {
 float tmp1,tmp2,tmp3,tmp4;
 tmp1=tmp2=tmp3=tmp4=0;
 
 //  tmp1 =  a *( f*(k*p - o*l) - g*(j*p - l*n) + h*(j*o - n*k));
 //   tmp2 = -b *( e*(k*p - o*l) - g*(i*p - l*m) + h*(i*o - m*k));
 //   tmp3 =  c *( e*(j*p - n*l) - f*(i*p - l*m) + h*(i*n - m*j));  
 //   tmp4 = -d *( e*(j*o - n*k) - f*(i*o - k*m) + g*(i*n - m*j));
 
 tmp1 =  A[0] *( B[1]*(C[2]*1 - D[2]*1) - B[2]*(C[1]*1 - 1*D[1]) + 1*(C[1]*D[2] - D[1]*C[2]));
 
 tmp2 = -A[1] *( B[0]*(C[2]*1 - D[2]*1) - B[2]*(C[0]*1 - 1*D[0]) + 1*(C[0]*D[2] - D[0]*C[2]));
 
 tmp3 =  A[2] *( B[0]*(C[1]*1 - D[1]*1) - B[1]*(C[0]*1 - 1*D[0]) + 1*(C[0]*D[1] - D[0]*C[1]));
 
 tmp4 = -1 *( B[0]*(C[1]*D[2] - D[1]*C[2]) - B[1]*(C[0]*D[2] - C[2]*D[0]) + B[2]*(C[0]*D[1] - D[0]*C[1]));
 
 return (tmp1+tmp2+tmp3+tmp4);

}

bool Utility::same_sign(float a, float b, float c, float d, float e) {

  if ( (a>0) && (b>0) && (c>0) && (d>0) && (e>0) ) { return true; }
  if ( (a<0) && (b<0) && (c<0) && (d<0) && (e<0) ) { return true; }
  
  return false;
}

bool Utility::one_zero(float a, float b, float c, float d) {
  
  if ( (is_zero(a)) || (is_zero(b)) || (is_zero(c)) || (is_zero(d)) ) { return true; }
  else { return false; }
  
}

bool Utility::is_zero(float x) {

  if ((fabs(x) > -EPSILON) && (fabs(x) < EPSILON))
    return true;
  else 
    return false;
  
}

bool Utility::delta(float x, float y) {
  if (fabs(x-y)<EPSILON) 
    return true;
  else 
    return false;
  
}

float Utility::get_3DTriangle_Area(Vector3 A, Vector3 B, Vector3 C) {
  
  float result = 0;
  float a,b,c,s;
  
  a = (B-A).length(); // a = B.dist(C);//Wpt_distance(B,C);
  b = (A-C).length(); // A.dist(C);//Wpt_distance(A,C);
  c = (A-B).length(); // A.dist(B);//Wpt_distance(A,B);
  
  s = (a+b+c)/2;
  result = s * (s-a) * (s-b) * (s-c);
  
  if (result < 0) 
    { result = -result;} 
  if (delta(result ,0)) 
    { return 0;}
  
  result = sqrt(result);
  return result;
}

// Copying this code from Paul Bourke.........
// Know that lines are going to intersect.. ???

bool Utility::line_line_intersect(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3& line_line_result  ) {
  
  Vector3 p13,p43,p21;
  double d1343,d4321,d1321,d4343,d2121;
  double numer,denom;
  float mua,mub;

  p13[0] = p1[0] - p3[0];
  p13[1] = p1[1] - p3[1];
  p13[2] = p1[2] - p3[2];
  p43[0] = p4[0] - p3[0];
  p43[1] = p4[1] - p3[1];
  p43[2] = p4[2] - p3[2];

  //  if ((abs(p43[0])  < EPSILON) && (abs(p43[1])  < EPSILON) && (abs(p43[2])  < EPSILON)) return(FALSE);

  p21[0] = p2[0] - p1[0];
  p21[1] = p2[1] - p1[1];
  p21[2] = p2[2] - p1[2];
  
  //  if ( (abs(p21[0])  < EPSILON) && (abs(p21[1])  < EPSILON) && (abs(p21[2])  < EPSILON))  return(FALSE);
  
  d1343 = p13[0] * p43[0] + p13[1] * p43[1] + p13[2] * p43[2];
  d4321 = p43[0] * p21[0] + p43[1] * p21[1] + p43[2] * p21[2];
  d1321 = p13[0] * p21[0] + p13[1] * p21[1] + p13[2] * p21[2];
  d4343 = p43[0] * p43[0] + p43[1] * p43[1] + p43[2] * p43[2];
  d2121 = p21[0] * p21[0] + p21[1] * p21[1] + p21[2] * p21[2];
  
  denom = d2121 * d4343 - d4321 * d4321;
  //  if (abs(denom) < EPSILON)  return(FALSE);
  numer = d1343 * d4321 - d1321 * d4343;
  
  mua = numer / denom;
  float line_line_t = (d1343 + d4321 * (mua)) / d4343;
  
  if ( (line_line_t>=0) && (line_line_t<=1) && (mua>=0) && (mua<=1) ) {
    //    line_line_result[0] = p3[0] + line_line_t * p43[0];
    //    line_line_result[1] = p3[1] + line_line_t * p43[1];
    //    line_line_result[2] = p3[2] + line_line_t * p43[2];
    //Vector3 r = Vector3(p3 + line_line_t*Wvec(p43));
    Vector3 r = Vector3(p3 + line_line_t*Vector3(p43));
    line_line_result = r;
    
    return true;
  }

  return false;  
  
}
