
#include "Torus.h"

//#include "WorldTranslate.H"

Torus::Torus() {
  
  _slices = 32;
  _stacks = 96;//24

  _a = 0.0;
  _b = 0.0;
  _c = 0.0;

  first = 1;

  initialize_colors();

  calculate_geometry();

}

void Torus::initialize_colors() {
  
  /*
    _colorArray[0][0] = 255; _colorArray[0][1] = 62;  _colorArray[0][2] = 150;
    _colorArray[1][0] = 255; _colorArray[1][1] = 255;  _colorArray[1][2] = 255;
    _colorArray[2][0] = 0;   _colorArray[2][1] = 0;   _colorArray[2][2] = 128;
    
    _colorArray[3][0] = 255;   _colorArray[3][1] = 255;   _colorArray[3][2] = 0;
    _colorArray[4][0] = 0;   _colorArray[4][1] = 100; _colorArray[4][2] = 0;
    _colorArray[5][0] = 102; _colorArray[5][1] = 205; _colorArray[5][2] = 0;
    
    _colorArray[6][0] = 154; _colorArray[6][1] = 205; _colorArray[6][2] = 50;
    _colorArray[7][0] = 255; _colorArray[7][1] = 215; _colorArray[7][2] = 0;
    _colorArray[8][0] = 255; _colorArray[8][1] = 165; _colorArray[8][2] = 0;
    
    _colorArray[9][0] = 255; _colorArray[9][1] = 99;  _colorArray[9][2] = 71;
    _colorArray[10][0] = 255; _colorArray[10][1] = 0;   _colorArray[10][2] = 0;
    _colorArray[11][0] = 205; _colorArray[11][1] = 38;  _colorArray[11][2] = 38;
  */

  /*  
  _colorArray[0][0] = 255; _colorArray[0][1] = 110;  _colorArray[0][2] = 180;
  _colorArray[2][0] = 255; _colorArray[2][1] = 255;  _colorArray[2][2] = 255;
  _colorArray[4][0] = 0;   _colorArray[3][1] = 0;   _colorArray[4][2] = 128;
  
  _colorArray[6][0] = 255;   _colorArray[6][1] = 255;   _colorArray[6][2] = 0;
  _colorArray[8][0] = 0;   _colorArray[8][1] = 100; _colorArray[8][2] = 0;
  _colorArray[10][0] = 102; _colorArray[10][1] = 205; _colorArray[10][2] = 0;
  
  _colorArray[12][0] = 154; _colorArray[12][1] = 205; _colorArray[12][2] = 50;
  _colorArray[14][0] = 255; _colorArray[14][1] = 215; _colorArray[14][2] = 0;
  _colorArray[16][0] = 255; _colorArray[16][1] = 165; _colorArray[16][2] = 0;
  
  _colorArray[18][0] = 255; _colorArray[18][1] = 99;  _colorArray[18][2] = 71;
  _colorArray[20][0] = 255; _colorArray[20][1] = 0;   _colorArray[20][2] = 0;
  _colorArray[22][0] = 205; _colorArray[22][1] = 38;  _colorArray[22][2] = 38;
  */
  
  // Colorscheme from PIC24.GIF, d/l from the web
  // yellow -> orange
  _colorArray[0][0] = 249/255.0; _colorArray[0][1] = 255/255.0;  _colorArray[0][2] = 90/255.0;
  _colorArray[1][0] = 249/255.0; _colorArray[1][1] = 217/255.0;  _colorArray[1][2] = 25/255.0;
  _colorArray[2][0] = 252/255.0;   _colorArray[2][1] = 152/255.0;   _colorArray[2][2] = 64/255.0;
  
  // red ->blue-pink
  _colorArray[3][0] = 252/255.0;   _colorArray[3][1] = 21/255.0;   _colorArray[3][2] = 47/255.0;
  _colorArray[4][0] = 250/255.0;   _colorArray[4][1] = 5/255.0; _colorArray[4][2] = 152/255.0;
  _colorArray[5][0] = 245/255.0; _colorArray[5][1] = 26/255.0; _colorArray[5][2] = 250/255.0;
  
  // violet->medium blue
  _colorArray[6][0] = 178/255.0; _colorArray[6][1] = 5/255.0; _colorArray[6][2] = 239/255.0;
  _colorArray[7][0] = 81/255.0; _colorArray[7][1] = 2/255.0; _colorArray[7][2] = 211/255.0;
  _colorArray[8][0] = 11/255.0; _colorArray[8][1] = 5/255.0; _colorArray[8][2] = 187/255.0;
  
  // dark blue ->greenish blue
  _colorArray[9][0] = 4/255.0; _colorArray[9][1] = 46/255.0;  _colorArray[9][2] = 156/255.0;
  _colorArray[10][0] = 4/255.0; _colorArray[10][1] = 136/255.0;   _colorArray[10][2] = 162/255.0;
  _colorArray[11][0] = 4/255.0; _colorArray[11][1] = 184/255.0;  _colorArray[11][2] = 167/255.0;
  
  // green -> yellow green
  _colorArray[12][0] = 4/255.0; _colorArray[12][1] = 216/255.0;  _colorArray[12][2] = 111/255.0;
  _colorArray[13][0] = 7/255.0; _colorArray[13][1] = 184/255.0;   _colorArray[13][2] = 25/255.0;
  _colorArray[14][0] = 48/255.0; _colorArray[14][1] = 232/255.0;  _colorArray[14][2] =  4/255.0;
  _colorArray[15][0] = 185/255.0; _colorArray[15][1] = 250/255.0;  _colorArray[15][2] =  12/255.0;

}


