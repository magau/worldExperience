#include "testApp.h"

World :: World() {
    particles.set_main_container(true);
    tags.set_main_container(true);
}

Particle* World::create_particle(string iName, bool isActive){
/*
 * Create a new particle. Add created particle to the world particles
 * container and if "isActive" is setted true run the
 * activate_particle method (set true the "isActive" 
 * attribute of the particle and run
 * the "setup" method of the particle).
 */
    Particle* particle = nature.create_particle(iName);
    particle->set_world(this);
    if (isActive) {
        particle->set<bool>("is_active",true);
        particle->setup(); 
    } else {
        particle->set<bool>("is_active",false);
    }
    particles.push_back(particle);

    return particle;
}

Particle* World::create_particle(const type_info& particle_type, bool isActive){
/*
 * Create a new particle. Add created particle to the world particles
 * container and if "isActive" is setted true run the
 * activate_particle method (set true the "isActive" 
 * attribute of the particle and run
 * the "setup" method of the particle).
 */
    Particle* particle = nature.create_particle(particle_type);
    particle->set_world(this);
    if (isActive) {
        particle->set<bool>("is_active",true);
        particle->setup(); 
    } else {
        particle->set<bool>("is_active",false);
    }
    particles.push_back(particle);

    return particle;
}

Controller* World::create_controller(string iName, bool isActive) {
    Controller* controller = nature.create_controller(iName);
    controller->set_world(this);
    if (isActive) {
        controller->set<bool>("is_active",true);
        controller->setup(); 
    } else {
        controller->set<bool>("is_active",false);
    }
    controllers.push_back(controller);

    return controller;
}

Controller* World::create_controller(const type_info& controller_type, bool isActive) {
    Controller* controller = nature.create_controller(controller_type);
    controller->set_world(this);
    if (isActive) {
        controller->set<bool>("is_active",true);
        controller->setup(); 
    } else {
        controller->set<bool>("is_active",false);
    }
    controllers.push_back(controller);

    return controller;
}

PointersVector<Particle*> World::get_particle_by_typeid(const type_info& particle_typeid) {
    return particles.get_items_by_typeid(particle_typeid);
}

Particle* World::get_particle_by_id(int particle_id){
    return particles.get_item_by_id(particle_id);
}


void World :: remove_particle(Particle* particle){
    // Remove the particle from the particles container of each
    // world tag.
    PointersVector<Tag*>::iterator iter_tag;
    for(iter_tag=tags.begin(); iter_tag!=tags.end(); iter_tag++)
        (*iter_tag)->remove_particle(particle);
    // Remove the particle from the world.particles container.
    particles.erase_item_by_id(particle->get_id());
}

/*
 * Implementation in the furute of the "get" and "remove"
 * methods by name and id, for the particles and actions.
 * ...
 */

Tag* World::create_tag(string iName){
    //create a new tag in the World's tags container.
    Tag* newTag = new Tag(this);
    tags.push_back(newTag);

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
    tags.erase_item_by_id(tag->get_id());
}


PointersVector<Particle*>* World :: update(){

    for(PointersVector<Tag*>::iterator iter_tag = tags.begin();
                                    iter_tag != tags.end();
                                    iter_tag++){
        (*iter_tag)->run();
    }

    // This "for" statement is iterated in reverse mode to avoid core 
    // dump in case of the "remove_particle" function is called.
    for(PointersVector<Particle*>::iterator iter_particle = particles.end() - 1;
                                    iter_particle >= particles.begin();
                                    iter_particle--) {
        if(!(*iter_particle)->get<bool>("is_alive")->value) {
            remove_particle(*iter_particle);
        } else if ((*iter_particle)->get<bool>("is_active")->value) {
            (*iter_particle)->run();
        }
    }
    return &(particles);
}

void World::draw(){
    for(PointersVector<Particle*>::iterator iter_particle = particles.begin();
                                    iter_particle != particles.end();
                                    iter_particle++){
        //if ((*iter_particle)->get<bool>("is_visible")->value)
        if ((*iter_particle)->visible.value)
            (*iter_particle)->display();
    }
}
