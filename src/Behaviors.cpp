#include "testApp.h"

Behavior::Behavior() : Action(){
    set_name(get_type_name());
}

const type_info& Behavior::get_typeid() {
    return typeid(this);
}

string Behavior::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};


GravityGlue::GravityGlue() : Behavior(){
    set_name(get_type_name());
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    weight_fac = Item_Parameter<float>(0.1, pair<float,float> (0,5));
    set_variable("weight",&weight_fac,IP_FLOAT);
}

const type_info& GravityGlue::get_typeid() {
    return typeid(this);
}

string GravityGlue::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

void GravityGlue::setup(Particle* _host_particle){
    _host_particle->set_item_parameter<ofVec3f>("loc", *_host_particle->get_item_parameter<ofVec3f>("loc"), this);
}

//void GravityGlue::setup(){
//    Action::setup();
//}

void GravityGlue::free(){
    PointersVector<Particle*>::iterator iter_particle;
    for ( iter_particle = get_tag()->particles.begin();
          iter_particle < get_tag()->particles.end();
          iter_particle++){
        free(*iter_particle);
    }
}

void GravityGlue::free(Particle* _host_particle){
    _host_particle->erase_variable("loc",this);
}

void GravityGlue::run(Particle* _host_particle){
    float dist,dx,dy,weight,acc;//weight_fact,
    ofVec3f* glue_loc = &_host_particle->get_item_parameter<ofVec3f>("loc",this)->value;
    ofVec3f* _host_loc = &_host_particle->get_item_parameter<ofVec3f>("loc")->value;
    ofVec3f* _host_acc = &_host_particle->get_item_parameter<ofVec3f>("acc")->value;
    //cout << "p name:" << _host_particle->get_type_name()<< endl;
    //_host_particle->print_shared_var_names();


    //weight_fact = get_item_parameter<float>("weigt")->value;
    //weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist * weight_fac.value;
    //weight = max_dist*weight_fact;

    dist = glue_loc->distance(*_host_loc);

    //dx = _host_particle->get_ofVec3f("loc")->x - glue_loc->x;
    //dy = _host_particle->get_ofVec3f("loc")->y - glue_loc->y;
    dx = _host_loc->x - glue_loc->x;
    dy = _host_loc->y - glue_loc->y;

    if (dist < min_dist) dist = min_dist;

    acc = weight / pow(dist,2);

    _host_acc->x += - dx * acc;
    _host_acc->y += - dy * acc;

    //Do not aplly relaxation at the bounthery wall  
    //int offset = _host_particle->rad;
    //if (_host_particle->locat.x > offset &&
    //    _host_particle->locat.x < ofGetWindowWidth() - offset &&
    //    _host_particle->locat.y > offset &&
    //    _host_particle->locat.y < ofGetWindowHeight() - offset ){

    //_host_particle->set_float("relax_fact",0.7);
    _host_particle->set_item_parameter<float>("relax",0.7);
    //}
}

MouseTracking::MouseTracking() : Behavior(){
    set_name(get_type_name());
}

string MouseTracking::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

const type_info& MouseTracking::get_typeid() {
    return typeid(this);
}

void MouseTracking::run(Particle* _host_particle){
    ofVec3f* _host_vel = &_host_particle->get_item_parameter<ofVec3f>("vel")->value;
    ofVec3f* _host_loc = &_host_particle->get_item_parameter<ofVec3f>("loc")->value;
#ifdef USE_MOUSE_THREAD
    extern getMouseLocation mouse;
    _host_vel->x = mouse.x - _host_loc->x;
    _host_vel->y = mouse.y - _host_loc->y;
#else
    _host_vel->x = ofGetMouseX() - _host_loc->x;
    _host_vel->y = ofGetMouseY() - _host_loc->y;
#endif
}
