#include "testApp.h"

Particle_props :: Particle_props(){
    locat = ofVec3f(float(NULL));
    veloc = ofVec3f(float(NULL));
    accel = ofVec3f(float(NULL));
    color = ofColor(float(NULL));
    rad = int(NULL);
    relax_fact = float(NULL);
    isAlive = true;
}


   /*
Base_World::Base_World(){
    name = "baseW";
    default_addedItemName = "basePS";
}

void Base_World::add_itemByName(string iName, Particle_props init_props){
   if (iName.size() == 0){
       iName = default_addedItemName;
       //cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("basePS") == 0){
       add(new Base_ParticlesSystem(init_props));
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("derivedPS") == 0){
       add(new RegularGrid_ParticlesSystem(init_props));
       //cout<<"add item, iName:"<<iName<<endl;
   }
    .
    .
    .
       Add new item types
}
   */
//
////main(){
////    
////    Base_ParticlesSystem sys;
////    sys.setup();
////    sys.pop_itemById(8);
////    sys.get_itemsByName();
////    sys.add(new BaseParticle());
////    sys.get_itemsByName();
////    sys.pop_itemByName("baseP");
////    sys.get_itemsByName();
////    sys.add(new DerivedParticle());
////    sys.get_itemsByName();
////    sys.pop_itemById(2);
////    sys.get_itemsByName();
////    sys.add_itemByName("derivedP");
////    sys.set_default_itemName("derivedP");
////    sys.add_itemByName();
////    sys.get_itemsByName();
////    sys.clear();
////    sys.get_itemsByName();
////    sys.add_itemByName();
////    sys.add_itemByName();
////    sys.add_itemByName();
////    sys.get_itemsByName();
////    sys.reset_itemTypeById(2,"baseP");
////    sys.set_default_itemName("baseP");
////    sys.reset_itemTypeById(0);
////    sys.get_itemsByName();
////
////    cout<<"world..."<<endl;
////    Base_World myWorld;
////    myWorld.add(&sys);
////    myWorld.get_itemsByName()[0]->get_itemsByName();
////    cout<<"done"<<endl;
////    
////    //World world;
////    //world.add("basePS","baseP");
////    //cout<<"size world:"<<world.base_particles_sys.size()<<endl;
////    //world.base_particles_sys.back().setup();
////    //world.get_info();
////}
