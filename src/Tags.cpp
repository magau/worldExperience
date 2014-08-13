#include "testApp.h"

Tag::Tag (World* _world){
    particles.set_main_container(false);
    behaviors.set_main_container(true);
    interactions.set_main_container(true);
    set_world(_world);
}

Tag::~Tag (){
    remove_particles();    
    remove_behaviors();
    remove_interactions();
    clear_variables();
    remove_attached_buttons();
}

void Tag::add_particle(Particle* particle){
    // Add this tag to particle's tags container:
    particle->tags.push_back(this);
    // Run the setup function of this tag's behaviors
    // and interactions over the added particle:
    setup_particle(particle);
    // Add the particle to this tag's particles container:
    particles.push_back(particle); 
    // Add the particle to this tag's attaced buttons event listeners:
    setup_attached_buttons(particle);
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
    // Remove particle from this tag's attaced buttons event listeners:
    free_attached_buttons(particle);
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

void Tag::remove_particles(PointersVector<Particle*>* particles_selection){
    if (particles_selection == NULL)
        particles_selection = &particles;
    PointersVector<Particle*>::iterator iter_particle;
    for (iter_particle = particles_selection->begin();
         iter_particle < particles_selection->end();
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

void Tag::add_listener(Item* host_controller, string button_name) {
    Button* button = static_cast<Button*>(host_controller->get_variable(button_name).value);
    if (button != NULL) {
        ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event = &(button->event);
        if (event != NULL) {
            // Add button to attached_buttons (vector<Button*>).
            attached_buttons.push_back(button);
            // Add this to the button listeners vector<Items*>. 
            button->listeners.push_back(this);

            PointersVector<Particle*>::iterator iter_particle;
            for (iter_particle = particles.begin();
                iter_particle != particles.end();
                iter_particle++){
                (*iter_particle)->add_listener(event);
            }
        } else {
            cout << "error: Invalid event name for Controller: " << host_controller->get_name() << "." << endl;
        }
    } else {
        cout << "error: Invalid button name for Controller: " << host_controller->get_name() << "." << endl;
    }
}

void Tag::remove_listener(string button_name, Item* host_controller) {
    cout << "remove button from tag..."<<endl;
    Button* button = static_cast<Button*>(host_controller->get_variable(button_name).value);
    if (button != NULL) {
        ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &(button->event);
        if (event != NULL) {
            PointersVector<Particle*>::iterator iter_particle;
            for (iter_particle = particles.begin();
                iter_particle != particles.end();
                iter_particle++){
                (*iter_particle)->remove_listener(event);
            //cout<< "Remove listener from particle:" << (*iter_particle)->get_name() << endl;
            }
            // Remove button from attached_buttons (vector<Button*>).
            //cout << "Remove button from the attached_buttons." << endl;
            vector<Button*>::iterator button_it = find(attached_buttons.begin(),attached_buttons.end(),button);
            if(button_it != attached_buttons.end())
                attached_buttons.erase(button_it);
            // Remove this from the button listeners (vector<Items*>). 
            //cout << "Remove tag:" << get_name() << " from the button listeners." << endl; 
            vector<Item*>::iterator listener_it = find(button->listeners.begin(),button->listeners.end(),this);
            if(listener_it != button->listeners.end())
                button->listeners.erase(listener_it);
            //cout << "tag:" << get_name() << " removed sccessfully." << endl; 
        } else {
            cout << "error: Invalid event name for Controller: " << host_controller->get_name() << "." << endl;
        }
    } else {
        cout << "error: Invalid button name for Controller: " << host_controller->get_name() << "." << endl;
    }
    //cout << "exit tag.remove_listener..." << endl;
}

void Tag::remove_attached_buttons() {
    // Remove button from attached_buttons (vector<Button*>).
    vector<Button*>::iterator button_it;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){
        // Remove this tag from the button listeners (vector<Items*>). 
        vector<Item*>::iterator listener_it = find((*button_it)->listeners.begin(),(*button_it)->listeners.end(),this);
        if(listener_it != (*button_it)->listeners.end())
            (*button_it)->listeners.erase(listener_it);
        ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &((*button_it)->event);
        if (event != NULL) {
            PointersVector<Particle*>::iterator iter_particle;
            for (iter_particle = particles.begin();
                iter_particle != particles.end();
                iter_particle++){
                (*iter_particle)->remove_listener(event);
                //cout<< "Remove listener from particle:" << (*iter_particle)->get_name() << endl;
            }
        }
    }
    attached_buttons.clear();
}

void Tag::setup_attached_buttons(Particle* particle) {
    vector<Button*>::iterator button_it;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){
        ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &((*button_it)->event);
        if (event != NULL)
            particle->add_listener(event);
    }
}

void Tag::free_attached_buttons(Particle* particle) {
    vector<Button*>::iterator button_it;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){
        ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &((*button_it)->event);
        if (event != NULL)
            particle->remove_listener(event);
    }
}
