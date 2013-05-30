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
        if(!temp_particle_ptr->props.bool_map["isAlive"]){
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

void World_KeyboardInterface::start(){

    particlesName.push_back("baseP"); 
    particlesName.push_back("P_Circle"); 
    particlesName.push_back("MP_RegGrid"); 

    isListening = false;
    creatingParticle = false;
}

void World_KeyboardInterface::listen(int key){
   if(ofGetKeyPressed(9)) { //CTRL + I
       isListening = true;
       msg.erase();
       cout<<"insert mode"<<msg<<endl;
   } else if(ofGetKeyPressed(5)) { //CTRL + E
       isListening = false;
       cout<<"end msg"<<msg<<endl;
       cout<<"msg:"<<msg<<endl;
       if(msg.compare("create particle") == 0){
           creatingParticle = true;
           cout<<"particles:";
           // iterate over particlesName in future...
           cout<<"baseP"<<endl;
           cout<<"P_Circle"<<endl;
           cout<<"MP_RegGrid"<<endl;
       } else if(creatingParticle){
           tempParticle = world->create_particle(msg, Particle_props());
       }
   } else if(isListening){
       if(key != 8){
           msg += key;
       } else {
           msg.erase(msg.end()-1);
       }
       cout<<"msg:"<<msg<<endl;
   }
   
}

