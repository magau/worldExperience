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
        action->set_item_parameter<bool>("is_active",true);
    } else {
        action->set_item_parameter<bool>("is_active",false);
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
         //cout << (*iter_interaction)->get_type_name() << endl;
         (*iter_interaction)->run();
    }

    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){
         //cout << (*iter_behavior)->get_type_name() << endl;
         (*iter_behavior)->run();
    }
}


void Tag::add_listener_to_particles(Item* host_controller, string button_name) {

    Button* button = static_cast<Button*>(host_controller->get_variable(button_name).value);
    ofEvent<pair<shared_variable_key, shared_variable_value>>* event = &(button->event);

    if (event != NULL) {
        set_variable(button_name, event, EVENT_SH_VAR, host_controller, &(particles_events_map));
        PointersVector<Particle*>::iterator iter_particle;
        for (iter_particle = particles.begin();
            iter_particle != particles.end();
            iter_particle++){
            (*iter_particle)->add_listener(event);
        }
    } else {
        cout << "error: Invalid event name for Controller: " << host_controller->get_name() << "." << endl;
    }
}

void Tag::remove_listener_from_particles(string button_name, Item* host_controller) {
    Button* button = static_cast<Button*>(host_controller->get_variable(button_name).value);
    ofEvent<pair<shared_variable_key, shared_variable_value>>* event = &(button->event);

    if (event != NULL) {
        PointersVector<Particle*>::iterator iter_particle;
        for (iter_particle = particles.begin();
            iter_particle != particles.end();
            iter_particle++){
            (*iter_particle)->remove_listener(event);
        }
    } else {
        cout << "error: Invalid event name for Controller: " << host_controller->get_name() << "." << endl;
    }

    erase_variable(button_name, host_controller, &(particles_events_map));

//    arg_t event_arg_t = host_ctrl_ptr->get_variable(event_name).type_enum;
//    PointersVector<Particle*>::iterator iter_particle;
//    for (iter_particle = particles.begin();
//        iter_particle != particles.end();
//        iter_particle++){
//
//        switch (event_arg_t) {
//            case EVENT_IP_BOOL:
//                (*iter_particle)->remove_listener<bool>(host_ctrl_ptr->get_event<bool>(event_name));
//                break;
//            case EVENT_IP_INT:
//                (*iter_particle)->remove_listener<int>(host_ctrl_ptr->get_event<int>(event_name));
//                break;
//            case EVENT_IP_FLOAT:
//                (*iter_particle)->remove_listener<float>(host_ctrl_ptr->get_event<float>(event_name));
//                break;
//            case EVENT_IP_DOUBLE:
//                (*iter_particle)->remove_listener<double>(host_ctrl_ptr->get_event<double>(event_name));
//                break;
//            case T_NULL:
//                cout << "arg_t not defined for this type!!" << endl;
//                break;
//            default:
//                cout << "arg_t not defined for this type!!" << endl;
//                break;
//        }
//    }
//    erase_event(event_name, host_ctrl_ptr);
}


void Tag::add_listener_to_interaction(string event_name, Item* host_controller) {
}
void Tag::add_listener_to_behavior(string event_name, Item* host_controller) {
}
