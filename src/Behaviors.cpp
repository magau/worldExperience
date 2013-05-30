#include "testApp.h"

Behavior::Behavior(Particle_props* host_props){
    props = host_props;
}

void Behavior::run(){
}

GravityGlue::GravityGlue(Particle_props* host_props) :
Behavior(host_props){

    name = "GravityGlue";
    locat = host_props->ofVec3f_map["loc"];
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void GravityGlue::run(){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = locat.distance(props->ofVec3f_map["loc"]);
    dx = props->ofVec3f_map["loc"].x - locat.x;
    dy = props->ofVec3f_map["loc"].y - locat.y;

    if (dist < min_dist) dist = min_dist;

    acc = weight / pow(dist,2);

    props->ofVec3f_map["acc"].x += - dx * acc;
    props->ofVec3f_map["acc"].y += - dy * acc;

    //Do not aplly relaxation at the bounthery wall  
    //int offset = props->rad;
    //if (props->locat.x > offset &&
    //    props->locat.x < ofGetWindowWidth() - offset &&
    //    props->locat.y > offset &&
    //    props->locat.y < ofGetWindowHeight() - offset ){

    props->relax_fact = 0.7;
    //}
}

MouseTracking::MouseTracking(Particle_props* host_props) : 
Behavior(host_props){
    name = "B_MouseTracking"; 
}

void MouseTracking::run(){
   extern getMouseLocation mouse;
   props->ofVec3f_map["vel"].x = mouse.x - props->ofVec3f_map["loc"].x;
   props->ofVec3f_map["vel"].y = mouse.y - props->ofVec3f_map["loc"].y;
}

Behavior* Behaviors_Container::add_itemByName(string iName, Particle_props* host_props){

   Behavior* newBehavior = (int)NULL;

   if (iName.size() == 0) iName = default_addedItemName;

   if (iName.compare("GravityGlue") == 0){
       newBehavior = new GravityGlue(host_props);
   } else if (iName.compare("B_MouseTracking") == 0){
       newBehavior = new MouseTracking(host_props);
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
