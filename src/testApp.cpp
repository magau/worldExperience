#include "testApp.h"
#include "math.h"

getMouseLocation mouse;

void testApp::setup(){
    //ofSetFrameRate(1);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    // 15 pixels given for particle regular grid distance
//    main_particles_system.setup(15,ofPoint(4.0/5));
//    regularGrid_interactions_system.setup(2,15,ofPoint(4.0/5));
//    external_interactions.setup();
////    external_interactions.allInteractions_ptr[0]->min_dist = regularGrid_interactions_system.grid_ds*2;
////    mouseWave.min_dist = regularGrid_interactions_system.grid_ds*2;
//
////    mouseWaveGenerator.setup();
//
//    //setting up the mouse controled location.
//    //mouse.setup(&external_interactions.allInteractions_ptr[0]->props.loc);
    mouse.startThread(true, false);
    managerInterface.start();
    //listenMsg = false;
//    main_particles_system.setup_interactions(); 
//
//    u_int interaction_type = 1;
//    external_interactions.setup(interaction_type);
//
//#ifdef OSC_MSG
//    external_interactions.oscReceiver.setup(12346);
//#endif
//#ifdef SYPHON
//    mainOutputSyphonServer.setName("dancingParticules");
//#endif
//
  manager.world = &world;
  manager.create_regularGrid(15,4.0/5);
  //cout<<world.particles.itemsVector.size()<<endl;
  //for (u_int i=0; i<manager.world->groups.itemsVector.size(); i++){
  //    cout<<manager.world->groups.itemsVector[i]->id;
  //}
  //cout<<endl;


}
   
   //--------------------------------------------------------------
   void testApp::update(){
       manager.update();
//       external_interactions.update();
//       main_particles_system.update_interactions(external_interactions.allInteractions_ptr);
//cout<<"update start..."<<endl;


//     external_interactions.update(ofPoint(mouse.x,mouse.y));
//     external_interactions.run( &(main_particles_system.particles) );
////mouseWaveGenerator.update(ofPoint(mouse.x,mouse.y));
////mouseWaveGenerator.run( &(main_particles_system.particles) );
//     //mouseWave.update(ofPoint(mouse.x,mouse.y));
//     //mouseWave.run( &(main_particles_system.particles) );
//
//     regularGrid_interactions_system.run( &(main_particles_system.particles) );
////cout<<"update end."<<endl;
       //if(keys[OF_KEY_ALT]){// && keys['g']){
       //if(ofGetKeyPressed('a')){//OF_KEY_CTRL)){
       //    for (u_int i=0; i<manager.world->groups.itemsVector.size(); i++){
       //        cout<<manager.world->groups.itemsVector[i]->id;
       //    }
       //    cout<<endl;

       //    //if (key != OF_KEY_ALT && key != 'g') {  
       //    //    group = manager.world->groups.get_itemById(key);
       //    //    cout<<group->name<<";"<<group->id<<endl;
       //    //    // do whatever you wanna do if both a and b are down.  
       //    //}
       //}

   }
   
   //--------------------------------------------------------------
   void testApp::draw(){
       ofBackground(0);

       manager.draw();
//
//         for(int i=0;i<world.particles.itemsVector.size();i++){
//             world.particles.itemsVector[i]->display();
//            // cout<<i<<":"<<world.particles.itemsVector[i]->props.locat<<endl;
//
//         }
//
////cout<<"update start..."<<endl;
//       main_particles_system.run();
////cout<<"update end."<<endl;
////ofSleepMillis(50);
////   
////   #ifdef SYPHON
////   	mainOutputSyphonServer.publishScreen();
////   #endif
////   
////   #ifdef OSC_MSG
////       //oscPositionParticle.run();
////   #endif
   }
   
   //--------------------------------------------------------------
   void testApp::keyPressed(int key){
        managerInterface.listen(key);
        //switch (key){
        //    case 'm':
        //        manager.create_regularGrid(15,4.0/5);
        //        break;
        //    case 's':
        //        for (u_int i=0; i<manager.world->groups.itemsVector.size(); i++){
        //            cout<<manager.world->groups.itemsVector[i]->id;
        //        }
        //        cout<<endl;
        //        break;
        //}

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

   void testApp::exit() {
 
    // stop the thread
    mouse.stopThread();
   }
