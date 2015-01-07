#include "testApp.h"

Action::Action() : Item(){}
void Action::add_tag(Tag* tag){_tag = tag;}
Tag* Action::get_tag(){return _tag;}
void Action::setup_particle(Particle* particle){}
void Action::free(Particle* particle){}

void Action::setup(){
    if (get_tag() != (Tag*)NULL) {
        PointersVector<Particle*>* particles = &(get_tag()->particles);
        PointersVector<Particle*>::iterator iter_particle;
        for ( iter_particle = particles->begin();
              iter_particle != particles->end();
              iter_particle++){
            setup_particle(*iter_particle);
        }
    }
}

void Action::free(){
    if (get_tag() != (Tag*)NULL) {
        PointersVector<Particle*>* particles = &(get_tag()->particles);
        PointersVector<Particle*>::iterator iter_particle;
        for ( iter_particle = particles->begin();
              iter_particle != particles->end();
              iter_particle++){
            free(*iter_particle);
        }
    }
}

void Action::update_particle(Particle* _host_particle){}

void Action::update(){
    PointersVector<Particle*>::iterator iter_particle;
    if (get_tag()->particles.size() > 0) {
        
        for (iter_particle = get_tag()->particles.end() - 1;
             iter_particle >= get_tag()->particles.begin();
             iter_particle--){

             if ((*iter_particle)->get_item_parameter<bool>("is_active")->value){
                 update_particle(*iter_particle);
             } else {
                 cout << "skip behavior :" << get_type_name() << endl;
             }
         }
        
    }
}

Particle* Action::create_particle(string p_name){
    Particle* particle = get_world()->create_particle(p_name);
    get_tag()->add_particle(particle);
    return particle;
};

void Action::erase_particle(Particle* particle){
    //particle->is_active = false;
    //particle->is_alive = false;
    get_world()->remove_particle(particle);
};
