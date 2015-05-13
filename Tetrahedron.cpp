
#include "Tetrahedron.h"
//#include "WorldTranslate.h"

#include <GL/glut.h>

Tetrahedron::Tetrahedron() {
  
  initialize_coordinates();
  world_offset = Vector3(0,0,0);
  intersection_point = Vector3(0,0,0);
  _u = new Utility();

}

Tetrahedron::~Tetrahedron() {
  if (_u)
    delete _u;
}

// give x,y,z values to the tetrahedron geometry
void Tetrahedron::initialize_coordinates() 
{
  float xoffset = 0.0; 
  float yoffset = 0.0; 

  tetra_height = 0.4446*2;

  //
  //
  //                   top
  //                    /\
  //                   /  \  <-- Base
  //                  /    \
  //                 /      \
  //           left ---------- right
  //
  //                   tip is at the top of tetrahedron
  
  float topx,topy,rightx,righty,leftx,lefty;
   
  topx   = xoffset + 0;
  leftx  = xoffset - 0.25*2;
  rightx = xoffset + 0.25*2;

  topy   =  yoffset + 0.2887*2;
  lefty  =  yoffset - 0.14434*2;
  righty =  yoffset - 0.14434*2;
  
  // Cave convention is 
  //
  //            / Z
  //           /
  //          O---------->X
  //          |
  //          |
  //          |
  //          |
  //          V  Y


  //  left   = Vector3(leftx,   -lefty,    0);
  //  right  = Vector3(rightx,  -righty,   0);
  //  top    = Vector3(topx,    -topy,     0);

  //  origin = Vector3(xoffset, -yoffset,  0);
  //  tip    = Vector3(origin[0], origin[1], tetra_height);

  left   = Vector3(leftx,   0, -lefty);
  right  = Vector3(rightx,  0, -righty);
  top    = Vector3(topx,    0, -topy);
  
  origin = Vector3(xoffset,   0,            yoffset);
  tip    = Vector3(origin[0], -tetra_height, origin[2]);

  center = Vector3(origin[0], -tetra_height/2.0, origin[2]);
  
  last_abc = Vector3(0,0,0);
  last_intersection_point = Vector3(0,0,0);

}


