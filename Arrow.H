/**
 * \author Daniel Keefe (dfk)
 *
 * \file  Arrow.H
 * \brief
 *
 */


#ifndef ARROW_H
#define ARROW_H

#include "DrawObj.H"
#include "Color.H"

#include "glwrap.H"

// gluebase includes
#define OUTSIDE_GLUE_CORE
#include <config/config.H>


class Arrow : public DrawObj
{
 public:
  Arrow(Wpt loc=Wpt(0,0,0), Color col=Color::red) : 
    DrawObj("Arrow_drawobj") 
  {
    _shininess = CONFIGval("DEFAULT_SHININESS",100,false);
    _specular  = Color(CONFIGval("DEFAULT_SPECULAR",
				 str_ptr("1.0 1.0 1.0 1.0"),false));
    _emission  = Color(CONFIGval("DEFAULT_EMISSION",
				 str_ptr("0.2 0.2 0.2 1.0"),false));
    _loc = loc;
    _color = col;
  }
  
  virtual ~Arrow() {}
  
  void setLoc(Wpt p) { _loc = p; }
  void setColor(Color c) { _color = c; }
  void reColor(Color c) { _color = c; }

  void drawDisk(Wtransf m, Color c, double rad) {
    glColor4fv(c.array());
    glPushMatrix();
    glMultMatrixd(m.matrix());
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluDisk(qobj, 0, rad, 10, 1);
    glPopMatrix();
  }

  void drawCone(Wtransf m, Color c, double length, double rad) {
    glColor4fv(c.array());
    glPushMatrix();
    glMultMatrixd(m.matrix());
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluCylinder(qobj, rad, 0, length, 10, 10);
    glPopMatrix();
  }

  void drawCylinder(Wtransf m, Color c, double length, double rad) {
    glColor4fv(c.array());
    glPushMatrix();
    glMultMatrixd(m.matrix());
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluCylinder(qobj, rad, rad, length, 10, 10);
    glPopMatrix();
  }



  void draw() {
    // TODO: put this all in a display list
    // setup proper rendering states
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, _shininess);  
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColor4fv(_specular.array());
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glColor4fv(_emission.array());

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    drawCone(Wtransf::translation(Wvec(0,0,-0.25)),_color, 0.25, 0.125);
    drawDisk(Wtransf::translation(Wvec(0,0,-0.25)),_color, 0.125);
    drawCylinder(Wtransf::translation(Wvec(0,0,-0.75)),_color, 0.5, 0.03);
    drawDisk(Wtransf::translation(Wvec(0,0,-0.75)),_color, 0.03);

    
    glDisable(GL_COLOR_MATERIAL);

  }

 protected:

  Wpt   _loc;
  float _shininess;
  Color _specular;
  Color _emission;
  Color _color;

};

#endif
