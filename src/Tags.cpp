#include "testApp.h"

Tag::Tag (World* _world){
    particles.set_main_container(false);
    behaviors.set_main_container(true);
    interactions.set_main_container(true);
    set_world(_world);
}

Tag::~Tag (){
    remove_particles(particles);    
    remove_behaviors();
    remove_interactions();
}

void Tag::add_particle(Particle* particle){
    // Add this tag to particle's tags container:
    particle->tags.push_back(this);
    // Run the setup function of this tag's behaviors
    // and interactions over the added particle:
    setup_particle(particle);
    // Add the particle to this tag's particles container:
    particles.push_back(particle); 
}

void Tag::setup_particle(Particle* particle){

    PointersVector<Interaction*>::iterator iter_interaction;
    for (iter_interaction = interactions.begin();
         iter_interaction != interactions.end();
         iter_interaction++){
         (*iter_interaction)->setup(particle);
    }

    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){
         (*iter_behavior)->setup(particle);
    }
}

void Tag::add_particles(PointersVector<Particle*> added_particles){
    PointersVector<Particle*>::iterator iter_particle;
    for (iter_particle = added_particles.begin();
         iter_particle < added_particles.end();
         iter_particle++){
        add_particle(*iter_particle);
    }
}

Particle* Tag::get_particle_by_id(int particle_id){
    return particles.get_item_by_id(particle_id);
}

PointersVector<Particle*> Tag::get_particles_by_typeid(const type_info& particle_typeid){
    return particles.get_items_by_typeid(particle_typeid);
}

void Tag::remove_particle(Particle* particle){
    // Free the particle variables seted by this tag's behaviors and interactions:
    free_particle(particle);
    // Remove the particle from this tag's particles container:
    particles.erase_item_by_id(particle->get_id()); 
    // Remove this tag from particle's tags container:
    particle->tags.erase_item_by_id(id);
}

void Tag::free_particle(Particle* particle){
    // Free the particle variables seted by this tag's actions.
    PointersVector<Interaction*>::iterator iter_interaction;
    for (iter_interaction = interactions.begin();
         iter_interaction != interactions.end();
         iter_interaction++){
         (*iter_interaction)->free(particle);
    }

    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){
         (*iter_behavior)->free(particle);
    }

}

void Tag::remove_particles(PointersVector<Particle*> particles_to_remove){
    PointersVector<Particle*>::iterator iter_particle;
    for (iter_particle = particles_to_remove.begin();
         iter_particle < particles_to_remove.end();
         iter_particle++){
        remove_particle(*iter_particle);
    }
}

void Tag::setup_action(Action* action, bool isActive){
/*
 * If the action acts over the world or tag
 * since its creation, it only can be done 
 * after seting up the world and tag.
 * This is the purpose of the setup function.
 */ 
    action->add_tag(this);
    action->set_world(get_world());
    if(isActive){
        action->setup(); 
        action->set_active_state(true);
    } else {
        action->set_active_state(false);
    }
}

Behavior* Tag::create_behavior(string behavior_name, bool isActive){
    Behavior* behavior = world->nature.create_behavior(behavior_name);
    setup_action(behavior, isActive);
    behaviors.push_back(behavior);
    return behavior;
}

Behavior* Tag::create_behavior(const type_info& behavior_typeid, bool isActive){
    Behavior* behavior = world->nature.create_behavior(behavior_typeid);
    setup_action(behavior, isActive);
    behaviors.push_back(behavior);
    return behavior;
}

PointersVector<Behavior*> Tag::get_behaviors_by_typeid(const type_info& behavior_typeid){
    return behaviors.get_items_by_typeid(behavior_typeid);
}

Behavior* Tag::get_behavior_by_id(int behavior_id){
    return behaviors.get_item_by_id(behavior_id);
}

void Tag::remove_behavior(Behavior* behavior){
    behavior->free();
    behaviors.erase_item_by_id(behavior->get_id());
}

void Tag::remove_behaviors(){
    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){

        (*iter_behavior)->free();
    }
    behaviors.clear();
}

Interaction* Tag::create_interaction(string interaction_name, bool isActive){
    Interaction* interaction = world->nature.create_interaction(interaction_name);
    setup_action(interaction, isActive);
    interactions.push_back(interaction);
    return interaction;
}

Interaction* Tag::create_interaction(const type_info& interaction_typeid, bool isActive){
    Interaction* interaction = world->nature.create_interaction(interaction_typeid);
    setup_action(interaction, isActive);
    interactions.push_back(interaction);
    return interaction;
}

PointersVector<Interaction*> Tag::get_interactions_by_typeid(const type_info& interaction_typeid){
    return interactions.get_items_by_typeid(interaction_typeid);
}

Interaction* Tag::get_interaction_by_id(int interaction_id){
    return interactions.get_item_by_id(interaction_id);
}

void Tag::remove_interaction(Interaction* interaction){
    interaction->free();
    interactions.erase_item_by_id(interaction->get_id());
}

void Tag::remove_interactions(){
    PointersVector<Interaction*>::iterator iter_interaction;
    for (iter_interaction = interactions.begin();
         iter_interaction != interactions.end();
         iter_interaction++){
        (*iter_interaction)->free();
    }
    interactions.clear();
}

void Tag::run(){

    PointersVector<Interaction*>::iterator iter_interaction;
    for (iter_interaction = interactions.begin();
         iter_interaction != interactions.end();
         iter_interaction++){
         (*iter_interaction)->run();
    }

    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){
         (*iter_behavior)->run();
    }


}

void Tag::add_listener_to_particles(string attr_name){
    PointersVector<Particle*>::iterator iter_particle;
    for (iter_particle = particles.begin();
         iter_particle < particles.end();
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

    for (iter_particle = particles.begin();
         iter_particle < particles.end();
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
    for (iter_particle = particles.begin();
         iter_particle < particles.end();
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
    for (iter_particle = particles.begin();
         iter_particle < particles.end();
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
    for (iter_particle = particles.begin();
         iter_particle < particles.end();
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
