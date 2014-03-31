#include "testApp.h"

#ifdef USE_MOUSE_THREAD
getMouseLocation mouse;
#endif
void testApp::setup(){
    Particle* p;
    //ofSetFrameRate(1);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
#ifdef USE_MOUSE_THREAD
    mouse.startThread(true, false);
#endif
    //managerInterface.start(&world);
    
    // Cria a particula "MP_RegGrid" que por sua vez cria uma
    // grelha regular de particulas com o tipo "P_Circle". 
    p = world.create_particle("MP_RegGrid");
    
    // Cria uma tag t0 à qual adiciona as particulas da grelha regular
    // e o comportamento "B_GravityGlue".
    Tag* t0 = world.create_tag();
    //t0->add_behavior("B_GravityGlue");
    t0->create_behavior("B_GravityGlue");
    t0->add_particles(world.particles.get_itemsByName("P_Circle"));
    //t0->add_behavior("B_GravityGlue");

    // Cria uma nova particula vermelha.
    p = world.create_particle("P_Circle");
    p->set_ofColor("color",ofColor(255,0,0));
    
    // Cria uma nova tag t1 à qual adiciona a particula vermelha
    // e o comportamento "B_MouseTracking".
    Tag* t1 = world.create_tag();
    t1->add_particle(p);
    //t1->create_behavior("B_MouseTracking");
    t1->create_behavior("B_MouseTracking");

    // Adiciona à tag t1 uma interacção do tipo "I_ElectRepulsion"
    //Interaction* i0 = t1->create_interaction("I_ElectRepulsion");
    Interaction* i0 = t1->create_interaction("I_ElectRepulsion");
    //Interaction* i0 = t1->add_interaction("I_WaveSource");
    // Adiciona a tag t0, que transporta consigo as particulas
    // da grelha, à interacção.
    i0->add_actuated_tag(t0);
    //t0->add_bool_listener_to_particles(&(t0->bool_event));
    //t0->add_listener_to_particles<bool_attr>(&(t0->bool_event));
    t0->add_listener_to_particles("isAlive");
    t0->add_listener_to_particles("color");

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
     switch (key){
         case 'd':{
             bool_attr d;
             d.name = "isAlive";
             d.value = false;
             ofNotifyEvent(world.tags.get_itemById(0)->bool_event, d);
             break;}
         case 'b':{
             ofColor_attr b;
             b.name = "color";
             b.value = ofColor(0,0,255);
             ofNotifyEvent(world.tags.get_itemById(0)->ofColor_event, b);
             break;}
         case 'g':{
             ofColor_attr g;
             g.name = "color";
             g.value = ofColor(0,255,0);
             ofNotifyEvent(world.tags.get_itemById(0)->ofColor_event, g);
             break;}
         case 'r':{
             ofColor_attr r;
             r.name = "color";
             r.value = ofColor(255,0,0);
             ofNotifyEvent(world.tags.get_itemById(0)->ofColor_event, r);
             break;}
         case 'w':{
             ofColor_attr r;
             r.name = "color";
             r.value = ofColor(255);
             ofNotifyEvent(world.tags.get_itemById(0)->ofColor_event, r);
             break;}
         case 'f':{
             Tag* tag = world.tags.get_itemById(1);
             tag->actions.pop_itemsByName("B_MouseTracking");
             break;}
         case 'm':{
             Tag* tag = world.tags.get_itemById(1);
             tag->create_behavior("B_MouseTracking");
             break;}
      }
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
#ifdef USE_MOUSE_THREAD
 // stop the thread
 mouse.stopThread();
#endif
}
