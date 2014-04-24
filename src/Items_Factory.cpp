#include "testApp.h"

Particle* Items_Factory::create_particle(const type_info& item_typeid){

    

    Particle* newItem = (Particle*)NULL;

    if (item_typeid == typeid(Particle*)){
        newItem = new Particle();
    } else if (item_typeid == typeid(Circle*)){
        newItem = new Circle();
    } else if (item_typeid == typeid(RegularGrid_MP*)){
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

Particle* Items_Factory::create_particle(string item_name){

    Particle* newItem = (Particle*)NULL;

    if (item_name.compare("Particle") == 0){
        newItem = new Particle();
    } else if (item_name.compare("Circle") == 0){
        newItem = new Circle();
    } else if (item_name.compare("RegularGrid_MP") == 0){
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

Behavior* Items_Factory::create_behavior(const type_info& item_typeid){

    Behavior* newItem = (Behavior*)NULL;

    if (item_typeid == typeid(GravityGlue*)){
        newItem = new GravityGlue();
    } else if (item_typeid == typeid(MouseTracking*)){
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

Behavior* Items_Factory::create_behavior(string item_name){

    Behavior* newItem = (Behavior*)NULL;

    if (item_name.compare("GravityGlue") == 0){
        newItem = new GravityGlue();
    } else if (item_name.compare("MouseTracking") == 0){
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

Interaction* Items_Factory::create_interaction(const type_info& item_typeid){

    Interaction* newItem = (Interaction*)NULL;

    if (item_typeid == typeid(Electrical_Repulsion*)){
        newItem = new Electrical_Repulsion();
    } else if (item_typeid == typeid(Electrical_Attraction*)){
        newItem = new Electrical_Attraction();
    } else if (item_typeid == typeid(Wave_Source*)){
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

Interaction* Items_Factory::create_interaction(string item_name){

    Interaction* newItem = (Interaction*)NULL;

    if (item_name.compare("Electrical_Repulsion") == 0){
        newItem = new Electrical_Repulsion();
    } else if (item_name.compare("Electrical_Attraction") == 0){
        newItem = new Electrical_Attraction();
    } else if (item_name.compare("WaveSource") == 0){
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
