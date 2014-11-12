#include "testApp.h"

Action::Action() : Item(){}
void Action::add_tag(Tag* tag){_tag = tag;}
Tag* Action::get_tag(){return _tag;}
void Action::setup(Particle* particle){}
void Action::free(Particle* particle){}

void Action::setup(){
    if (get_tag() != (Tag*)NULL) {
        PointersVector<Particle*>* particles = &(get_tag()->particles);
        PointersVector<Particle*>::iterator iter_particle;
        for ( iter_particle = particles->begin();
              iter_particle != particles->end();
              iter_particle++){
            setup(*iter_particle);
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

void Action::run(Particle* _host_particle){}

void Action::run(){
    PointersVector<Particle*>::iterator iter_particle;
    PointersVector<Action*>::iterator iter_action;
    for (iter_particle = get_tag()->particles.begin();
	 iter_particle != get_tag()->particles.end();
         iter_particle++){
         run(*iter_particle);
    }
}
