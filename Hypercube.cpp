
#include "Hypercube.h"

//#include "WorldTranslate.H"

Hypercube::Hypercube() {
  
  _slices = 4;
  _stacks = 4;

  _a = 0.0;
  _b = 0.0;
  _c = 0.0;

  first = 1;

  initialize_colors();

  calculate_geometry();

  _face_vertices.clear();
  _line_vertices.clear();
}

void Hypercube::initialize_colors() {
  
  // Colorscheme from PIC24.GIF, d/l from the web
  _colorArray[0][0] = 255/255.0; _colorArray[0][1] = 110/255.0;  _colorArray[0][2] = 180/255.0;
  _colorArray[1][0] = 255/255.0; _colorArray[1][1] = 255/255.0;  _colorArray[1][2] = 255/255.0;
  _colorArray[2][0] = 67/255.0;   _colorArray[2][1] = 110/255.0;   _colorArray[2][2] = 238/255.0;
  
  _colorArray[3][0] = 255/255.0;   _colorArray[3][1] = 255/255.0;   _colorArray[3][2] = 0/255.0;
  _colorArray[4][0] = 0/255.0;   _colorArray[4][1] = 100/255.0; _colorArray[4][2] = 0/255.0;
  _colorArray[5][0] = 102/255.0; _colorArray[5][1] = 205/255.0; _colorArray[5][2] = 0/255.0;
  
}


void Hypercube::manual_increment(int code) {
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
  
  fprintf(stderr,"Values of a, b, c inside Hypercube::manual_increment are %f, %f, %f\n " , _a, _b, _c);

  calculate_geometry();

}

