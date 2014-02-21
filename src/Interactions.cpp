#include "testApp.h"

#define USE_UNORDERED_MAP

Interaction::Interaction() : Action(){}
void Interaction::interact(Particle* actuated_particle, Particle* _host_particle){}
void Interaction::run(Particle* _host_particle){
    vector<Tag*>::iterator iter_tag;
    vector<Particle*>::iterator iter_particle;
    for (iter_tag = actuated_tags.itemsVector.begin();
         iter_tag < actuated_tags.itemsVector.end();
         iter_tag++ ){

        for (iter_particle = (*iter_tag)->particles.itemsVector.begin();
             iter_particle != (*iter_tag)->particles.itemsVector.end();
             iter_particle++){

            interact(*iter_particle, _host_particle);
        }
    }
}

void Interaction::add_actuated_tag(Tag* tag){
   actuated_tags.add(tag, false); 
}

void Interaction::remove_actuated_tag(Tag* tag){
   actuated_tags.pop_itemById(tag->id);
}

Electrical_Repulsion::Electrical_Repulsion() : Interaction() {
    set_name("I_ElectRepulsion");
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void Electrical_Repulsion::interact(Particle* actuated_particle, Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.2;
    //weight_fact = 0.25;

    weight = max_dist*weight_fact;

    dist = _host_particle->locat.distance(actuated_particle->locat);

#ifdef USE_UNORDERED_MAP
    dx = actuated_particle->get_ofVec3f("loc")->x - _host_particle->get_ofVec3f("loc")->x;
    dy = actuated_particle->get_ofVec3f("loc")->y - _host_particle->get_ofVec3f("loc")->y;
#else
    dx = actuated_particle->locat.x - _host_particle->locat.x;
    dy = actuated_particle->locat.y - _host_particle->locat.y;
#endif

    acc = weight / pow(dist,2);

#ifdef USE_UNORDERED_MAP
    actuated_particle->get_ofVec3f("acc")->x += dx * acc;
    actuated_particle->get_ofVec3f("acc")->y += dy * acc;
#else
    actuated_particle->accel.x += dx * acc;
    actuated_particle->accel.y += dy * acc;
#endif

    ////Do not aplly relaxation at the bounthery wall  
    //int offset = actuated_particle->rad;
    //if (actuated_particle->locat.x > offset &&
    //    actuated_particle->locat.x < ofGetWindowWidth() - offset &&
    //    actuated_particle->locat.y > offset &&
    //    actuated_particle->locat.y < ofGetWindowHeight() - offset ){

    //    actuated_particle->relax_fact = 0.7;
    //}
} 

Electrical_Attraction::Electrical_Attraction() : Interaction(){
    set_name("I_ElectAttraction");
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void Electrical_Attraction::interact(Particle* actuated_particle, Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.1;
    min_dist = 40;
    weight = max_dist*weight_fact;

    dist = _host_particle->locat.distance(actuated_particle->locat);
    dx = actuated_particle->locat.x - _host_particle->locat.x;
    dy = actuated_particle->locat.y - _host_particle->locat.y;

    if (dist < min_dist) dist = min_dist;
    acc = weight / pow(dist,2);

    actuated_particle->accel.x += - dx * acc;
    actuated_particle->accel.y += - dy * acc;

    // //Over relaxation
    // if (dist == min_dist) {
    //     actuated_particle->relax_fact *= 0.95;
    //     //actuated_particle->relax_fact *= 0.7;
    // }
}

Wave_Source :: Wave_Source() : Interaction(){
    set_name("I_WaveSource");
    min_dist=80;
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    weight_fact = 0.05;
    weight = max_dist*weight_fact;
    timer = 0;
    wave_speed = 5;
}

void Wave_Source :: run(Particle* _host_particle){
    Interaction::run(_host_particle);
    timer += wave_speed;
}

void Wave_Source :: interact(Particle* actuated_particle, Particle*_host_particle){
    float dist,acc,size_ds;
    ofPoint ds, dir, wavePos;

    ds.x = actuated_particle->locat.x - _host_particle->locat.x;
    ds.y = actuated_particle->locat.y - _host_particle->locat.y;
    size_ds = ofVec3f(0).distance(ds);
    dir.set(ds.x/size_ds,ds.y/size_ds);
    
    wavePos.set(_host_particle->locat.x + timer * dir.x, _host_particle->locat.y + timer * dir.y);
    dist = actuated_particle->locat.distance(wavePos);
    if (dist > max_dist) {
        _host_particle->set_live_state(false);
        set_live_state(false);
    } else {

        if (dist < min_dist) dist = min_dist;

        acc = weight / pow(dist,2);

        ds.x = actuated_particle->locat.x - wavePos.x ;
        ds.y = actuated_particle->locat.y - wavePos.y;
        actuated_particle->accel.x += ds.x * acc;
        actuated_particle->accel.y += ds.y * acc;

//        cout<<"dir.x:"<<dir.x<<" wavePos.x:"<<wavePos.x<<" ds.x:"<<ds.x<<" dist:"<<dist<<endl;

        ////Do not aplly relaxation at the bounthery wall  
        //int offset = actuated_particle->rad;
        //if (actuated_particle->locat.x > offset &&
        //    actuated_particle->locat.x < ofGetWindowWidth() - offset &&
        //    actuated_particle->locat.y > offset &&
        //    actuated_particle->locat.y < ofGetWindowHeight() - offset ){

        //    actuated_particle->relax_fact = 0.9;
        //    //actuated_particle->relax_fact = 0.7;
        //}
    } 
}
