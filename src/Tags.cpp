#include "testApp.h"

Tag::Tag (World* _world){
    set_name(get_type_name());
    particles.set_main_container(false);
    behaviors.set_main_container(true);
    interactions.set_main_container(true);
    set_world(_world);
}

Tag::~Tag (){
    remove_behaviors();
    remove_interactions();
    remove_particles();    
    clear_variables();
    remove_attached_buttons();
}

const type_info& Tag::get_typeid() {
    return typeid(this);
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
         (*iter_interaction)->setup_particle(particle);
    }

    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){
         (*iter_behavior)->setup_particle(particle);
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

Particle* Tag::get_particle_by_id(Particle* particle_ptr){
    return particles.get_item_by_id(particle_ptr);
}

PointersVector<Particle*> Tag::get_particles_by_typeid(const type_info& particle_typeid){
    return particles.get_items_by_typeid(particle_typeid);
}

void Tag::remove_particle(Particle* particle){

    if (get_particle_by_id(particle) != (Particle*)NULL) {
        // Free the particle variables seted by this tag's behaviors and interactions:
        free_particle(particle);
        // Remove the particle from this tag's particles container:
        particles.erase_item_by_id(particle); 
        // Remove this tag from particle's tags container:
        particle->tags.erase_item_by_id(this);
        // Remove particle from this tag's attaced buttons event listeners:
        free_attached_buttons(particle);
    }
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
    for (iter_particle = particles_selection->end() - 1;
         iter_particle >= particles_selection->begin();
         iter_particle--){
        // Free the particle variables seted by this tag's behaviors and interactions:
        free_particle(*iter_particle);
        // Remove the particle from this tag's particles container:
        particles_selection->pop_back();
        if (particles_selection != &particles)
            particles.erase_item_by_id(*iter_particle); 
        // Remove this tag from particle's tags container:
        (*iter_particle)->tags.erase_item_by_id(this);
        // Remove particle from this tag's attaced buttons event listeners:
        free_attached_buttons(*iter_particle);
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

Behavior* Tag::get_behavior_by_id(Behavior* behavior_ptr){
    return behaviors.get_item_by_id(behavior_ptr);
}

void Tag::remove_behavior(Behavior* behavior_ptr){
    behavior_ptr->free();
    behaviors.erase_item_by_id(behavior_ptr);
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

Interaction* Tag::get_interaction_by_id(Interaction* interaction_ptr){
    return interactions.get_item_by_id(interaction_ptr);
}

void Tag::remove_interaction(Interaction* interaction_ptr){
    interaction_ptr->free();
    interactions.erase_item_by_id(interaction_ptr);
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
         (*iter_interaction)->update();
    }

    PointersVector<Behavior*>::iterator iter_behavior;
    for (iter_behavior = behaviors.begin();
         iter_behavior != behaviors.end();
         iter_behavior++){
         //cout << (*iter_behavior)->get_type_name() << endl;
         (*iter_behavior)->update();
    }
}

void Tag::set_listener(Button* button, ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event) {

    if (event != NULL) {
        // Add button to attached_buttons (vector<Button*>).
        attached_buttons.push_back(button);

        PointersVector<Particle*>::iterator iter_particle;
        for (iter_particle = particles.begin();
            iter_particle != particles.end();
            iter_particle++){
            (*iter_particle)->add_listener(event);
        }

    } else {
        cout << "error: Missing button's event." << endl;
    }
    
}

void Tag::remove_listener(Button* button, ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event) {
    //cout << "remove button from tag..."<<endl;
    //ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &(button->event);
    if (event != NULL) {
        PointersVector<Particle*>::iterator iter_particle;
        for (iter_particle = particles.begin();
            iter_particle != particles.end();
            iter_particle++){
            (*iter_particle)->remove_listener(event);
        }
        // Remove button from attached_buttons (vector<Button*>).
        vector<Button*>::iterator button_it = find(attached_buttons.begin(),attached_buttons.end(),button);
        if(button_it != attached_buttons.end())
            attached_buttons.erase(button_it);
    } else {
        cout << "error: Missing button's event." << endl;
    }
}

void Tag::remove_attached_buttons() {
    // Remove button from attached_buttons (vector<Button*>).
    vector<Button*>::iterator button_it;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){

        unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it = (*button_it)->listeners_map.find(this);
        if (b_item_map_it != (*button_it)->listeners_map.end()){
            ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &(b_item_map_it->second.event);

        // Remove this tag from the button attached listeners (unordered_map<Button_Items,Item*>). 
            if (event != NULL) {
                PointersVector<Particle*>::iterator iter_particle;
                for (iter_particle = particles.begin();
                    iter_particle != particles.end();
                    iter_particle++){
                    (*iter_particle)->remove_listener(event);
                }
            }
            (*button_it)->listeners_map.erase(b_item_map_it);
        }
    }
    attached_buttons.clear();
}

void Tag::setup_attached_buttons(Particle* particle) {
    vector<Button*>::iterator button_it;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){

        unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it = (*button_it)->listeners_map.find(this);
        if (b_item_map_it != (*button_it)->listeners_map.end()){
            ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &(b_item_map_it->second.event);
            if (event != NULL)
                particle->add_listener(event);
        }
    }
}

void Tag::free_attached_buttons(Particle* particle) {
    vector<Button*>::iterator button_it;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){

        unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it = (*button_it)->listeners_map.find(this);
        if (b_item_map_it != (*button_it)->listeners_map.end()){
            ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &(b_item_map_it->second.event);
            if (event != NULL)
                particle->remove_listener(event);
        }
    }
}
