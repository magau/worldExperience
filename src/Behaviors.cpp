#include "testApp.h"

Behavior::Behavior(){
    host_particle = (Particle*)NULL;
    isAlive = true;
    isActive = true;
}

Behavior::Behavior(Particle* _host_particle){
    host_particle = _host_particle;
    isAlive = true;
    isActive = true;
}

void Behavior::run(Particle* _host_particle){
}

GravityGlue::GravityGlue() : Behavior(){

    name = "B_GravityGlue";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

GravityGlue::GravityGlue(Particle* _host_particle) : Behavior(_host_particle){

    name = "B_GravityGlue";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    host_particle = _host_particle;
    locat = _host_particle->locat;
}

void GravityGlue::run(Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    if(_host_particle == (Particle*)NULL){
        _host_particle = host_particle;

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = locat.distance(_host_particle->locat);
    dx = _host_particle->locat.x - locat.x;
    dy = _host_particle->locat.y - locat.y;

    if (dist < min_dist) dist = min_dist;

    acc = weight / pow(dist,2);

    _host_particle->accel.x += - dx * acc;
    _host_particle->accel.y += - dy * acc;

    //Do not aplly relaxation at the bounthery wall  
    //int offset = _host_particle->rad;
    //if (_host_particle->locat.x > offset &&
    //    _host_particle->locat.x < ofGetWindowWidth() - offset &&
    //    _host_particle->locat.y > offset &&
    //    _host_particle->locat.y < ofGetWindowHeight() - offset ){

    _host_particle->relax_fact = 0.7;
    //}
    } else {
        cout << "behavior runing in dead mode..." << endl;
    }
}

MouseTracking::MouseTracking() : Behavior(){
    name = "B_MouseTracking"; 
}

MouseTracking::MouseTracking(Particle* _host_particle) : Behavior(_host_particle){
    name = "B_MouseTracking"; 
}

void MouseTracking::run(Particle* _host_particle){
   extern getMouseLocation mouse;
   if (_host_particle == (Particle*)NULL)
       _host_particle = host_particle;
   _host_particle->veloc.x = mouse.x - _host_particle->locat.x;
   _host_particle->veloc.y = mouse.y - _host_particle->locat.y;
}

Behavior* Behaviors_Container::add_itemByName(string iName, Particle* _host_particle){

   Behavior* newBehavior = (int)NULL;

   if (iName.size() == 0) iName = default_addedItemName;

   if (iName.compare("B_GravityGlue") == 0){
       newBehavior = new GravityGlue(_host_particle);
   } else if (iName.compare("B_MouseTracking") == 0){
       newBehavior = new MouseTracking(_host_particle);
   }
   /*
    .
    .
    .
       Add new item types
   */

   add(newBehavior);

   return newBehavior;
}
