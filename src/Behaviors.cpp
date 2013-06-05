#include "testApp.h"

Behavior::Behavior(Particle* _host_particle){
    host_particle = _host_particle;
    isAlive = true;
    isActive = true;
}

void Behavior::run(){
}

GravityGlue::GravityGlue(Particle* _host_particle) :
Behavior(_host_particle){

    name = "GravityGlue";
    locat = _host_particle->locat;
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void GravityGlue::run(){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = locat.distance(host_particle->locat);
    dx = host_particle->locat.x - locat.x;
    dy = host_particle->locat.y - locat.y;

    if (dist < min_dist) dist = min_dist;

    acc = weight / pow(dist,2);

    host_particle->accel.x += - dx * acc;
    host_particle->accel.y += - dy * acc;

    //Do not aplly relaxation at the bounthery wall  
    //int offset = host_particle->rad;
    //if (host_particle->locat.x > offset &&
    //    host_particle->locat.x < ofGetWindowWidth() - offset &&
    //    host_particle->locat.y > offset &&
    //    host_particle->locat.y < ofGetWindowHeight() - offset ){

    host_particle->relax_fact = 0.7;
    //}
}

MouseTracking::MouseTracking(Particle* _host_particle) : 
Behavior(_host_particle){
    name = "B_MouseTracking"; 
}

void MouseTracking::run(){
   extern getMouseLocation mouse;
   host_particle->veloc.x = mouse.x - host_particle->locat.x;
   host_particle->veloc.y = mouse.y - host_particle->locat.y;
}

Behavior* Behaviors_Container::add_itemByName(string iName, Particle* _host_particle){

   Behavior* newBehavior = (int)NULL;

   if (iName.size() == 0) iName = default_addedItemName;

   if (iName.compare("GravityGlue") == 0){
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
