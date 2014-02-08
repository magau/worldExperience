#include "testApp.h"

getMouseLocation mouse;

void testApp::setup(){
    Particle* p;
    //ofSetFrameRate(1);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    mouse.startThread(true, false);
    //managerInterface.start(&world);
    
    // Cria a particula "MP_RegGrid" que por sua vez cria uma
    // grelha regular de particulas com o tipo "P_Circle". 
    p = world.create_particle("MP_RegGrid");
    
    // Cria uma tag t0 à qual adiciona as particulas da grelha regular
    // e o comportamento "B_GravityGlue".
    Tag* t0 = world.create_tag();
    t0->add_particles(world.particles.get_itemsByName("P_Circle"));
    t0->add_behavior("B_GravityGlue");

    // Cria uma nova particula vermelha.
    p = world.create_particle("P_Circle");
    p->set_ofColor("color",ofColor(255,0,0));
    
    // Cria uma nova tag t1 à qual adiciona a particula vermelha
    // e o comportamento "B_MouseTracking".
    Tag* t1 = world.create_tag();
    t1->add_particle(p);
    t1->add_behavior("B_MouseTracking");

    // Adiciona à tag t1 uma interacção do tipo "I_ElectRepulsion"
    Interaction* i0 = t1->add_interaction("I_ElectRepulsion");
    // Adiciona a tag t0, que transporta consigo as particulas
    // da grelha, à interacção.
    i0->add_tag(t0);

}
   
//--------------------------------------------------------------
void testApp::update(){
    world.update();
}
   
//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    world.draw();

    //ofSleepMillis(50);

#ifdef SYPHON
    mainOutputSyphonServer.publishScreen();
#endif

}
   
//--------------------------------------------------------------
void testApp::keyPressed(int key){

     //managerInterface.listen(key);
/*
     switch (key){
         case 'a':
             ...
             break;
         case 'b':
             ...
             break;
      }
*/

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::exit() {
 // stop the thread
 mouse.stopThread();
}
