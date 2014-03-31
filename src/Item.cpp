#include "testApp.h"

Item::Item(){
    isAlive = true;
    isActive = true;
}

//Item :: Item (World* _world){
//    Item();
//    //set_world(_world);
//    //add_bool("is_alive",&isAlive);
//}

Item :: ~Item(){}

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

void   Item::change_bool_attr(bool_attr& _attr){
    set_bool(_attr.name,_attr.value);
}

void   Item::change_int_attr(int_attr& attr){
    set_int(attr.name,attr.value);
}

void   Item::change_float_attr(float_attr& attr){
    set_float(attr.name,attr.value);
}

void   Item::change_ofVec3f_attr(ofVec3f_attr& attr){
    set_ofVec3f(attr.name,attr.value);
}

void   Item::change_ofColor_attr(ofColor_attr& attr){
    set_ofColor(attr.name,attr.value);
}

void   Item::add_bool_listener(ofEvent<bool_attr>* event){
    ofAddListener(*event, this ,& Item::change_bool_attr);
}

void   Item::add_int_listener(ofEvent<int_attr>* event){
    ofAddListener(*event, this ,& Item::change_int_attr);
}

void   Item::add_float_listener(ofEvent<float_attr>* event){
    ofAddListener(*event, this ,& Item::change_float_attr);
}

void   Item::add_ofVec3f_listener(ofEvent<ofVec3f_attr>* event){
    ofAddListener(*event, this ,& Item::change_ofVec3f_attr);
}

void   Item::add_ofColor_listener(ofEvent<ofColor_attr>* event){
    ofAddListener(*event, this ,& Item::change_ofColor_attr);
}

//void   Item::add_listener(ofEvent<bool_attr>& bool_event){
//    ofAddListener(bool_event, this ,& Item::change_bool_attr);
//    /*ofAddListener(event object, callback object,callback function)*/
//    //ofAddListener(controller.iterate_variable,this,&iterate_attribute);}
//}

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

void   Item :: setup(){}

void   Item :: run(){}


