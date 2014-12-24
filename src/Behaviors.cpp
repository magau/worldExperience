#include "testApp.h"

Behavior::Behavior() : Action(){
    set_name(get_type_name());
}

const type_info& Behavior::get_typeid() {
    return typeid(this);
}

GravityGlue::GravityGlue() : Behavior(){
    set_name(get_type_name());
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    weight_fac = Item_Parameter<float>(0.1, pair<float,float> (0,5));
    set_variable("weight",&weight_fac,IP_FLOAT);
}

const type_info& GravityGlue::get_typeid() {
    return typeid(this);
}

void GravityGlue::setup_particle(Particle* _host_particle){
    //_host_particle->set_variable("loc",*_host_particle->get_item_parameter<ofVec3f>("loc"),this);
    _host_particle->set_variable("loc",*(Item_Parameter<ofVec3f>*)(_host_particle->get_variable("loc").value),this);
}

//void GravityGlue::setup(){
//    Action::setup();
//}

void GravityGlue::free(){
    PointersVector<Particle*>::iterator iter_particle;
    for ( iter_particle = get_tag()->particles.begin();
          iter_particle != get_tag()->particles.end();
          iter_particle++){
        free(*iter_particle);
    }
}

void GravityGlue::free(Particle* _host_particle){
    cout << "call GravityGlue::free(Particle)" << endl;
    _host_particle->erase_variable("loc",this);
    cout << "Particle free." << endl;
}

void GravityGlue::update_particle(Particle* _host_particle){
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

    //_host_particle->set_item_parameter<float>("relax",0.7);
    _host_particle->set_variable("relax",Item_Parameter<float>(0.7));
    //}
}

MouseTracking::MouseTracking() : Behavior(){
    set_name(get_type_name());

    #ifdef USE_MOUSE_THREAD
    startThread(true);
    #endif
}

MouseTracking::~MouseTracking() {
    #ifdef USE_MOUSE_THREAD
    stopThread();
    #endif
}

const type_info& MouseTracking::get_typeid() {
    return typeid(this);
}

void MouseTracking::update_particle(Particle* _host_particle){
    ofVec3f* _host_vel = &_host_particle->get_item_parameter<ofVec3f>("vel")->value;
    ofVec3f* _host_loc = &_host_particle->get_item_parameter<ofVec3f>("loc")->value;
#ifdef USE_MOUSE_THREAD
    //extern getMouseLocation mouse;
    _host_vel->x = x - _host_loc->x;
    _host_vel->y = y - _host_loc->y;
#else
    _host_vel->x = ofGetMouseX() - _host_loc->x;
    _host_vel->y = ofGetMouseY() - _host_loc->y;
#endif
}

OscTracker::OscTracker() : Behavior(){
    set_name(get_type_name());
    //default_particle = "Circle";
    default_particle = "Sphere";
    default_rad = 10;
    set_variable("default",&default_particle,STRING);
    set_variable("osc_msg",&particles_tracker,IP_VECTOR_OF_VEC3F);
}

const type_info& OscTracker::get_typeid() {
    return typeid(this);
}

void OscTracker::update(){

    Item_Parameter_VectorOfofVect3f p_tracker = particles_tracker;
    vector<ofVec3f>::iterator track_it;
    for(track_it = p_tracker.value.begin();
        track_it != p_tracker.value.end();
        track_it++){
        bool is_present = false;
        PointersVector<Particle*>::iterator iter_particle;
        for (iter_particle = get_tag()->particles.begin();
             iter_particle != get_tag()->particles.end();
             iter_particle++){
            if((int)(track_it->z) == *(int*)((*iter_particle)->get_variable("id",this).value)){
                is_present = true;
                break;
            }

        }
        if (!is_present) {
            Particle* particle = create_particle(default_particle);
            particle->set_variable("id",(int)(track_it->z),this);
            particle->set_item_parameter("rad",default_rad);
            particle->set_item_parameter("color",ofColor(255,0,0));
        }
    }

    Action::update();
};

void OscTracker::update_particle(Particle* _host_particle){
    bool is_present = false;
    vector<ofVec3f>::iterator track_it;
    Item_Parameter_VectorOfofVect3f p_tracker = particles_tracker;
    for(track_it = p_tracker.value.begin();
        track_it != p_tracker.value.end();
        track_it++){

        if((int)(track_it->z) == *(int*)(_host_particle->get_variable("id",this).value)){
            is_present = true;

            _host_particle->vel.value.x = (int)track_it->x - _host_particle->loc.value.x;
            _host_particle->vel.value.y = (int)track_it->y - _host_particle->loc.value.y;
            //cout << (_host_particle->loc.value) << endl;
            break;
        }

    }

    if(!is_present){
        erase_particle(_host_particle);
    }
};

void OscTracker::setup_particle(Particle* _host_particle){
};

void OscTracker::free(Particle* _host_particle){
    _host_particle->erase_variable("id",this);
};
