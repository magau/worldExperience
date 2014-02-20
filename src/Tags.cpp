#include "testApp.h"


Tag :: Tag (World* _world){
    set_world(_world);
}

Tag :: ~Tag (){
    remove_particles(particles.itemsVector);    
    behaviors.erase_all();
    interactions.erase_all();
    actions.erase_all();
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
    // Remove the particle from this tag's particles container:
    particles.pop_itemById(particle->id); 
    // Remove this tag from particle's tags container:
    particle->tags.pop_itemById(id);
    // Free the particle variables seted by this tag's behaviors and interactions:
    free_particle_vars(particle);
}

//void Tag::free(Item* item){
//    // Free the item variables seted by this tag's behaviors.
//    vector<Behavior*>::iterator iter_behavior;
//    for (iter_behavior = behaviors.itemsVector.begin();
//         iter_behavior != behaviors.itemsVector.end();
//         iter_behavior++){
//             (*iter_behavior)->free(item);
//    }
//
//    // Free the item variables seted by this tag's interactions.
//    vector<Interaction*>::iterator iter_interaction;
//    for (iter_interaction = interactions.itemsVector.begin();
//         iter_interaction != interactions.itemsVector.end();
//         iter_interaction++){
//             (*iter_interaction)->free(item);
//    }
//
//    // Free the item variables seted by this tag's actions.
//    vector<Action*>::iterator iter_action;
//    for (iter_action = actions.itemsVector.begin();
//         iter_action != actions.itemsVector.end();
//         iter_action++){
//             (*iter_action)->free(item);
//    }
//
//    // Free the item variables seted by this tag's particles.
//    vector<Particle*>::iterator iter_particle;
//    for (iter_particle = particles.itemsVector.begin();
//         iter_particle != particles.itemsVector.end();
//         iter_particle++){
//             (*iter_particle)->free(item);
//    }
//}
//
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

    // Free the particle variables seted by this tag's actions.
    vector<Action*>::iterator iter_action;
    for (iter_action = actions.itemsVector.begin();
         iter_action != actions.itemsVector.end();
         iter_action++){
             (*iter_action)->free(particle);
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

    vector<Action*>::iterator iter_action;
    for (iter_action = actions.itemsVector.begin();
         iter_action != actions.itemsVector.end();
         iter_action++){
             (*iter_action)->setup(particle);
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

void Tag::add_action(Action* action){
    actions.add(action);
    action->add_tag(this);
    action->setup();
}

Action* Tag::add_action(string action_name){
    //Action* action = world->create_action(action_name);
    //actions.add(interaction);
    Action* action = actions.create_itemByName(action_name);
    action->set_world(world);
    action->add_tag(this);
    action->setup();
    return action;
}

void Tag::remove_action(Action* action){
    actions.pop_itemById(action->id);

    vector<Particle*>::iterator iter_particle;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
        action->free(*iter_particle);
    }
}

void Tag::add_interaction(Interaction* interaction){
    //interactions.add(interaction);
    actions.add(interaction);
    interaction->add_tag(this);
    interaction->setup();
}

Interaction* Tag::add_interaction(string interaction_name){
    //Interaction* interaction = interactions.create_itemByName(interaction_name);
    Interaction* interaction = world->create_interaction(interaction_name);
    actions.add(interaction);
    interaction->set_world(world);
    interaction->add_tag(this);
    interaction->setup();
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

Behavior* Tag::add_behavior(string behavior_name){
    
    //Behavior* behavior = behaviors.create_itemByName(behavior_name);
    Behavior* behavior = world->create_behavior(behavior_name);
    actions.add(behavior);
    behavior->set_world(world);
    behavior->add_tag(this);
    behavior->setup();
    //vector<Particle*>::iterator iter_particle;
    //for ( iter_particle = particles.itemsVector.begin();
    //      iter_particle < particles.itemsVector.end();
    //      iter_particle++){
    //    behavior->setup(*iter_particle);
    //}
    return behavior;
}

void Tag::add_behavior(Behavior* behavior){
    actions.add(behavior);
    behavior->add_tag(this);
    behavior->setup();

    //behaviors.add(behavior);
    //behavior->add_tag(this);
    //behavior->setup();

    //vector<Particle*>::iterator iter_particle;
    //for ( iter_particle = particles.itemsVector.begin();
    //      iter_particle < particles.itemsVector.end();
    //      iter_particle++){
    //    behavior->setup(*iter_particle);
    //}
}

void Tag::remove_behavior(Behavior* behavior){
    behaviors.pop_itemById(behavior->id);
    behavior->free();
    //vector<Particle*>::iterator iter_particle;
    //for ( iter_particle = particles.itemsVector.begin();
    //      iter_particle < particles.itemsVector.end();
    //      iter_particle++){
    //    behavior->free(*iter_particle);
    //}
}

void Tag::run(){
    //behave();
    //interact();
    actuate();
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

void Tag::actuate(){
    vector<Particle*>::iterator iter_particle;
    vector<Action*>::iterator iter_action;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle != particles.itemsVector.end();
         iter_particle++){
         
        for (iter_action = actions.itemsVector.begin();
             iter_action != actions.itemsVector.end();
             iter_action++){
             (*iter_action)->run(*iter_particle);
             //cout << "action runing in dead mode..." << endl;
        }
    }
}
