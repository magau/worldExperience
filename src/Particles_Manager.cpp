#include "testApp.h"

//Particles_Container* World::create_group(string iName){
//    //create System systemParticles Particles_Container.
//    Particles_Container* newGroup;
//    newGroup = new Particles_Container;
//    newGroup->name = iName;
//    world->groups.add(newGroup);
//    return newGroup;
//}

Particle* World::create_particle(string iName, Particle_props init_props){
    //create newParticle add particle to worldParticles and 
    //systemParticles Particles_Container
    Particle* newParticle;
    init_props.world = this;
    newParticle = particles.add_itemByName(iName,init_props);
    return newParticle;
}

Particles_Container* World :: update(){
    Particle* temp_particle_ptr;
    for(vector<Particle*>::iterator IterPart = particles.itemsVector.begin();
                                    IterPart != particles.itemsVector.end();
                                    IterPart++){
        temp_particle_ptr = *IterPart;
        temp_particle_ptr->run();
        if(!temp_particle_ptr->props.isAlive){
            remove_particle(temp_particle_ptr);
        }
    }
    return &(particles);
}

void World :: remove_particle(Particle* particle_ptr){

}

void World::draw(){
    for(vector<Particle*>::iterator IterPart = particles.itemsVector.begin();
                                    IterPart != particles.itemsVector.end();
                                    IterPart++){
        (*IterPart)->display();
    }
}

void Manager_KeyboardInterface::start(){
    isListening = false;
}

void Manager_KeyboardInterface::listen(int key){
   if(ofGetKeyPressed(17)) { //CTRL + Q
       isListening = true;
       msg.erase();
   } else if(ofGetKeyPressed(23)) { //CTRL + W
       isListening = false;
       cout<<"msg:"<<msg<<endl;
   } else if(isListening){
       msg += key;
   }
}