//given new values of a,b,c update the private variables..
void Hypercube::update_geometry(double a, double b, double c) {

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

void Hypercube::calculate_geometry() {

  double theta, ntheta;
  double phi, nphi;
  
  double x,y,u,v;
  double nx, ny, nu, nv;

  Vector3 pt1, pt2, pt3, pos;
  Vector3 norm1, norm2, ncross;

  double x1,x2,x3,x4;
  double y1,y2,y3,y4;
  double z1,z2,z3,z4;
  double den1,den2,den3,den4;
  
  double d,den;
  

  if (_face_vertices.size()>0)
    _face_vertices.clear();
  if (_line_vertices.size()>0)
    _line_vertices.clear();


  if (_normals.size()>0) 
    _normals.clear();

  if (_face_colors.size()>0)
    _face_colors.clear();
  if (_line_colors.size()>0)
    _line_colors.clear();


  d = 1 - (_a+_b+_c);
  den = sqrt(2) * sqrt(_a*_a + _b*_b + _c*_c + d*d);
  
  for (int j=0; j<_slices; j++)  {
    
    phi =  ((2*M_PI* j  ) /_slices);
    nphi = ((2*M_PI*(j+1))/_slices);
    
    u = cos(phi);
    v = sin(phi);
    nu = cos(nphi);
    nv = sin(nphi);
    
    //    if (j%2==0) 
    { // Planes and lines both..
      
      for (int i=0; i<_stacks; i++) { // # stacks = _par2 till _par2 for tip !! 
        
        //int ci = (int) floor(((double)j)/2.0);
        int ci = j;

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
        pt3[1]= x4;//(den - den4); 
        pt3[0]= y4;//(den - den4);
        pt3[2]= z4;//(den - den4);
        
        // Point A........
        pt1[1]= x1;//(den - den1); 
        pt1[0]= y1;//(den - den1);
        pt1[2]= z1;//(den - den1);
        
        // Point B........
        pt2[1]= x2;//(den - den2); 
        pt2[0]= y2;//(den - den2);
        pt2[2]= z2;//(den - den2);
        
        ncross = cross(pt2-pt1, pt3-pt1);
        
        if (j%2==0) { // planes
	  _face_vertices.push_back(pt1);
	  _face_vertices.push_back(pt3);
	  _face_vertices.push_back(pt2);

	  _face_colors.push_back(Vector3(_colorArray[ci][0],_colorArray[ci][1],_colorArray[ci][2]));
        } 
        else { // lines
          //          Vector3 pos = (pt3 + pt1)/2.0;
          pos = Vector3(pt1[0]+pt3[0], pt1[1]+pt3[1], pt1[2]+pt3[2]); 
          pos = pos / 2.0;

          _line_vertices.push_back(pt1);
          _line_vertices.push_back(pos);
          _line_vertices.push_back(pt3);
          _line_colors.push_back(Vector3(_colorArray[ci][0],_colorArray[ci][1],_colorArray[ci][2]));
        }
        
        _normals.push_back(ncross);
        
        //_colors += Vector3(_colorArray[ci%11][0],_colorArray[ci%11][1],_colorArray[ci%11][2]);

        
        // Finished with the first triangle..................
        
        // Triangle BCD ..............................    
        
        // Point C	
        pt2[1]= x3;//(den - den3); 
        pt2[0]= y3;//(den - den3);
        pt2[2]= z3;//(den - den3); 
        
        // Point B
        pt1[1]= x2;//(den - den2); 
        pt1[0]= y2;//(den - den2);
        pt1[2]= z2;//(den - den2);
        
        // Point D 
        pt3[1]= x4;//(den - den4); 
        pt3[0]= y4;//(den - den4);
        pt3[2]= z4;//(den - den4);
        
        ncross = cross(pt2-pt1, pt3-pt1);
        
        if (j%2==0) { // planes
          _face_vertices.push_back(pt3);
          _face_vertices.push_back(pt2);
          _face_vertices.push_back(pt1);
          _face_colors.push_back(Vector3(_colorArray[ci][0],_colorArray[ci][1],_colorArray[ci][2]));
        } 
        else { // lines
          //          Vector3 pos = (pt1 + pt2)/2.0; 
          Vector3 pos = Vector3(pt1[0]+pt2[0], pt1[1]+pt2[1], pt1[2]+pt2[2]);
          pos = pos / 2.0;
          
          _line_vertices.push_back(pt1);
          _line_vertices.push_back(pt2);
          _line_vertices.push_back(pos);
          _line_colors.push_back(Vector3(_colorArray[ci][0],_colorArray[ci][1],_colorArray[ci][2]));
        }
        
        _normals.push_back(ncross);
        
        //_colors += Vector3(_colorArray[ci%11][0],_colorArray[ci%11][1],_colorArray[ci%11][2]);

        // Finished with the second triangle..................	
      

      }//_stacks loop
      
    } // j%2 planes..
    
    }//_slices loop
    
  
}

void Hypercube::draw() {

  //  int numTriangles = _normals.size();
  //  assert(numTriangles == _colors.size());
  //  assert(numTriangles*3 == _face_vertices.size());
  
  //  int numTriangles = (int)(_face_colors.size()/2.0);
  int numTriangles = _face_colors.size();

  //cout << "numTriangles is" << numTriangles << endl;
  assert(_face_vertices.size()==_line_vertices.size());
  
  glMatrixMode(GL_MODELVIEW);
  
  glPushMatrix();
  //  glMultMatrixd(MathTranslate::instance()->ROOM_TO_WORLD().invert().matrix());
  //glMultMatrixd(MathTranslate::instance()->WORLD_TO_ROOM().matrix());
//  std::cerr << "Hypercube.cpp: VRG3D version of glMultMatrixd(MathTranslate::instance()->WORLD_TO_ROOM().matrix()) not implemented.." << std::endl;
  
  glTranslatef(5,0,0); // draw the hypercube off to the side

  glEnable(GL_BLEND);

  // drawing some of the triangle edges to show shape better..
  int j = 0;
  glBegin(GL_LINES);
  glLineWidth(3.0);
  for (int i=0; i<numTriangles; i++) {
    glColor3f(0,0,0);
    glVertex3f(_face_vertices[j][0], _face_vertices[j][1], _face_vertices[j][2]);
    glVertex3f(_face_vertices[j+1][0], _face_vertices[j+1][1], _face_vertices[j+1][2]);
    glVertex3f(_face_vertices[j+1][0], _face_vertices[j+1][1], _face_vertices[j+1][2]);
    glVertex3f(_face_vertices[j+2][0], _face_vertices[j+2][1], _face_vertices[j+2][2]);
    
    j = j+3;
  }
  glEnd();


  
  // draw connecting lines..
  j = 0;
  glLineWidth(5.0);
  glBegin(GL_LINES);
  for (int i=0; i<numTriangles; i++) {
    glColor3f(_line_colors[i][0],_line_colors[i][1],_line_colors[i][2]);
    //    glNormal3f(_normals[i][0],_normals[i][1],_normals[i][2]);
    
    glVertex3f(_line_vertices[j][0], _line_vertices[j][1], _line_vertices[j][2]);
    glVertex3f(_line_vertices[j+1][0], _line_vertices[j+1][1], _line_vertices[j+1][2]);
    glVertex3f(_line_vertices[j+1][0], _line_vertices[j+1][1], _line_vertices[j+1][2]);
    glVertex3f(_line_vertices[j+2][0], _line_vertices[j+2][1], _line_vertices[j+2][2]);
    
    j = j + 3;
  }
  glEnd();


  // draw solid triangles..
  j = 0;
  glBegin(GL_TRIANGLES);
  for (int i=0; i<numTriangles; i++) {
    glColor4f(_face_colors[i][0],_face_colors[i][1],_face_colors[i][2],0.9);
    glNormal3f(_normals[i][0],_normals[i][1],_normals[i][2]);
    
    glVertex3f(_face_vertices[j][0], _face_vertices[j][1], _face_vertices[j][2]);
    glVertex3f(_face_vertices[j+1][0], _face_vertices[j+1][1], _face_vertices[j+1][2]);
    glVertex3f(_face_vertices[j+2][0], _face_vertices[j+2][1], _face_vertices[j+2][2]);
  
    j = j+3;
  }
  glEnd();



  glDisable(GL_BLEND);

  glLineWidth(1.0);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
}


