#include "testApp.h"

Behavior::Behavior(Particle_props* host_props){
    props = host_props;
}

void Behavior::run(){
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

   if (iName.compare("B_1") == 0){
       newBehavior = new Behavior(host_props);
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("B_MouseTracking") == 0){
       add(new MouseTracking(host_props));
       //add(new DerivedParticle());
       //cout<<"add item, iName:"<<iName<<endl;
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


