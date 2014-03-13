#include "testApp.h"

Behavior::Behavior() : Action(){}

GravityGlue::GravityGlue() : Behavior(){
    set_name("B_GravityGlue");
    location_key = get_name()+"_loc";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void GravityGlue::setup(Particle* _host_particle){
    ofVec3f var_value = _host_particle->locat;
    _host_particle->add_ofVec3f(location_key, var_value);
}

void GravityGlue::setup(){
    vector<Particle*> particles = get_tag()->particles.get_items();
    vector<Particle*>::iterator iter_particle;
    for ( iter_particle = particles.begin();
          iter_particle < particles.end();
          iter_particle++){
        setup(*iter_particle);
    }
}

void GravityGlue::free(){
    vector<Particle*>::iterator iter_particle;
    for ( iter_particle = get_tag()->particles.itemsVector.begin();
          iter_particle < get_tag()->particles.itemsVector.end();
          iter_particle++){
        free(*iter_particle);
    }
}

void GravityGlue::free(Particle* _host_particle){
    _host_particle->delete_ofVec3f(location_key);
}

void GravityGlue::run(Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;
    ofVec3f* _locat;
    _locat = _host_particle->get_ofVec3f(location_key);

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = _locat->distance(_host_particle->locat);

#ifdef USE_UNORDERED_MAP
    dx = _host_particle->get_ofVec3f("loc")->x - _locat->x;
    dy = _host_particle->get_ofVec3f("loc")->y - _locat->y;
#else
    dx = _host_particle->locat.x - _locat->x;
    dy = _host_particle->locat.y - _locat->y;
#endif

    if (dist < min_dist) dist = min_dist;

    acc = weight / pow(dist,2);

#ifdef USE_UNORDERED_MAP
    _host_particle->get_ofVec3f("acc")->x += - dx * acc;
    _host_particle->get_ofVec3f("acc")->y += - dy * acc;
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
    _host_particle->set_float("relax_fact",0.7);
#else
    _host_particle->relax_fact = 0.7;
#endif
    //}
}

MouseTracking::MouseTracking() : Behavior(){
    set_name("B_MouseTracking"); 
}

void MouseTracking::run(Particle* _host_particle){
    //extern getMouseLocation mouse;
    //_host_particle->veloc.x = mouse.x - _host_particle->locat.x;
    //_host_particle->veloc.y = mouse.y - _host_particle->locat.y;
    _host_particle->veloc.x = ofGetMouseX() - _host_particle->locat.x;
    _host_particle->veloc.y = ofGetMouseY() - _host_particle->locat.y;
}
