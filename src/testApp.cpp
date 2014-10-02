#include "testApp.h"

#ifdef USE_MOUSE_THREAD
getMouseLocation mouse;
#endif
void testApp::setup(){
    //cl = world.create_controller("Controller");
    Controller* cl = world.create_controller("Controller");
    //cl = world.create_controller("MidiController");
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

    p = world.create_particle("RegularGrid_MP");
    //cout << p->get_type_name() << endl;
    //p = world.create_particle(typeid(RegularGrid_MP*));
    
    // Cria uma tag t0 à qual adiciona as particulas da grelha regular
    // e o comportamento "B_GravityGlue".
    Tag* t0 = world.create_tag();
    //t0->create_behavior("GravityGlue");
    Behavior* b0 = t0->create_behavior(typeid(GravityGlue*));
    //cl->add_listener("ctrl3",b0);

    t0->add_particles(world.particles.get_items_by_typeid(typeid(Circle*)));
    //t0->add_behavior("B_GravityGlue");

    // Cria uma nova particula vermelha.
    //p = world.create_particle("Circle");
    p = world.create_particle(typeid(Circle*));
    p->set_item_parameter<ofColor>("color",ofColor(255,0,0));
    //p->set_ofColor("color",ofColor(255,0,0));

    // Cria uma nova tag t1 à qual adiciona a particula vermelha
    // e o comportamento "B_MouseTracking".
    Tag* t1 = world.create_tag();
    t1->add_particle(p);
    //t1->create_behavior("MouseTracking");
    t1->create_behavior(typeid(MouseTracking*));
    Particle* l = world.create_particle("Line");
    Tag* t2 = world.create_tag();
    t2->add_particle(l);
    Interaction* i1 = t1->create_interaction("DrawLine");
    i1->add_actuated_tag(t2);
    //t1->create_behavior(typeid(DrawLine*));

    // Adiciona à tag t1 uma interacção do tipo ElecticleRepulsion"
    //Interaction* i0 = t1->create_interaction("Electrical_Repulsion");
    Interaction* i0 = t1->create_interaction(typeid(Electrical_Repulsion*));
//cout << "Electrical_Repulsion interaction created." << endl;
    //cl->add_listener("ctrl2",i0);
//    cl->attach_listener_parameter("ctrl2",i0,"weight");
    //Interaction* i0 = t1->add_interaction("I_WaveSource");
    // Adiciona a tag t0, que transporta consigo as particulas
    // da grelha, à interacção.
    i0->add_actuated_tag(t0);

    World_Camera* c0 = &(world.camera);

    //cl->attach_listener_parameter("ctrl1",i0,"weight");
    //cl->attach_listener_parameter("ctrl1",t0,"rad");
    //cl->attach_listener_parameter("ctrl3",b0,"weight");
    cl->attach_listener_parameter("ctrl1",c0,"pan");
    cl->attach_listener_parameter("ctrl2",c0,"tilt");
    cl->attach_listener_parameter("switch4",c0,"travel");
//cout << "setup done." << endl; 
}
   
//--------------------------------------------------------------
void testApp::update(){
    world.update();

}
   
//--------------------------------------------------------------
void testApp::draw(){
    world.draw();
    //cl->run();


    //ofSleepMillis(50);

#ifdef SYPHON
    mainOutputSyphonServer.publishScreen();
#endif

}
   
//--------------------------------------------------------------
void testApp::keyPressed(int key){

     //managerInterface.listen(key);
     switch (key){
    //     case 'd':{
    //         Tag* t0 = world.tags.get_item_by_id(0);
    //         pair<string,bool> attr("is_alive", false);
    //         ofNotifyEvent(*(t0->get_event<pair<string,bool>>("e1")), attr);
    //         break;}
    //     case 'b':{
    //         Tag* t0 = world.tags.get_item_by_id(0);
    //         pair<string,ofColor> attr("color", ofColor(0,0,255));
    //         ofNotifyEvent(*(t0->get_event<pair<string,ofColor>>("e2")), attr);
    //         break;}
    //     case 'g':{
    //         Tag* t0 = world.tags.get_item_by_id(0);
    //         pair<string,ofColor> attr("color", ofColor(0,255,0));
    //         ofNotifyEvent(*(t0->get_event<pair<string,ofColor>>("e2")), attr);
    //         break;}
    //     case 'r':{
    //         Tag* t0 = world.tags.get_item_by_id(0);
    //         pair<string,ofColor> attr("color", ofColor(255,0,0));
    //         ofNotifyEvent(*(t0->get_event<pair<string,ofColor>>("e2")), attr);
    //         break;}
    //     case 'w':{
    //         Tag* t0 = world.tags.get_item_by_id(0);
    //         pair<string,ofColor> attr("color", ofColor(255));
    //         ofNotifyEvent(*(t0->get_event<pair<string,ofColor>>("e2")), attr);
    //         break;}
    //     case '+':{
    //         pair<string,Item_Parameter<int>> attr("rad",Item_Parameter<int>(30,pair<int,int>(0,500)));
    //         ofNotifyEvent(*(cl->get_event<int>("ctrl2")), attr);
    //         break;}
    //     case '-':{
    //         pair<string,Item_Parameter<int>> attr("rad",Item_Parameter<int>(10,pair<int,int>(0,500)));
    //         ofNotifyEvent(*(cl->get_event<int>("ctrl2")), attr);
    //         break;}
    //   case 'v':{
    //       pair<string,Item_Parameter<bool>> attr("is_visible",Item_Parameter<bool>(true));
    //       ofNotifyEvent(*(cl->get_event<bool>("ctrl1")), attr);
    //       break;}
    //   case 'i':{
    //         Controller* cl = world.controllers.get_item_by_id(0);
    //         if (cl != NULL)
    //             cl->erase_button("ctrl3");
    //       break;}
         case 'f':{
             Tag* t1 = world.tags.get_item_by_id(1);
             t1->behaviors.erase_items_by_typeid(typeid(MouseTracking*));
             break;}
         case 'm':{
             Tag* t1 = world.tags.get_item_by_id(1);
             t1->create_behavior("MouseTracking");
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
