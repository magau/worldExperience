#include "testApp.h"

World :: World(){
    particles.set_main_container(true);
    tags.set_main_container(true);

    camera.setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()/2, -700.f));
    camera.lookAt(ofVec3f(ofGetWindowWidth()/2,ofGetWindowHeight()/2 , 0), ofVec3f(0,-1,0));

    //light.setPointLight();
    light.setDirectional();
    light.setPosition(ofVec3f(ofGetWindowWidth()/2, -ofGetWindowHeight()/2, -700.f));
    //light.setOrientation(ofVec3f(ofGetWindowWidth()/2,ofGetWindowHeight()/2 , 700.f));
    //light.setOrientation(ofVec3f(ofGetWindowWidth()/2,ofGetWindowHeight()/2 , 700.f));
    light.setOrientation(ofVec3f(0,0, 700.f));
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
        particle->set_variable("is_active",Item_Parameter<bool>(true));
        particle->setup(); 
    } else {
        particle->set_variable("is_active",Item_Parameter<bool>(false));
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
        particle->set_variable("is_active",Item_Parameter<bool>(true));
        particle->setup(); 
    } else {
        particle->set_variable("is_active",Item_Parameter<bool>(false));
    }
    particles.push_back(particle);

    return particle;
}

Controller* World::create_controller(string iName, bool isActive) {
    Controller* controller = nature.create_controller(iName);
    controller->set_world(this);
    if (isActive) {
        controller->set_variable("is_active",Item_Parameter<bool>(true));
        controller->setup(); 
    } else {
        controller->set_variable("is_active",Item_Parameter<bool>(false));
    }
    controllers.push_back(controller);

    return controller;
}

Controller* World::create_controller(const type_info& controller_type, bool isActive) {
    Controller* controller = nature.create_controller(controller_type);
    controller->set_world(this);
    if (isActive) {
        controller->set_variable("is_active",Item_Parameter<bool>(true));
        controller->setup(); 
    } else {
        controller->set_variable("is_active",Item_Parameter<bool>(false));
    }
    controllers.push_back(controller);

    return controller;
}

Controller* World::add_controller(Controller* controller, bool isActive) {
    controller->set_world(this);
    if (isActive) {
        controller->set_variable("is_active",Item_Parameter<bool>(true));
        controller->setup(); 
    } else {
        controller->set_variable("is_active",Item_Parameter<bool>(false));
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
    // Remove the particle from the particles container of its
    // owne tag.
    PointersVector<Tag*>::iterator iter_tag;
    for(iter_tag=particle->tags.end() - 1;
        iter_tag >= particle->tags.begin();
        iter_tag--)
        (*iter_tag)->remove_particle(particle);
    // Remove the particle from the world.particles container.
    particles.erase_item_by_id(particle->get_id());
}

void World :: remove_particles(PointersVector<Particle*>* particles_selection){
    // Remove the particles from the world particles container of its
    // owne tag and erase it from the world.particles container.
    PointersVector<Particle*>::iterator iter_particle;
    for (iter_particle = particles_selection->end() - 1;
         iter_particle >= particles_selection->begin();
         iter_particle--)
        remove_particle(*iter_particle);
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

    for(PointersVector<Tag*>::iterator iter_tag = tags.end() - 1;
                                    iter_tag >= tags.begin();
                                    iter_tag--)
        (*iter_tag)->run();

    // This "for" statement is iterated in reverse mode to avoid core 
    // dump in case of the "remove_particle" function is called.
    for(PointersVector<Particle*>::iterator iter_particle = particles.end() - 1;
                                            iter_particle >= particles.begin();
                                            iter_particle--) {
        if(!(*iter_particle)->get_item_parameter<bool>("is_alive")->value) {
            remove_particle(*iter_particle);
        } else if ((*iter_particle)->get_item_parameter<bool>("is_active")->value) {
            (*iter_particle)->run();
        }
    }

    for(PointersVector<Controller*>::iterator iter_controller = controllers.begin();
                                              iter_controller != controllers.end();
                                              iter_controller++)
        (*iter_controller)->update();

    return &(particles);
}

void World::draw(){
    ofBackground(0);
    //light.enable();
    camera.begin();
    for(PointersVector<Particle*>::iterator iter_particle = particles.begin();
                                            iter_particle != particles.end();
                                            iter_particle++){
        //if ((*iter_particle)->get_item_parameter<bool>("is_visible")->value)
        if ((*iter_particle)->visible.value)
            (*iter_particle)->display();
    }
    camera.end();
    //light.disable();
}
