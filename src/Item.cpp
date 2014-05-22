#include "testApp.h"

Item::Item(){
    isAlive = true;
    isActive = true;
    set_name(get_type_name());
}

Item :: ~Item(){
    /* delete added variables. */
}

const type_info& Item::get_typeid(){
    return typeid(this);
}

string Item::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

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

void   Item::iterate_attribute(string attr_name, bool forward){}

void   Item :: setup(){}

void   Item :: run(){}

