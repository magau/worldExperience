#include "testApp.h"

World :: World() {}

Tag* World::create_tag(string iName){
    //create a new tag in the tags container of the world.
    Tag* newTag = new Tag(this);
    tags.add(newTag);

    if (iName.size() != 0) {
        newTag->set_name(iName) ;
    } else {
        char tmp[7];
        sprintf(tmp,"T_%04d",newTag->get_id());
        newTag->set_name(tmp);
    }
    return newTag;
}

Action* World::create_action(string iName){
    //create newAction.
    //Action* newAction = actions.create_itemByName(iName);
    Action* newAction = nature.create_action(iName);
    newAction->set_world(this);
    //If the action acts over the world since its creation, it only
    //can be done after seting up the world. this is the purpose for setup function
    if(newAction->is_active())
        newAction->setup(); 
    return newAction;
}


Behavior* World::create_behavior(string iName){
    //create newBehavior.
    //Behavior* newBehavior = behaviors.create_itemByName(iName);
    Behavior* newBehavior = nature.create_behavior(iName);
    newBehavior->set_world(this);
    //If the behavior acts over the world since its creation, it only
    //can be done after seting up the world. this is the purpose for setup function
    if(newBehavior->is_active())
        newBehavior->setup(); 
    return newBehavior;
}


Interaction* World::create_interaction(string iName){
    //create newInteraction.
    //Interaction* newInteraction = interactions.create_itemByName(iName);
    Interaction* newInteraction = nature.create_interaction(iName);
    newInteraction->set_world(this);
    //If the interaction acts over the world since its creation, it only
    //can be done after seting up the world. this is the purpose for setup function
    if(newInteraction->is_active())
        newInteraction->setup(); 
    return newInteraction;
}

Particle* World::create_particle(string iName){
    //create newParticle add particle to world.particles
    Particle* newParticle = particles.create_itemByName(iName);
    newParticle->set_world(this);
    //If the particle acts over the world since its creation, it only
    //can be done after seting up the world. this is the purpose for setup function
    if(newParticle->is_active())
        newParticle->setup(); 
    return newParticle;
}

void World::add_particle(Particle* particle){
    // At the moment the particles instantiated at the "world.create_particle" are
    // already added. (change in future...)
    if(particle->get_world()==(World*)NULL){// for future usase...
        particle->set_world(this);
        particles.add(particle);
    }
    //If the particle constructor sets false the default value of the "isAlive" variable.
    //Used to preset the particle members.
    if(!particle->is_active()){
        particle->set_live_state(true);
        particle->setup(); 
    }
}

Particles_Container* World :: update(){

    for(vector<Tag*>::iterator iter_tag = tags.itemsVector.begin();
                                    iter_tag != tags.itemsVector.end();
                                    iter_tag++){
        (*iter_tag)->run();
    }

    // This "for" statement is iterated in reverse mode to avoid core 
    // dump in case of the "remove_particle" function is called.
    for(vector<Particle*>::iterator iter_particle = particles.itemsVector.end() - 1;
                                    iter_particle >= particles.itemsVector.begin();
                                    iter_particle--) {
        if(!(*iter_particle)->is_alive()) {
            remove_particle(*iter_particle);
        } else if ((*iter_particle)->is_active()) {
            (*iter_particle)->run();
        }
    }
    return &(particles);
}

void World :: remove_tag(Tag* tag){
    tags.erase_itemById(tag->get_id());
}

void World :: remove_particle(Particle* particle){
    // Remove the particle from the world.particles container.
    particles.erase_itemById(particle->get_id());
}

void World::draw(){
    for(vector<Particle*>::iterator iter_particle = particles.itemsVector.begin();
                                    iter_particle != particles.itemsVector.end();
                                    iter_particle++){
        (*iter_particle)->display();
    }
}