void Torus::manual_increment(int code) {
  switch (code) {
    
  case 1 : if ((_a+_b+_c)<1) _a = _a + 0.05;
    break;
    
  case 2:  if ((_a+_b+_c)<1) _b = _b + 0.05;
    break;
    
  case 3:  if ((_a+_b+_c)<1) _c = _c + 0.05;
    break;

  case 4 : if ((_a+_b+_c)>0) _a = _a - 0.05;
    break;
    
  case 5:  if ((_a+_b+_c)>0) _b = _b - 0.05;
    break;
    
  case 6:  if ((_a+_b+_c)>0) _c = _c - 0.05;
    break;

  }
  
  fprintf(stderr,"Values of a, b, c inside Torus::manual_increment are %f, %f, %f\n " , _a, _b, _c);

  calculate_geometry();

}

//given new values of a,b,c update the private variables..
void Torus::update_geometry(double a, double b, double c) {

  // shifter to Tetrahedron.C
  /*  double MIN_EPSILON = 1e-5;
  double MAX_EPSILON = 0.3;

  double distance = (a-_a)*(a-_a) + (b-_b)*(b-_b) + (c-_c)*(c-_c);
  distance = sqrt(distance);
  
  if ((distance>MIN_EPSILON) && (distance<MAX_EPSILON))
  */
  { // recalculate things only if distance is less then threshold (to precent small movements)
    // OR if distance is less than great change (flickering)
    _a = a;
    _b = b;
    _c = c;
    calculate_geometry();
  }
  
  
}