void Tetrahedron::draw() 
{
  Vector3 v0 = top;//   + Vector3(world_offset);
  Vector3 v1 = left;//  + Vector3(world_offset);
  Vector3 v2 = right;// + Vector3(world_offset);
  Vector3 v3 = tip;//   + Vector3(world_offset);
  
  //  glEnable(GL_BLEND);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  
  //  glMultMatrixd(MathTranslate::instance()->ROOM_TO_WORLD().matrix());

#if 0
  glBegin(GL_TRIANGLES);
  glColor4f(1.0,0.0,0.0,0.9f); // red face = (left, top, right)
  glVertex3f(v1[0],v1[1],v1[2]);
  glVertex3f(v0[0],v0[1],v0[2]);
  glVertex3f(v2[0],v2[1],v2[2]);
  
  glColor4f(0.0,1.0,0.0,0.9f); // green face = (left, right, tip)
  glVertex3f(v1[0],v1[1],v1[2]);
  glVertex3f(v2[0],v2[1],v2[2]);
  glVertex3f(v3[0],v3[1],v3[2]);
   
  glColor4f(1.0,1.0,1.0,0.9f); // white face = (tip, right, top)
  glVertex3f(v3[0],v3[1],v3[2]);
  glVertex3f(v2[0],v2[1],v2[2]);
  glVertex3f(v0[0],v0[1],v0[2]);
  
  glColor4f(0.0,0.0,1.0,0.9f); // blue face = (tip, top, left)
  glVertex3f(v3[0],v3[1],v3[2]);
  glVertex3f(v0[0],v0[1],v0[2]);
  glVertex3f(v1[0],v1[1],v1[2]);
  glEnd();
  
#else

  glPointSize(10.0);
  glBegin(GL_POINTS);
  glColor3f(1,1,1);
  glVertex3f(v0[0],v0[1],v0[2]);
  glVertex3f(v1[0],v1[1],v1[2]);
  glVertex3f(v2[0],v2[1],v2[2]);
  glVertex3f(v3[0],v3[1],v3[2]);
  glEnd();

  glLineWidth(7.0);
  glBegin(GL_LINES);
  glColor3f(1,0,0); // red line tip, left
  glVertex3f(v3[0],v3[1],v3[2]);
  glVertex3f(v1[0],v1[1],v1[2]);

  glColor3f(0,0,1); // blue line tip right
  glVertex3f(v3[0],v3[1],v3[2]);
  glVertex3f(v2[0],v2[1],v2[2]);

  glColor3f(0,1,0); // green line tip top
  glVertex3f(v3[0],v3[1],v3[2]);
  glVertex3f(v0[0],v0[1],v0[2]);

  glColor3f(1,0,1); // cyan line top left
  glVertex3f(v0[0],v0[1],v0[2]);
  glVertex3f(v1[0],v1[1],v1[2]);

  glColor3f(1,1,0); // yellow line top right 
  glVertex3f(v0[0],v0[1],v0[2]);
  glVertex3f(v2[0],v2[1],v2[2]);

  glColor3f(0,1,1); // pink? line right left
  glVertex3f(v2[0],v2[1],v2[2]);
  glVertex3f(v1[0],v1[1],v1[2]);
  
  glEnd();
  
  glColor3f(1,1,1);
  glPointSize(1.0);
  glLineWidth(1.0);
#endif


  /*
    glColor3f(1,1,0);
    glBegin(GL_LINES);
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(intersection_point[0], intersection_point[1], intersection_point[2]);
    glEnd();
    
    // draw a sphere at the wand-tetrahedron intersection point
    //  glColor3f(intersection_point_color[0],
    //            intersection_point_color[1],
    //            intersection_point_color[2]);
  
    glColor3f(1,1,0);
    glTranslatef(last_intersection_point[0], 
    last_intersection_point[1], 
    last_intersection_point[2]);
    glutWireSphere(0.1,5,5);
    glTranslatef(-last_intersection_point[0],
    -last_intersection_point[1],
    -last_intersection_point[2]);
  */
  
  glColor3f(1,1,1);
  Vector3 pt;
  float aa = last_abc[0];
  float bb = last_abc[1];
  float cc = last_abc[2];
  float dd = 1 - (aa+bb+cc);
  
  pt[0] = aa*right[0] + bb*tip[0] + cc*left[0] + dd*top[0];
  pt[1] = aa*right[1] + bb*tip[1] + cc*left[1] + dd*top[1];
  pt[2] = aa*right[2] + bb*tip[2] + cc*left[2] + dd*top[2];
  
  glTranslatef(pt[0],pt[1],pt[2]);
  glutWireSphere(0.1,15,15);
  glutSolidSphere(0.03,20,20);

  /*
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis red
  glColor3f(0,1,0);
  glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis green
  glColor3f(0,0,1);
  glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis blue
  glEnd();
  */

  glPopMatrix();
  //  glDisable(GL_BLEND);
  
}

