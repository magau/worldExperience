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

Particles_Container* World::update(){
    for(vector<Particle*>::iterator IterPart = particles.itemsVector.begin();
                                    IterPart != particles.itemsVector.end();
                                    IterPart++){
        (*IterPart)->run();
    }
    return &(particles);
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