void Torus::calculate_geometry() {

  double theta, ntheta;
  double phi, nphi;
  
  double x,y,u,v;
  double nx, ny, nu, nv;

  Vector3 pt1, pt2, pt3;
  Vector3 norm1, norm2, ncross;

  double x1,x2,x3,x4;
  double y1,y2,y3,y4;
  double z1,z2,z3,z4;
  double den1,den2,den3,den4;
  
  double d,den;
  

  if (_vertices.size()>0)
    _vertices.clear();
  if (_normals.size()>0) 
    _normals.clear();
  if (_colors.size()>0)
    _colors.clear();


  d = 1 - (_a+_b+_c);
  den = sqrt(2) * sqrt(_a*_a + _b*_b + _c*_c + d*d);
  
  for (int j=0; j<_slices; j++) {
        
    phi =  ((2*M_PI* j  ) /_slices);
    nphi = ((2*M_PI*(j+1))/_slices);
    
    u = cos(phi);
    v = sin(phi);
    nu = cos(nphi);
    nv = sin(nphi);

    if (j%2==0) { // Planes....
      
      
      for (int i=0; i<_stacks; i++) { // # stacks = _par2 till _par2 for tip !! 
        
        int ci = (int) floor(((double)j)/2.0);
        theta =  ((2*M_PI* i)  / _stacks);
        ntheta =  (2*M_PI*(i+1)/ _stacks);

        x = cos(theta);
        y = sin(theta);
        nx = cos(ntheta);
        ny = sin(ntheta);

        x1  = - _b*x  + _a*y  - d*u  + _c*v ;
        x2  = - _b*nx + _a*ny - d*u  + _c*v ;
        x3  = - _b*nx + _a*ny - d*nu + _c*nv;
        x4  = - _b*x  + _a*y  - d*nu + _c*nv;
        
        y1  = - _c*x  + d*y  + _a*u  - _b*v ;    
        y2  = - _c*nx + d*ny + _a*u  - _b*v ;       
        y3  = - _c*nx + d*ny + _a*nu - _b*nv;    
        y4  = - _c*x  + d*y  + _a*nu - _b*nv;       
        
        
        z1  = - d*x  - _c*y  + _b*u  + _a*v ;
        z2  = - d*nx - _c*ny + _b*u  + _a*v ;
        z3  = - d*nx - _c*ny + _b*nu + _a*nv;
        z4  = - d*x  - _c*y  + _b*nu + _a*nv;

        den1 = (_a*x   + _b*y   + _c*u  + d*v  );
        den2 = (_a*nx  + _b*ny  + _c*u  + d*v  );
        den3 = (_a*nx  + _b*ny  + _c*nu + d*nv );
        den4 = (_a*x   + _b*y   + _c*nu + d*nv );

        // triangle ABD...............
        
        // Point D........
        pt3[1]= x4/(den - den4); 
        pt3[0]= y4/(den - den4);
        pt3[2]= z4/(den - den4);
        
        // Point A........
        pt1[1]= x1/(den - den1); 
        pt1[0]= y1/(den - den1);
        pt1[2]= z1/(den - den1);
        
        // Point B........
        pt2[1]= x2/(den - den2); 
        pt2[0]= y2/(den - den2);
        pt2[2]= z2/(den - den2);
        
        ncross = cross(pt2-pt1, pt3-pt1);
        
        _vertices.push_back(pt1);
        _vertices.push_back(pt3);
        _vertices.push_back(pt2);
        
        _normals.push_back(ncross);
        
        //_colors += Vector3(_colorArray[ci%11][0],_colorArray[ci%11][1],_colorArray[ci%11][2]);
        _colors.push_back(Vector3(_colorArray[ci][0],_colorArray[ci][1],_colorArray[ci][2]));
        
        // Finished with the first triangle..................
        
        // Triangle BCD ..............................    
        
        // Point C	
        pt2[1]= x3/(den - den3); 
        pt2[0]= y3/(den - den3);
        pt2[2]= z3/(den - den3); 
        
        // Point B
        pt1[1]= x2/(den - den2); 
        pt1[0]= y2/(den - den2);
        pt1[2]= z2/(den - den2);
        
        // Point D 
        pt3[1]= x4/(den - den4); 
        pt3[0]= y4/(den - den4);
        pt3[2]= z4/(den - den4);
        
        ncross = cross(pt2-pt1, pt3-pt1);
        
        _vertices.push_back(pt1);
        _vertices.push_back(pt3);
        _vertices.push_back(pt2);
        
        _normals.push_back(ncross);
        
        //_colors += Vector3(_colorArray[ci%11][0],_colorArray[ci%11][1],_colorArray[ci%11][2]);
        _colors.push_back(Vector3(_colorArray[ci][0],_colorArray[ci][1],_colorArray[ci][2]));
        // Finished with the second triangle..................	
      

      }//_stacks loop

    } // j%2 planes..

  }//_slices loop
  
  
}

void Torus::draw() {

  int numTriangles = _normals.size();
  assert(numTriangles == _colors.size());
  assert(numTriangles*3 == _vertices.size());

  glMatrixMode(GL_MODELVIEW);
  
  glPushMatrix();
  //  glMultMatrixd(MathTranslate::instance()->ROOM_TO_WORLD().invert().matrix());
  //glMultMatrixd(MathTranslate::instance()->WORLD_TO_ROOM().matrix());
  std::cerr << "Torus.cpp: VRG3D version of glMultMatrixd(MathTranslate::instance()->WORLD_TO_ROOM().matrix()) not implemented.." << std::endl;

  glBegin(GL_TRIANGLES);

  int j = 0;

  for (int i=0; i<numTriangles; i++) {
    glColor3f(_colors[i][0],_colors[i][1],_colors[i][2]);
    glNormal3f(_normals[i][0],_normals[i][1],_normals[i][2]);
    
    glVertex3f(_vertices[j][0], _vertices[j][1], _vertices[j][2]);
    glVertex3f(_vertices[j+1][0], _vertices[j+1][1], _vertices[j+1][2]);
    glVertex3f(_vertices[j+2][0], _vertices[j+2][1], _vertices[j+2][2]);
  
    j = j+3;
  }
  
  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
}


