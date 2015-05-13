
#include "TestApp.H"

// application specific includes
#include "ISModeler.H"
#include "ISMesh.H"
#include "ISMeshObj.H"
#include "MouseNavNew.H"
#include "WorldInt.H"
#include "ObjectInt.H"
#include "Dev2dToDev6d.H"
#include "DefaultCursor.H"

// for testing device input
#include "TestDev1D.H"
#include "TestDev2D.H"
#include "TestDev6D.H"
#include "TestDevBtn.H"

// Font stuff
#include "FontMgr.H"

#include <ivrnav-1.0/ivrflygrab.H>


TestApp::TestApp() : ISApp()
{
  torus = new Torus();
  hypercube = new Hypercube();
  hopf = new Hopf();

  //  control = new ControlSpace(torus, hypercube, hopf);
  control = new ControlSpace();
  
  wandInt = new SimpleInt(control, this);
  
  draw_mode = DRAW_HYPERCUBE;
}

TestApp::~TestApp()
{
  if (torus)
    delete torus;
  if (hypercube)
    delete hypercube;
  if (hopf) 
    delete hopf;


  if (wandInt)
    delete wandInt;
  if (control)
    delete control;
}

void
TestApp::splashScreen()
{
}

void
TestApp::postSplashInit()
{

  FONTMGR::registerFont(**CONFIGval("GLFONT","",true));

  // startup mouse stuff if display has desktop in it..  otherwise
  // assume you're using trackers etc..
  if (CONFIGval("DISPLAY","desktopwindow",false).contains("desktop")) {

    // a default interactor for scene navigation with a mouse
    new MouseNavNew();
    // translates mouse events into a simulated 6DOF device
    new Dev2dToDev6d("mouse_pointer","mouse_middle_btn",
		     "kbd_X","kbd_Y","kbd_Z","mouse_6dof",1);
  }

  // default inspace interactors for the world and objects
  new WorldInt();
  new ObjectInt();

  //  new FlyNavInt();
  
  new IVRFlyGrab();

  // a simple cursor that follows a 6DOF tracking device
  //  new DefaultCursor();



  // EXAMPLE 2: Create your own mesh-based geometry

  /*
    ISMesh *m2 = new ISMesh("my_fresh_mesh");
    ISVertex *v1 = m2->addVertex(Wpt(1.0, 0.5,-0.5));
    v1->setColor(Color::red);
    ISVertex *v2 = m2->addVertex(Wpt(2.0, 0.0, 0.0));
    v2->setColor(Color(1.0,0.9,0.4));
    ISVertex *v3 = m2->addVertex(Wpt(0.25,-0.5, 0.5));
    v3->setColor(Color::blue);
    
    m2->addFace(v1,v2,v3);
    
    // again, MeshObj is the subclass of DrawObj.. create a MeshObj container
    // for the Mesh and add it to the DrawMgr.
    ISMeshObj *mo2 = new ISMeshObj("my_fresh_meshobj",m2);
    DRAWMGR::registerObj(mo2);
  */

  // EXAMPLE 3: Very simple device input

  // *_TEST_DEVICES are space separated lists of devices for which to 
  // print out values as they change.  Each of the TestDev* classes shows
  // how to make a very, very simple FSA to print out the values of the
  // device input as they change.
  /*
  int i;
  str_list dev1ds = tokenize(CONFIGval("1D_TEST_DEVICES","",false));
  for (i=0;i<dev1ds.num();i++) {
    new TestDev1D(dev1ds[i]);
  }
  str_list dev2ds = tokenize(CONFIGval("2D_TEST_DEVICES","",false));
  for (i=0;i<dev2ds.num();i++) {
    new TestDev2D(dev2ds[i], XYpt(0.05, 0.88 - (double)i*0.1));
  }
  str_list dev6ds = tokenize(CONFIGval("6D_TEST_DEVICES","",false));
  for (i=0;i<dev6ds.num();i++) {
    new TestDev6D(dev6ds[i]);
  }
  str_list devbtns = tokenize(CONFIGval("BTN_TEST_DEVICES","",false));
  for (i=0;i<devbtns.num();i++) {
    new TestDevBtn(devbtns[i], XYpt(-0.98, 0.88 - (double)i*0.1), torus);
  }
  */

}

void
TestApp::postSplashGLContextInit()
{

}

void TestApp::draw()
{
  update_geometry();

  draw_text();

  wandInt->drawWand();
  
  control->draw();

  switch(draw_mode) {
    
  case DRAW_HYPERCUBE:
    hypercube->draw();
    break;
  case DRAW_HYPERCUBE_TORUS:
    hypercube->draw();
    torus->draw();
    break;
  case DRAW_HYPERCUBE_TORUS_HOPF:
    hypercube->draw();
    torus->draw(); 
    hopf->draw();
    break;
  case DRAW_TORUS_HOPF:
    torus->draw();
    hopf->draw();
    break;
  case DRAW_TORUS:
    torus->draw();
    break;
  case DRAW_HOPF:
    hopf->draw();
    break;
  default:
    break;
  }
  
  ISApp::draw();
}

void TestApp::update_geometry()
{
  double a,b,c;
  control->get_abc(a, b, c);
  
  // go over all the geometry objects
  torus->update_geometry(a,b,c);
  hypercube->update_geometry(a,b,c);
  hopf->update_geometry(a,b,c);

  sprintf(wall_text, "a=%4.2f b=%4.2f c=%4.2f", a,b,c);
  
}

void TestApp::draw_text()
{

  Wtransf myMat = Wtransf::align(Wpt(0,0,0),Wvec(1,0,0),Wvec(0,1,0),
                                 Wpt(0,0,0),Wvec(1,0,0),Wvec(0,-1,0))*
    Wtransf::scaling(Wvec(0.08,0.08,0.08));
  
  glPushMatrix();
  //  glMultMatrixd((Wtransf::translation(Wvec(-2.3,-1.9,0)) *
  //                  myMat).matrix());
  glMultMatrixd((Wtransf::translation(Wvec(-3.5,-3.8,4.0)) *
                 myMat).matrix());

  FONTMGR::render(wall_text, 0.0,0.0,0.0);
  glPopMatrix();
  
}

void TestApp::toggle_drawmode() {

  switch(draw_mode) {
  case DRAW_HYPERCUBE:
    draw_mode = DRAW_HYPERCUBE_TORUS;
    break;
  case DRAW_HYPERCUBE_TORUS:
    draw_mode = DRAW_HYPERCUBE_TORUS_HOPF;
    break;
  case DRAW_HYPERCUBE_TORUS_HOPF:
    draw_mode = DRAW_TORUS_HOPF;
    break;
  case DRAW_TORUS_HOPF:
    draw_mode = DRAW_TORUS;
    break;
  case DRAW_TORUS:
    draw_mode = DRAW_HOPF;
    break;
  case DRAW_HOPF:
    draw_mode = DRAW_HYPERCUBE;
    break;
  default:
    draw_mode = DRAW_HYPERCUBE;
    break;
  }
  

}
