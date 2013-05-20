#include "testApp.h"

Behavior::Behavior(Particle_props* host_props){
    props = host_props;
}

void Behavior::run(){
}

GravityGlue::GravityGlue(Particle_props* host_props) :
Behavior(host_props){

    name = "GravityGlue";
    locat = host_props->locat;
    name = "I_1";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void GravityGlue::run(){
    float dist,dx,dy,weight,weight_fact,acc;
    //Particle* actuated_particle;

    weight_fact = 0.25;

    weight = max_dist*weight_fact;

    dist = locat.distance(props->locat);
    dx = props->locat.x - locat.x;
    dy = props->locat.y - locat.y;
    acc = weight / pow(dist,2);
    props->accel.x += dx * acc;
    props->accel.y += dy * acc;
    //Do not aplly relaxation at the bounthery wall  
    int offset = props->rad;
    if (props->locat.x > offset &&
        props->locat.x < ofGetWindowWidth() - offset &&
        props->locat.y > offset &&
        props->locat.y < ofGetWindowHeight() - offset ){

        props->relax_fact = 0.7;
     }

//if (id == 0) {
//    cout<<"locat:"<<locat<<" props->locat:"<<props->locat<<endl;
//}
 
}

MouseTracking::MouseTracking(Particle_props* host_props) : 
Behavior(host_props){
    name = "B_MouseTracking"; 
}

void MouseTracking::run(){
   extern getMouseLocation mouse;
   props->locat.x = mouse.x;
   props->locat.y = mouse.y;
}

Behavior* Behaviors_Container::add_itemByName(string iName, Particle_props* host_props){

   Behavior* newBehavior = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
       //cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("GravityGlue") == 0){
       newBehavior = new GravityGlue(host_props);
       //cout<<"add item, iName:"<<iName<<endl;
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


