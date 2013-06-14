#include "testApp.h"

World :: World() {
    particles.name = "C_World";
}

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
   
    particles.pop_itemById(particle_ptr->id);

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
    mainObj = false;
}

void Manager_KeyboardInterface::listen(int key){

   if(ofGetKeyPressed(13)) {
       //RETURN
   } else if(ofGetKeyPressed(9)) {
       //CTRL + I
       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT":"EXIT INSERT")<<endl;
   } else if(ofGetKeyPressed(5)) {
       //CTRL + E
       isListening = false;
       cout<<"END"<<endl;
       cout<<"temp_msg:"<<temp_msg<<endl;
   } else if(isListening){
       if( key != 8 ){
           temp_msg += key;
       } else if (!temp_msg.empty()){
           temp_msg.erase(temp_msg.end() - 1);
       }
       //cout<<key<<endl;
       cout<<temp_msg<<endl;
   } else if(ofGetKeyPressed(3)){
       //CTRL + C
       create = true;
       remove = false;
       get    = false;
       set    = false;
       add    = false;
       action = "CREATE";
       cout<<action<<endl;
       mainObj = true;

   } else if(ofGetKeyPressed(18)){
       //CTRL + R
       create = false;
       remove = true;
       get    = false;
       set    = false;
       add    = false;
       action = "REMOVE";
       cout<<action<<endl;
       mainObj = true;


   } else if(ofGetKeyPressed(7)){
       //CTRL + G
       create = false;
       remove = false;
       get    = true;
       set    = false;
       add    = false;
       action = "GET";
       cout<<action<<endl;
       mainObj = true;


   } else if(ofGetKeyPressed(19)){
       //CTRL + S
       create = false;
       remove = false;
       get    = false;
       set    = true;
       add    = false;
       action = "SET";
       cout<<action<<endl;
       mainObj = true;


   } else if(ofGetKeyPressed(1)){
       //CTRL + A
       create = false;
       remove = false;
       get    = false;
       set    = false;
       add    = true;
       action = "ADD";
       cout<<action<<endl;
       mainObj = true;


   } else if(ofGetKeyPressed(112)){
       // P
       particle    = true;
       group       = false;
       behavior    = false;
       interaction = false;
       obj = "PARTICLE";
       if(mainObj) msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(103)){
       // G
       particle    = false;
       group       = true;
       behavior    = false;
       interaction = false;
       obj = "GROUP";
       if(mainObj) msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(98)){
       // B
       particle    = false;
       group       = false;
       behavior    = true;
       interaction = false;
       obj = "BEHAVIOR";
       if(mainObj) msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(105)){
       // I
       particle    = false;
       group       = false;
       behavior    = false;
       interaction = true;
       obj = "INTERACTION";
       if(mainObj) msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

   }
}

