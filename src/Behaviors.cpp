#include "testApp.h"

Behavior::Behavior(Particle_props* host_props){
    props = host_props;
}

void Behaviors_Container::add_itemByName(string iName, Particle_props* init_props){
   if (iName.size() == 0){
       iName = default_addedItemName;
       //cout<<"default itemType:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("I_1") == 0){
       add(new Behavior(init_props));
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("I_2") == 0){
       add(new Behavior(init_props));
       //add(new DerivedParticle());
       //cout<<"add item, iName:"<<iName<<endl;
   }
   /*
    .
    .
    .
       Add new item types
   */
}


