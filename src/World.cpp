#include "testApp.h"

World :: World() {
}

Particle* World::create_particle(string iName, bool isActive){
/*
 * Create a new particle. Add created particle to the world particles
 * container and if "isActive" is setted true run the
 * activate_particle method (set true the "isActive" 
 * attribute of the particle and run
 * the "setup" method of the particle).
 */
    Particle* newParticle = nature.create_particle(iName);
    if(newParticle->get_world() != this){
        newParticle->set_world(this);
        particles.add(newParticle);
    }
    if (isActive) {
        activate_particle(newParticle);
    } else if (!isActive) {
        newParticle->set_active_state(false);
    }

    return newParticle;
}

void World::activate_particle(Particle* particle){
    // Set the "isActive" attribute true and run 
    // the setup method for the particle.
    particle->set_active_state(true);
    particle->setup(); 
}

void World :: remove_particle(Particle* particle){
    // Remove the particle from the world.particles container.
    particles.erase_itemById(particle->get_id());
}

/*
 * Implementation in the furute of the "get" and "remove"
 * methods by name and id, for the particles and actions.
 * ...
 */

Action* World::create_action(string iName){
    //create newAction.
    Action* newAction = nature.create_action(iName);
    newAction->set_world(this);
    return newAction;
}


Behavior* World::create_behavior(string iName){
    //create newBehavior.
    Behavior* newBehavior = nature.create_behavior(iName);
    newBehavior->set_world(this);

    return newBehavior;
}


Interaction* World::create_interaction(string iName){
    //create newInteraction.
    Interaction* newInteraction = nature.create_interaction(iName);
    newInteraction->set_world(this);
    return newInteraction;
}

Tag* World::create_tag(string iName){
    //create a new tag in the World's tags container.
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

void World :: remove_tag(Tag* tag){
    tags.erase_itemById(tag->get_id());
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

void World::draw(){
    for(vector<Particle*>::iterator iter_particle = particles.itemsVector.begin();
                                    iter_particle != particles.itemsVector.end();
                                    iter_particle++){
        (*iter_particle)->display();
    }
}



Particle* Items_Fabric::create_particle(string item_name){

    Particle* newItem = (Particle*)NULL;

    if (item_name.compare("P_Base") == 0){
        newItem = new Particle();
    } else if (item_name.compare("P_Circle") == 0){
        newItem = new Circle();
    } else if (item_name.compare("MP_RegGrid") == 0){
        newItem = new RegularGrid_MP();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}

Action* Items_Fabric::create_action(string item_name){

    Action* newItem = (Action*)NULL;

    if (item_name.compare("B_GravityGlue") == 0){
        newItem = new GravityGlue();
    } else if (item_name.compare("B_MouseTracking") == 0){
        newItem = new MouseTracking();
    } else if (item_name.compare("I_ElectRepulsion") == 0){
        newItem = new Electrical_Repulsion();
    } else if (item_name.compare("I_ElectAttraction") == 0){
        newItem = new Electrical_Attraction();
    } else if (item_name.compare("I_WaveSource") == 0){
        newItem = new Wave_Source();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}

Behavior* Items_Fabric::create_behavior(string item_name){

    Behavior* newItem = (Behavior*)NULL;

    if (item_name.compare("B_GravityGlue") == 0){
        newItem = new GravityGlue();
    } else if (item_name.compare("B_MouseTracking") == 0){
        newItem = new MouseTracking();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}

Interaction* Items_Fabric::create_interaction(string item_name){

    Interaction* newItem = (Interaction*)NULL;

    if (item_name.compare("I_ElectRepulsion") == 0){
        newItem = new Electrical_Repulsion();
    } else if (item_name.compare("I_ElectAttraction") == 0){
        newItem = new Electrical_Attraction();
    } else if (item_name.compare("I_WaveSource") == 0){
        newItem = new Wave_Source();
    }
    /*
     .
     .
     .
        Add new item types
    */


    return newItem;
}