bool Tetrahedron::intersect(Vector3 start, Vector3 end, Vector3* abc_result) 
{
#if 1
  return false;
#else
  //  cout<<"Tetrahedron::intersect" << endl;
  
  assert(abc_result);
  
  //  *abc_result = Vector3(0.0,0.0,0.0);
  
  // for its own draw routine..
  
  Vector3 tend = MathTranslate::instance()->ROOM_TO_WORLD() * end;
  //  intersection_point = Vector3(0,0,0);

  Vector3 io_result;

  int result = inside_outside_test(tend, 0, &io_result);
  
  //cout<<"\t\t result of inside_outside_test is " << result << endl;

  if (0==result) intersection_point_color = Vector3(1,1,1); // on surface white
  else if (1==result) intersection_point_color = Vector3(1,1,0); // inside yellow
  else if (2==result) intersection_point_color = Vector3(0,0,0); // outside black

  Vector3 projected_point;
  Vector3 dirn;
  Vector3 new_pt, t_result;
  int rresult;
  
  switch(result) {
  case 0: // on surface
    //    cout<<"\t\t\t case0" << endl;
    projected_point = tend;
    break;
    
  case 1: // inside tetra
    dirn = tend - center;
    new_pt = center + 5*dirn;
    //    cout<<"\t\t\t case1" << endl;
    if (line_intersect(center, new_pt, t_result)) {
      projected_point = t_result;
    }
    else {
      projected_point = tend;
    }
    rresult = inside_outside_test(projected_point, 1, &io_result);
    break;

  case 2: // outside tetra
    //    cout<<"\t\t\t case2" << endl;
    if (line_intersect(center, tend, t_result)) {
      projected_point = t_result;
    }
    else {
      projected_point = tend;
    }
    rresult = inside_outside_test(projected_point, 1, &io_result);
    break;
    

  default:
    cout << "Tetrahedron intersect invalid result" << endl;
    assert(false); // should never happen...
    break;
  }
  
  // at the end of this we want an a,b,c result abc_result
  // and a x,y,z result
  float sum = 0.0;
  sum = io_result[0]+io_result[1]+io_result[2];
  if ((sum>1.0)||(sum<0)) {
    cout<< "WRONG Sum is " << sum << endl;
    cout<< "a b c " << io_result[0] << io_result[1] << io_result[2] << endl;
  }
  
  
  double MIN_EPSILON = 1e-8;
  double MAX_EPSILON = 0.3;//0.35
  
  double distance = (io_result[0]-last_abc[0])*(io_result[0]-last_abc[0]) 
    + (io_result[1]-last_abc[1])*(io_result[1]-last_abc[1]) 
    + (io_result[2]-last_abc[2])*(io_result[2]-last_abc[2]);
  
  distance = sqrt(distance);
  // hack the MIN_EPSILON
  if ((distance>-MIN_EPSILON) && (distance<MAX_EPSILON)) { //update
    intersection_point = projected_point;
    
    abc_result[0] = io_result; // this has abc values in it
    
    last_abc = io_result;
    last_intersection_point = intersection_point;
    
  }
  else {   
    abc_result[0] = last_abc;
    intersection_point = last_intersection_point;
  }
  return true;
#endif
}


// function returns
//     0 if P is on the surface
//     1 if P is inside tetrahedron
//     2 if P is outside tetrahedron

// project will force the point P to get projected onto the surface of tetrahedron
// abc_result is set ONLY if point is on the surface

