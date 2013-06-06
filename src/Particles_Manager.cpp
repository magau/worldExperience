#include "testApp.h"

Particles_Container* World::create_group(string iName){
    //create System systemParticles Particles_Container.
    Particles_Container* newGroup;
    newGroup = new Particles_Container;
    newGroup->name = iName;
    groups.add(newGroup);
    return newGroup;
}

Particle* World::create_particle(string iName){
    //create newParticle add particle to worldParticles and 
    //systemParticles Particles_Container
    Particle* newParticle;
    newParticle = particles.add_itemByName(iName, this);
    newParticle->world = this;
    return newParticle;
}

Particles_Container* World :: update(){
    Particle* temp_particle_ptr;
    for(vector<Particle*>::iterator IterPart = particles.itemsVector.begin();
                                    IterPart != particles.itemsVector.end();
                                    IterPart++){
        temp_particle_ptr = *IterPart;
        temp_particle_ptr->run();
        if(!temp_particle_ptr->isAlive){
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
   if(ofGetKeyPressed(9)) {
       //CTRL + I
       isListening = true;
       msg.erase();
       cout<<"INSERT"<<endl;
   } else if(ofGetKeyPressed(5)) {
       //CTRL + E
       isListening = false;
       cout<<"END"<<endl;
       cout<<"msg:"<<msg<<endl;
   } else if(isListening){
       msg += key;
       cout<<key<<endl;
   } else if(ofGetKeyPressed(3)){
       //CTRL + C
       create = true;
       remove = false;
       get    = false;
       set    = false;
       add    = false;

       cout<<"CREATE"<<endl;

   } else if(ofGetKeyPressed(18)){
       //CTRL + R
       create = false;
       remove = true;
       get    = false;
       set    = false;
       add    = false;

       cout<<"REMOVE"<<endl;

   } else if(ofGetKeyPressed(7)){
       //CTRL + G
       create = false;
       remove = false;
       get    = true;
       set    = false;
       add    = false;

       cout<<"GET"<<endl;

   } else if(ofGetKeyPressed(19)){
       //CTRL + S
       create = false;
       remove = false;
       get    = false;
       set    = true;
       add    = false;

       cout<<"SET"<<endl;

   } else if(ofGetKeyPressed(1)){
       //CTRL + A
       create = false;
       remove = false;
       get    = false;
       set    = false;
       add    = true;

       cout<<"ADD"<<endl;

   } else if(ofGetKeyPressed(112)){
       // P
       particle    = true;
       group       = false;
       behavior    = false;
       interaction = false;

       cout<<"PARTICLE"<<endl;

   } else if(ofGetKeyPressed(103)){
       // G
       particle    = false;
       group       = true;
       behavior    = false;
       interaction = false;

       cout<<"GROUP"<<endl;

   } else if(ofGetKeyPressed(98)){
       // B
       particle    = false;
       group       = false;
       behavior    = true;
       interaction = false;

       cout<<"BEHAVIOR"<<endl;

   } else if(ofGetKeyPressed(105)){
       // I
       particle    = false;
       group       = false;
       behavior    = false;
       interaction = true;

       cout<<"INTERACTION"<<endl;

   }
}

