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

void Behavior::run(Particle* _host_particle){}

void Behavior::setup(Particle* _host_particle){}

void Behavior::free(Particle* _host_particle){}

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

void GravityGlue::setup(Particle* _host_particle){
    _host_particle->set_var(name+"_loc", _host_particle->locat);
}

void GravityGlue::free(Particle* _host_particle){
    delete _host_particle->ofVec3fPtr_map[name+"_loc"]; 
    _host_particle->ofVec3fPtr_map.erase(name+"_loc");    
}

void GravityGlue::run(Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;
    ofVec3f* _locat;

    //cout << "run behavior:" << name << endl;

    if(_host_particle == (Particle*)NULL){
        _host_particle = host_particle;
        _locat = &locat;
    } else {
        _locat = _host_particle->get_ofVec3f(name+"_loc");
        //cout << "locat:" << (*_locat) << endl;
    }

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = _locat->distance(_host_particle->locat);
    dx = _host_particle->locat.x - _locat->x;
    dy = _host_particle->locat.y - _locat->y;

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
       if(_host_particle != (Particle*)NULL)
           newBehavior = new GravityGlue(_host_particle);
       else
           newBehavior = new GravityGlue();
   } else if (iName.compare("B_MouseTracking") == 0){
       if(_host_particle != (Particle*)NULL)
           newBehavior = new MouseTracking(_host_particle);
       else
           newBehavior = new MouseTracking();
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