int Tetrahedron::inside_outside_test(Vector3 P, int project, Vector3* get_abc_result) 
{

  assert(get_abc_result);

  float a,b,c,d;
  a=b=c=d=0;
  float D0, D1, D2, D3, D4;
  Vector3 P1, P2, P3, P4;
  
  P1 = top;
  P2 = left;
  P3 = right;
  P4 = tip;

  // P1 = top, P2 = left, P3 = right, P4 = tip
  // P = point
  
  D0 = _u->determinant(P1, P2, P3, P4);
  D1 = _u->determinant(P,  P2, P3, P4);
  D2 = _u->determinant(P1, P,  P3, P4);
  D3 = _u->determinant(P1, P2, P,  P4);
  D4 = _u->determinant(P1, P2, P3, P );
  
  //  printf("D's are %f, %f, %f, %f, %f \n", D0, D1, D2, D3, D4);

  // If one of the D's is 0 then point is on the surface.. we can use this case... 
  if ( (project==1) || (_u->one_zero(D1, D2, D3, D4)) ) {  // just get the barycentric co-ords....  
    
    if (_u->is_zero(D1)) { // P lies on face  P2, P3, P4 :: left, right, tip
      c = D2/D0;
      a = D3/D0;
      b = D4/D0;
      d = 1 - (a+b+c);
    }
    
    if (_u->is_zero(D2)) { // P lies on face P1, P3, P4 :: top, tip, right
      a = D3/D0;
      d = D1/D0;
      b = D4/D0;
      c = 1 - (a+b+d);
    } 
    
    if (_u->is_zero(D3)) { // P lies on face P1, P2, P4 :: top, tip, left
      b = D4/D0;
      d = D1/D0;
      c = D2/D0;
      a = 1 - (b+c+d);
    }
    
    if (_u->is_zero(D4)) { // P lies on face P1, P2, P3 :: top, left, right
      a = D3/D0;
      d = D1/D0;
      c = D2/D0;
      b = 1 - (a+c+d);
    }
    
    //cout<<"Tetrahedron:: inside_outside returning" << a << "," << b << "," << c << endl;
    get_abc_result[0] = Vector3(a,b,c);

    return 0;
  }
  
  else { // we are still trying to find out if point is inside or outside tetra..
    
    if (_u->same_sign(D0, D1, D2, D3, D4)) 
      { return 1; } // inside tetra... 
    else 
      { return 2; } // outside tetra...
  }
  
}


