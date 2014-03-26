#include "testApp.h"

Action::Action() : Item(){}
void Action::add_tag(Tag* tag){_tag = tag;}
Tag* Action::get_tag(){return _tag;}
void Action::setup(Particle* particle){}
void Action::free(Particle* particle){}
void Action::setup(){}
void Action::free(){}

void Action::run(Particle* _host_particle){}

void Action::run(){
    vector<Particle*>::iterator iter_particle;
    vector<Action*>::iterator iter_action;
    for (iter_particle = get_tag()->particles.itemsVector.begin();
	 iter_particle != get_tag()->particles.itemsVector.end();
         iter_particle++){
         run(*iter_particle);
    }
}