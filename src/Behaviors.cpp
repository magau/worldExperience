#include "testApp.h"

Behavior::Behavior() : Action(){}

const type_info& Behavior::get_typeid() {
    return typeid(this);
}

GravityGlue::GravityGlue() : Behavior(){
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

const type_info& GravityGlue::get_typeid() {
    return typeid(this);
}

void GravityGlue::setup(Particle* _host_particle){
    ofVec3f var_value = _host_particle->locat;
    _host_particle->set<ofVec3f>("loc", var_value, this);
}

void GravityGlue::setup(){
    Action::setup();
}

void GravityGlue::free(){
    PointersVector<Particle*>::iterator iter_particle;
    for ( iter_particle = get_tag()->particles.begin();
          iter_particle < get_tag()->particles.end();
          iter_particle++){
        free(*iter_particle);
    }
}

void GravityGlue::free(Particle* _host_particle){
    _host_particle->erase<ofVec3f>("loc",this);
}

void GravityGlue::run(Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;
    ofVec3f* _locat;
    _locat = _host_particle->get<ofVec3f>("loc",this);

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = _locat->distance(*_host_particle->get<ofVec3f>("loc"));

#ifdef USE_UNORDERED_MAP
    //dx = _host_particle->get_ofVec3f("loc")->x - _locat->x;
    //dy = _host_particle->get_ofVec3f("loc")->y - _locat->y;
    ofVec3f* _host_loc = _host_particle->get<ofVec3f>("loc");
    dx = _host_loc->x - _locat->x;
    dy = _host_loc->y - _locat->y;
#else
    dx = _host_particle->locat.x - _locat->x;
    dy = _host_particle->locat.y - _locat->y;
#endif

    if (dist < min_dist) dist = min_dist;

    acc = weight / pow(dist,2);

#ifdef USE_UNORDERED_MAP
    ofVec3f* _host_acc = _host_particle->get<ofVec3f>("acc");
    _host_acc->x += - dx * acc;
    _host_acc->y += - dy * acc;
    //_host_particle->get_ofVec3f("acc")->x += - dx * acc;
    //_host_particle->get_ofVec3f("acc")->y += - dy * acc;
#else
    _host_particle->accel.x += - dx * acc;
    _host_particle->accel.y += - dy * acc;
#endif

    //Do not aplly relaxation at the bounthery wall  
    //int offset = _host_particle->rad;
    //if (_host_particle->locat.x > offset &&
    //    _host_particle->locat.x < ofGetWindowWidth() - offset &&
    //    _host_particle->locat.y > offset &&
    //    _host_particle->locat.y < ofGetWindowHeight() - offset ){

#ifdef USE_UNORDERED_MAP
    //_host_particle->set_float("relax_fact",0.7);
    _host_particle->set<float>("relax",0.7);
#else
    _host_particle->relax_fact = 0.7;
#endif
    //}
}

MouseTracking::MouseTracking() : Behavior(){
}

const type_info& MouseTracking::get_typeid() {
    return typeid(this);
}

void MouseTracking::run(Particle* _host_particle){
#ifdef USE_MOUSE_THREAD
    extern getMouseLocation mouse;
    _host_particle->veloc.x = mouse.x - _host_particle->locat.x;
    _host_particle->veloc.y = mouse.y - _host_particle->locat.y;
#else
    _host_particle->veloc.x = ofGetMouseX() - _host_particle->locat.x;
    _host_particle->veloc.y = ofGetMouseY() - _host_particle->locat.y;
#endif
}
