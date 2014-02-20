#include "testApp.h"

Item::Item(){
    isAlive = true;
    isActive = true;
}

Item :: Item (World* _world){
    Item();
    set_world(_world);
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

void   Item::add_bool(string var_name, bool var_val){
    boolPtr_map[var_name] = new bool(var_val); 
}

void   Item::set_bool(string var_name, bool var_val){
    *(boolPtr_map[var_name]) = var_val; 
}

bool*   Item::get_bool(string var_name){
    return boolPtr_map[var_name];
}

void   Item::delete_bool(string var_name){
    delete boolPtr_map[var_name]; 
    boolPtr_map.erase(var_name);    
}

void   Item::add_int(string var_name, int var_val){
    intPtr_map[var_name] = new int(var_val); 
}

void   Item::set_int(string var_name, int var_val){
    *(intPtr_map[var_name]) = var_val; 
}

int*   Item::get_int(string var_name){
    return intPtr_map[var_name];
}

void   Item::delete_int(string var_name){
    delete intPtr_map[var_name]; 
    intPtr_map.erase(var_name);    
}

void   Item::add_float(string var_name, float var_val){
    floatPtr_map[var_name] = new float(var_val); 
}

void   Item::set_float(string var_name, float var_val){
    *(floatPtr_map[var_name]) = var_val; 
}

float*   Item::get_float(string var_name){
    return floatPtr_map[var_name];
}

void   Item::delete_float(string var_name){
    delete floatPtr_map[var_name]; 
    floatPtr_map.erase(var_name);    
}

void   Item::add_ofColor(string var_name, ofColor var_val){
    ofColorPtr_map[var_name] = new ofColor(var_val); 
}

void   Item::set_ofColor(string var_name, ofColor var_val){
    *(ofColorPtr_map[var_name]) = var_val; 
}

ofColor*   Item::get_ofColor(string var_name){
    return ofColorPtr_map[var_name];
}

void   Item::delete_ofColor(string var_name){
    delete ofColorPtr_map[var_name]; 
    ofColorPtr_map.erase(var_name);    
}

void   Item::add_ofVec3f(string var_name, ofVec3f var_val){
    ofVec3fPtr_map[var_name] = new ofVec3f(var_val); 
}

void   Item::set_ofVec3f(string var_name, ofVec3f var_val){
    *(ofVec3fPtr_map[var_name]) = var_val; 
}

ofVec3f*   Item::get_ofVec3f(string var_name){
    return ofVec3fPtr_map[var_name];
}

void   Item::delete_ofVec3f(string var_name){
    delete ofVec3fPtr_map[var_name]; 
    ofVec3fPtr_map.erase(var_name);    
}

void   Item::free(Item* _host_item){}

void   Item :: setup(){}

void   Item :: run(){}

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

Action* Items_Fabric::create_action(string item_name){

    Action* newItem = (Action*)NULL;

    if (item_name.compare("B_GravityGlue") == 0){
        newItem = new GravityGlue();
    } else if (item_name.compare("B_MouseTracking") == 0){
        newItem = new MouseTracking();
    } else if (item_name.compare("I_ElectRepulsion") == 0){
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
