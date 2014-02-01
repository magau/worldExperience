#include "testApp.h"


Tag :: Tag (World* _world){

    name="no_name_tag";
    world = _world;
    isAlive = true;
    isActive = true;
}

Tag :: ~Tag (){

    cout << "Removing particles, interactions and behaviors from tag." << endl;

    particles.clear();    
    behaviors.erase_all();
    interactions.erase_all();
}

void Tag::add_Particle(Particle* particle){
    particles.add(particle,false); 
}

void Tag::add_Interaction(Interaction* interaction){
    interactions.add(interaction);
}

void Tag::add_Behavior(Behavior* behavior){
    behaviors.add(behavior);
}

void Tag::run(){
    behave();
    interact();
}

void Tag::behave(){
    vector<Particle*>::iterator iter_particle;
    vector<Behavior*>::iterator iter_behavior;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle != particles.itemsVector.end();
         iter_particle++){
         
         for (iter_behavior = behaviors.itemsVector.begin();
              iter_behavior != behaviors.itemsVector.end();
              iter_behavior++){
                  (*iter_behavior)->run(*iter_particle);
         }
    }
}

void Tag::interact(){
    vector<Particle*>::iterator iter_particle;
    vector<Interaction*>::iterator iter_interaction;
    for (iter_particle = particles.itemsVector.begin();
         iter_particle != particles.itemsVector.end();
         iter_particle++){
         
         for (iter_interaction = interactions.itemsVector.begin();
              iter_interaction != interactions.itemsVector.end();
              iter_interaction++){
                  //iter_interaction.run(iter_particle);
                  cout << "interaction runing in dead mode..." << endl;

         }
    }
}
