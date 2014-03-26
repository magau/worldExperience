#include "testApp.h"

Tag :: Tag (World* _world){
    set_world(_world);
}

Tag :: ~Tag (){
    remove_actions();
    remove_particles(particles.itemsVector);    
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
    free_particle(particle);
}

void Tag::free_particle(Particle* particle){
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
    Action* action = world->create_action(action_name);
    actions.add(action);
    action->set_world(world);
    action->add_tag(this);
    action->setup();
    return action;
}

void Tag::remove_action(Action* action){
    actions.pop_itemById(action->id);
    action->free();
}

void Tag::remove_actions(){
    vector<Action*>::iterator iter_action;
    for (iter_action = actions.itemsVector.begin();
         iter_action != actions.itemsVector.end();
         iter_action++){
        remove_action(*iter_action);
    }
}

void Tag::add_interaction(Interaction* interaction){
    add_action(interaction);
}

Interaction* Tag::add_interaction(string interaction_name){
    Interaction* interaction = world->create_interaction(interaction_name);
    interaction->set_world(world);
    actions.add(interaction);
    interaction->add_tag(this);
    interaction->setup();
    return interaction;
}

void Tag::remove_interaction(Interaction* interaction){
    remove_action(interaction);
}

Behavior* Tag::add_behavior(string behavior_name){
    
    Behavior* behavior = world->create_behavior(behavior_name);
    behavior->set_world(world);
    actions.add(behavior);
    behavior->add_tag(this);
    behavior->setup();
    return behavior;
}

void Tag::add_behavior(Behavior* behavior){
    add_action(behavior);
}

void Tag::remove_behavior(Behavior* behavior){
    remove_action(behavior);
}

void Tag::run(){
    actuate();
}

void Tag::actuate(){
    vector<Action*>::iterator iter_action;
    for (iter_action = actions.itemsVector.begin();
         iter_action != actions.itemsVector.end();
         iter_action++){
         (*iter_action)->run();
    }
}

void Tag::add_listener_to_particles(string attr_name){
    vector<Particle*>::iterator iter_particle;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
          
         for (typename unordered_map<string,bool*>::iterator map_it = (*iter_particle)->boolPtr_map.begin();
              map_it != boolPtr_map.end();
              map_it++){
         
             if (map_it->first.compare(attr_name) == 0) {
                 if (typeid(*(map_it->second)) == typeid(bool)){
                     (*iter_particle)->add_bool_listener(&bool_event);
                     //(*iter_particle)->add_listener<bool_attr>(&bool_event);
                 }
             }
         }
    }

    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
          
         for (typename unordered_map<string,int*>::iterator map_it = (*iter_particle)->intPtr_map.begin();
              map_it != intPtr_map.end();
              map_it++){
             if (map_it->first.compare(attr_name) == 0) {
                 if (typeid(*(map_it->second)) == typeid(int)) {    
                     (*iter_particle)->add_int_listener(&int_event);
                 }
             }
         }

    }
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
          
         for (typename unordered_map<string,float*>::iterator map_it = (*iter_particle)->floatPtr_map.begin();
              map_it != floatPtr_map.end();
              map_it++){
             if (map_it->first.compare(attr_name) == 0) {
                 if (typeid(*(map_it->second)) == typeid(float)) {    
                     (*iter_particle)->add_float_listener(&float_event);
                 }
             }
         }
    }
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
          
         for (typename unordered_map<string,ofVec3f*>::iterator map_it = (*iter_particle)->ofVec3fPtr_map.begin();
              map_it != ofVec3fPtr_map.end();
              map_it++){
             if (map_it->first.compare(attr_name) == 0) {
                 if (typeid(*(map_it->second)) == typeid(ofVec3f)) {    
                     (*iter_particle)->add_ofVec3f_listener(&ofVec3f_event);
                 }
             }
         }
    }
    for (iter_particle = particles.itemsVector.begin();
         iter_particle < particles.itemsVector.end();
         iter_particle++){
          
         for (typename unordered_map<string,ofColor*>::iterator map_it = (*iter_particle)->ofColorPtr_map.begin();
              map_it != ofColorPtr_map.end();
              map_it++){
             if (map_it->first.compare(attr_name) == 0) {
                 if (typeid(*(map_it->second)) == typeid(ofColor)) {    
                     (*iter_particle)->add_ofColor_listener(&ofColor_event);
                 }
             }
         }
    } 
}
