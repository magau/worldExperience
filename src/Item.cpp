#include "testApp.h"

Item::Item(){
    isAlive = true;
    isActive = true;
}

string Item::get_name(){return name;}

int    Item::get_id(){return id;}

World* Item::get_world(){return world;}

bool   Item::is_alive(){return isAlive;}

bool   Item::is_active(){return isActive;}

void   Item::set_name(string _name){name=_name;}

void   Item::set_id(int _id){id=_id;}

void   Item::set_world(World* _world){world=_world;}

void   Item::set_live_state(bool live_state){isAlive=live_state;}

void   Item::set_active_state(bool active_state){isActive=active_state;}


Particle* Items_Fabric::create_particle(string item_name){

    Particle* newItem = (Particle*)NULL;

    if (item_name.compare("P_Base") == 0){
        newItem = new Particle();
    } else if (item_name.compare("P_Circle") == 0){
        newItem = new Circle();
    } else if (item_name.compare("MP_RegGrid") == 0){
        newItem = new RegularGrid_MP();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}

Behavior* Items_Fabric::create_behavior(string item_name){

    Behavior* newItem = (Behavior*)NULL;

    if (item_name.compare("B_GravityGlue") == 0){
        newItem = new GravityGlue();
    } else if (item_name.compare("B_MouseTracking") == 0){
        newItem = new MouseTracking();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}

Interaction* Items_Fabric::create_interaction(string item_name){

    Interaction* newItem = (Interaction*)NULL;

    if (item_name.compare("I_ElectRepulsion") == 0){
        newItem = new Electrical_Repulsion();
    } else if (item_name.compare("I_ElectAttraction") == 0){
        newItem = new Electrical_Attraction();
    } else if (item_name.compare("I_WaveSource") == 0){
        newItem = new Wave_Source();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}
