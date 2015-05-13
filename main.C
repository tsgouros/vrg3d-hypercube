

#include "GlutEngine.H"
#include "TestApp.H"



int
main(int argc, char **argv)
{
  // create a Glut VR Engine - this sets ISVREngine's instance variable
  GlutEngine::createInstance(argc,argv);

  TestApp *ta = new TestApp();  
  ISVREngine::instance()->run(ta);

  return 0;           
}
