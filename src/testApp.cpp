#include "testApp.h"
#include "math.h"

getMouseLocation mouse;

void testApp::setup(){
    Particle* p;
    Particles_Container* g;
    //ofSetFrameRate(1);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    // 15 pixels given for particle regular grid distance
    //mouseWave.min_dist = regularGrid_interactions_system.grid_ds*2;
    //mouseWaveGenerator.setup();
    mouse.startThread(true, false);
    managerInterface.start(&world);
    
    p = world.create_particle("MP_RegGrid");

    p = world.create_particle("P_Circle");

    *(p->ofColorPtr_map["color"]) = ofColor(255,0,0);
    *(p->intPtr_map["rad"]) = 10;

    p->behaviors.add_itemByName("B_MouseTracking",p);
    
    g = world.create_group("G_dancers");
    g->add(p,false);

    //world.remove_particle(p);
    //for (u_int i=0; i<world.groups.itemsVector.size(); i++){
    //    cout<<world.groups.itemsVector[i]->id;
    //}

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

     managerInterface.listen(key);
/*
     switch (key){
         case 'w':
             world.particles.itemsVector.back()->interactions.add_itemByName("Wave_Source",
                                                       world.particles.itemsVector.back());
             world.particles.itemsVector.back()->interactions.itemsVector.back()->actuated_particles                          = world.groups.itemsVector.back();
             cout<<"add Wave_Source interaction"<<endl;
             break;
         case 'r':
             world.particles.itemsVector.back()->interactions.add_itemByName("Electrical_Repulsion",
                                                       world.particles.itemsVector.back());
             world.particles.itemsVector.back()->interactions.itemsVector.back()->actuated_particles                          = world.groups.itemsVector.back();
             cout<<"add Electrical_Repulsion interaction"<<endl;
             break;
         case 'i':
             world.particles.itemsVector.back()->interactions.pop();
             cout<<"pop Electrical_Repulsion interaction"<<endl;
             break;
         case 'l':
             world.particles.itemsVector.back()->behaviors.pop();
             cout<<"pop MouseTracking behavior"<<endl;
             break;
         case 'm':
             world.particles.itemsVector.back()->behaviors.add_itemByName("B_MouseTracking",
                                                world.particles.itemsVector.back());
             cout<<"add B_MouseTracking"<<endl;
             break;
         case 'o':
             for (u_int i=0; i<world.particles.itemsVector.size()-2; i++){
                 world.particles.itemsVector[i]->locat.set(0);
             }
             cout<<"set particles location to origin"<<endl;
             break;
         case 'a':
             for (u_int i=0; i<world.particles.itemsVector.size()-2; i++){
                 world.particles.itemsVector[i]->behaviors.add_itemByName("GravityGlue",
                                                world.particles.itemsVector[i]);
             }
             cout<<"set GravityGlue"<<endl;
             break;
          case 'f':
             for (u_int i=0; i<world.particles.itemsVector.size()-2; i++){
                 world.particles.itemsVector[i]->behaviors.pop();
             }
             cout<<"pop GravityGlue behavior"<<endl;
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
