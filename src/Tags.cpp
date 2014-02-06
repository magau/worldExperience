#include "testApp.h"


Tag :: Tag (World* _world){

    name="no_name_tag";
    world = _world;
    isAlive = true;
    isActive = true;
}

Tag :: ~Tag (){
    //cout << "Removing particles, interactions and behaviors from tag." << endl;
    remove_particles(particles.itemsVector);    
    behaviors.erase_all();
    interactions.erase_all();
}

void Tag::remove_particles(vector<Particle*> removed_particles){
    vector<Particle*>::iterator iter_particle;
    for (iter_particle = removed_particles.begin();
         iter_particle < removed_particles.end();
         iter_particle++){
        remove_particle(*iter_particle);
    }

}

void Tag::remove_particle(Particle* particle){
    // Remove the particle from this tag's particles container.
    particles.pop_itemById(particle->id); 

    // Remove this tag from particle's tags container.
    particle->tags.pop_itemById(id);

    // Free the particle variables seted by this tag's behaviors and interactions.
    free_particle_vars(particle);
}

void Tag::free_particle_vars(Particle* particle){
    // Free the particle variables seted by this tag's behaviors.
    vector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.itemsVector.begin();
         iter_behavior != behaviors.itemsVector.end();
         iter_behavior++){
             (*iter_behavior)->free(particle);
    }

    // Free the particle variables seted by this tag's interactions.
    vector<Interaction*>::iterator iter_interaction;
    for (iter_interaction = interactions.itemsVector.begin();
         iter_interaction != interactions.itemsVector.end();
         iter_interaction++){
             (*iter_interaction)->free(particle);
    }
}

void Tag::add_particle(Particle* particle){
    particles.add(particle,false); 
    particle->tags.add(this,false);

    vector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.itemsVector.begin();
         iter_behavior != behaviors.itemsVector.end();
         iter_behavior++){
             (*iter_behavior)->setup(particle);
    }

    vector<Interaction*>::iterator iter_interaction;
    for (iter_interaction = interactions.itemsVector.begin();
         iter_interaction != interactions.itemsVector.end();
         iter_interaction++){
             (*iter_interaction)->setup(particle);
    }

}

void Tag::add_particles(vector<Particle*> added_particles){
    vector<Particle*>::iterator iter_particle;
    for (iter_particle = added_particles.begin();
         iter_particle < added_particles.end();
         iter_particle++){
        add_particle(*iter_particle);
    }
}

Interaction* Tag::add_interaction(string interaction_name){
    Interaction* interaction = interactions.add_itemByName(interaction_name);

    vector<Particle*>::iterator iter_particle;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
        interaction->setup(*iter_particle);
    }
    return interaction;
}

void Tag::remove_interaction(Interaction* interaction){
    interactions.pop_itemById(interaction->id);

    vector<Particle*>::iterator iter_particle;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
        interaction->free(*iter_particle);
    }
}

void Tag::add_interaction(Interaction* interaction){
    interactions.add(interaction);

    vector<Particle*>::iterator iter_particle;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
        interaction->setup(*iter_particle);
    }
}

Behavior* Tag::add_behavior(string behavior_name){
    
    Behavior* behavior = behaviors.add_itemByName(behavior_name);
    vector<Particle*>::iterator iter_particle;
    for ( iter_particle = particles.itemsVector.begin();
          iter_particle < particles.itemsVector.end();
          iter_particle++){
        behavior->setup(*iter_particle);
    }
    return behavior;
}

void Tag::add_behavior(Behavior* behavior){
    behaviors.add(behavior);
    vector<Particle*>::iterator iter_particle;
    for ( iter_particle = particles.itemsVector.begin();
          iter_particle < particles.itemsVector.end();
          iter_particle++){
        behavior->setup(*iter_particle);
    }
}

void Tag::remove_behavior(Behavior* behavior){
    behaviors.pop_itemById(behavior->id);
    vector<Particle*>::iterator iter_particle;
    for ( iter_particle = particles.itemsVector.begin();
          iter_particle < particles.itemsVector.end();
          iter_particle++){
        behavior->free(*iter_particle);
    }
}

void Tag::run(){
    behave();
    interact();
}

void Tag::behave(){
    vector<Particle*>::iterator iter_particle;
    vector<Behavior*>::iterator iter_behavior;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle != particles.itemsVector.end();
         iter_particle++){
         
         for (iter_behavior = behaviors.itemsVector.begin();
              iter_behavior != behaviors.itemsVector.end();
              iter_behavior++){
                  //cout << "run behavior at " << (*iter_particle)->name << " id:" << (*iter_particle)->id << endl;
                  (*iter_behavior)->run(*iter_particle);
         }
    }
}

void Tag::interact(){
    vector<Particle*>::iterator iter_particle;
    vector<Interaction*>::iterator iter_interaction;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle != particles.itemsVector.end();
         iter_particle++){
         
         for (iter_interaction = interactions.itemsVector.begin();
              iter_interaction != interactions.itemsVector.end();
              iter_interaction++){
                  (*iter_interaction)->run(*iter_particle);
                  //cout << "interaction runing in dead mode..." << endl;

         }
    }
}
