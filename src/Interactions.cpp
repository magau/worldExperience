#include "testApp.h"

Interaction::Interaction() : Action() {
}

string Interaction::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

const type_info& Interaction::get_typeid() {
    return typeid(this);
}

void Interaction::interact(Particle* actuated_particle, Particle* _host_particle){}

void Interaction::run(Particle* _host_particle){
    PointersVector<Tag*>::iterator iter_tag;
    PointersVector<Particle*>::iterator iter_particle;
    for (iter_tag = actuated_tags.begin();
         iter_tag < actuated_tags.end();
         iter_tag++ ){

        for (iter_particle = (*iter_tag)->particles.begin();
             iter_particle != (*iter_tag)->particles.end();
             iter_particle++){

            interact(*iter_particle, _host_particle);
        }
    }
}

void Interaction::add_actuated_tag(Tag* tag){
   actuated_tags.push_back(tag); 
}

void Interaction::remove_actuated_tag(Tag* tag){
   actuated_tags.erase_item_by_id(tag->id);
}

Electrical_Repulsion::Electrical_Repulsion() : Interaction() {
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

string Electrical_Repulsion::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

const type_info& Electrical_Repulsion::get_typeid() {
    return typeid(this);
}

void Electrical_Repulsion::add_listener(string attr_name) {
    //ofEvent<bool>* new_event = new ofEvent<bool>;
    //bool_events.add(new_event); 
    //ofAddListener(_tag->bool_event,this,&iterate_attribute(attr_name,b));}
}

void Electrical_Repulsion::interact(Particle* actuated_particle, Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.2;
    //weight_fact = 0.25;

    weight = max_dist*weight_fact;

    ofVec3f* actuated_loc = &actuated_particle->get<ofVec3f>("loc")->value;
    ofVec3f* _host_loc = &_host_particle->get<ofVec3f>("loc")->value;
    dist = _host_loc->distance(*actuated_loc);

#ifdef USE_UNORDERED_MAP
    dx = actuated_loc->x - _host_loc->x;
    dy = actuated_loc->y - _host_loc->y;
#else
    dx = actuated_loc->x - _host_loc->x;
    dy = actuated_loc->y - _host_loc->y;
#endif

    acc = weight / pow(dist,2);

#ifdef USE_UNORDERED_MAP
    //actuated_particle->get_ofVec3f("acc")->x += dx * acc;
    //actuated_particle->get_ofVec3f("acc")->y += dy * acc;
    ofVec3f* actuated_acc = &actuated_particle->get<ofVec3f>("acc")->value;
    actuated_acc->x += dx * acc;
    actuated_acc->y += dy * acc;
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
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

string Electrical_Attraction::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

const type_info& Electrical_Attraction::get_typeid() {
    return typeid(this);
}

void Electrical_Attraction::interact(Particle* actuated_particle, Particle* _host_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.1;
    min_dist = 40;
    weight = max_dist*weight_fact;

    ofVec3f* actuated_loc = &actuated_particle->get<ofVec3f>("loc")->value;
    ofVec3f* _host_loc = &_host_particle->get<ofVec3f>("loc")->value;

    dist = _host_loc->distance(*actuated_loc);
    dx = actuated_loc->x - _host_loc->x;
    dy = actuated_loc->y - _host_loc->y;

    if (dist < min_dist) dist = min_dist;
    acc = weight / pow(dist,2);

    ofVec3f* actuated_acc = &actuated_particle->get<ofVec3f>("acc")->value;
    actuated_acc->x += - dx * acc;
    actuated_acc->y += - dy * acc;

    // //Over relaxation
    // if (dist == min_dist) {
    //     actuated_particle->relax_fact *= 0.95;
    //     //actuated_particle->relax_fact *= 0.7;
    // }
}

Wave_Source::Wave_Source() : Interaction(){
    min_dist=80;
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    weight_fact = 0.05;
    weight = max_dist*weight_fact;
    timer = 0;
    wave_speed = 5;
}

string Wave_Source::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

const type_info& Wave_Source::get_typeid() {
    return typeid(this);
}

void Wave_Source :: run(Particle* _host_particle){
    Interaction::run(_host_particle);
    timer += wave_speed;
}

void Wave_Source :: interact(Particle* actuated_particle, Particle*_host_particle){
    float dist,acc,size_ds;
    ofPoint ds, dir, wavePos;

    ofVec3f* actuated_loc = &actuated_particle->get<ofVec3f>("loc")->value;
    ofVec3f* _host_loc = &_host_particle->get<ofVec3f>("loc")->value;

    ds.x = actuated_loc->x - _host_loc->x;
    ds.y = actuated_loc->y - _host_loc->y;
    size_ds = ofVec3f(0).distance(ds);
    dir.set(ds.x/size_ds,ds.y/size_ds);
    
    wavePos.set(_host_loc->x + timer * dir.x, _host_loc->y + timer * dir.y);
    dist = actuated_loc->distance(wavePos);
    if (dist > max_dist) {
        _host_particle->set<bool>("is_alive",Item_Parameter<bool>(false));
    } else {

        if (dist < min_dist) dist = min_dist;

        acc = weight / pow(dist,2);

        ds.x = actuated_loc->x - wavePos.x ;
        ds.y = actuated_loc->y - wavePos.y;
        ofVec3f* actuated_acc = &actuated_particle->get<ofVec3f>("acc")->value;
        actuated_acc->x += ds.x * acc;
        actuated_acc->y += ds.y * acc;

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