// function returns 
// 1 if line specified by endpoints pt1 and pt2 intersects
//   the tetrahedron, intersection result is provided in "result"
// 0 if there is no intersection
//
int Tetrahedron::line_intersect(Vector3 pt1, Vector3 pt2, Vector3& result)
{
  Vector3 tmp_pt = Vector3(0,0,0);
  //  result = Vector3(0,0,0);
  
  Vector3 A, B, C;
  Vector3 AB, CA, normal, N;
  Vector3 AC, BC, Vline, CP;
  Vector3 centroid;
  Vector3 line_line_result;
  
  float t, t1, t2, t3;
  int min_t = -1;
  float a_area, b_area, c_area, t_area, total;
  
  // represent Line by pt1 + t (pt1 - pt2)
  //                   pt1 + t Vline;

  Vline = (pt1 - pt2);
  
  // cycle through the 4 planes....
  for (int i = 0; i < 4; i++) {   

    // Set the planes.... 
    switch(i) {
      // important : order of faces is important........... right now anti-clockwise
    case 0: 
      A = top;  // WTp3_copy(top,  A);
      B = left; // WTp3_copy(left, B);
      C = right;//WTp3_copy(right,C);     
      break;

    case 1:
      A = tip;  // WTp3_copy(tip,  A);
      B = right;// WTp3_copy(right, B);
      C = left; // WTp3_copy(left,C);
      break;

    case 2 :
      A = tip; // WTp3_copy(tip,  A);
      B = left;// WTp3_copy(left, B);
      C = top; // WTp3_copy(top,C);
      break;

    case 3:
      A = tip;  //WTp3_copy(tip,  A);
      B = top;  //WTp3_copy(top, B);
      C = right;//WTp3_copy(right,C);
      break;

    }

    // intersect line with plane
    AC = A-C;//WTp3_subtract(A, C, AC);
    BC = B-C;//WTp3_subtract(B, C, BC);
    //cross = cross(AC,BC);//WTp3_cross(AC, BC, cross);
    //WTp3_norm(cross);
    //    WTp3_copy(cross, N);
    
    N = cross(Vector3(AC),Vector3(BC));
//    N = N.normalize();
    N = normalize(N);
    
    Vline = -1*(N);//    WTp3_set(Vline, -N[X], -N[Y], -N[Z]);

    CP = (C-pt2); //WTp3_subtract(C, pt2, CP); 
//    t = (N*CP) / (N*Vline);    //t = WTp3_dot(N, CP) / WTp3_dot(N, Vline) ;
    t = (N.dot(CP)) / (Vline.dot(N));    //t = WTp3_dot(N, CP) / WTp3_dot(N, Vline) ;
    
    // check if t is within valid line
    
    //    if ((t>=0) && (t<=1)) {
      
    if ((t>=0)) {
      //      // if so calculate the point...
      //tmp_pt = Vector3(Vline[0],Vline[1],Vline[2]);    // WTp3_copy(Vline, tmp_pt);
      //tmp_pt = t*tmp_pt; // WTp3_mults(tmp_pt, t);
      
      tmp_pt = pt2 + t*Vline; 
      //WTp3_add(pt2, tmp_pt, tmp_pt);      
      
      // check if point is within triangle    
      t_area = _u->get_3DTriangle_Area(A, B, C);
      a_area = _u->get_3DTriangle_Area(B, C, tmp_pt);
      b_area = _u->get_3DTriangle_Area(A, C, tmp_pt);
      c_area = _u->get_3DTriangle_Area(A, B, tmp_pt);
      total = a_area + b_area + c_area;
      
      if (fabs(total - t_area)< 0.0005 * t_area) { // we are all set........
	result = tmp_pt; //WTp3_copy(tmp_pt, intersect_tetra_result);
        //        printf("Result of successful tetra intersection is %f,%f,%f\n",
        //               intersect_tetra_result[X],intersect_tetra_result[Y],intersect_tetra_result[Z]);
	return 1;
      }   
      
      else { // point is outside triangle........need to project it onto an edge..
        //        printf("Point is outside triangle....\n");
        // WTp3_set(centroid, (A[X]+B[X]+C[X])/3,(A[Y]+B[Y]+C[Y])/3, (A[Z]+B[Z]+C[Z])/3);
        // important : we are changing the centroid to something else...
        
        AB = B-A; //WTp3_subtract(B, A, AB);
        CA = A-C; //WTp3_subtract(A, C, CA);
        BC = C-B; //WTp3_subtract(C, B, BC);
        N = cross(BC, CA); //WTp3_cross(BC, CA, N);
        
        normal = cross(N,AB); //WTp3_cross(N, AB, normal);
        
        centroid = tmp_pt + 2*normal;
        
        if (_u->line_line_intersect(A,B,centroid,tmp_pt, line_line_result)) {
          //          draw_line(centroid,tmp_pt,1);
          //          draw_sphere(line_line_result);
          //          WTp3_copy(line_line_result, intersect_tetra_result);
          result = line_line_result;
          return 1;
        }
        
        normal = cross(N,BC);//WTp3_cross(N, BC, normal);
        
        centroid = tmp_pt + 2*normal;
        
        if (_u->line_line_intersect(B,C,centroid,tmp_pt, line_line_result)) {
          //          draw_line(centroid,tmp_pt,1);
          //          draw_sphere(line_line_result);
          //          WTp3_copy(line_line_result, intersect_tetra_result);
          result = line_line_result;
          return 1;
        }

        normal = cross(N,CA);//WTp3_cross(N, CA, normal);
        
        //        centroid[X] = tmp_pt[X] + 2 * normal[X];
        //        centroid[Y] = tmp_pt[Y] + 2 * normal[Y];
        //        centroid[Z] = tmp_pt[Z] + 2 * normal[Z];
        centroid = tmp_pt + 2*normal;
        
        if (_u->line_line_intersect(A,C,centroid,tmp_pt, line_line_result)) {
          //          draw_line(centroid,tmp_pt,1);
          //          draw_sphere(line_line_result);
          //          WTp3_copy(line_line_result, intersect_tetra_result);
          result = line_line_result;
          return 1;
        }

        //        WTp3_copy(line_line_result, intersect_tetra_result);
        result = line_line_result;
        return 1;
        
      }
      
    } // if t is valid.. 
    
  } // for planes.... 
  
  return 0;
} 
