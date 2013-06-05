#include "testApp.h"

Interaction::Interaction(Particle* _host_particle){
    host_particle = _host_particle;
    isAlive = true;
    isActive = true;
}

void Interaction::interact(Particle* actuated_particle){

}

void Interaction::run(){
    vector<Particle*>::iterator actuatedParticle_it;

    for (actuatedParticle_it = actuated_particles->itemsVector.begin();
         actuatedParticle_it != actuated_particles->itemsVector.end();
         actuatedParticle_it++){

         interact(*actuatedParticle_it);
    }
}

Electrical_Repulsion::Electrical_Repulsion(Particle* _host_particle) :
Interaction(_host_particle){
    name = "Electrical_Repulsion";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}


void Electrical_Repulsion::interact(Particle* actuated_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.2;
    //weight_fact = 0.25;

    weight = max_dist*weight_fact;

    dist = host_particle->locat.distance(actuated_particle->locat);
    dx = actuated_particle->locat.x - host_particle->locat.x;
    dy = actuated_particle->locat.y - host_particle->locat.y;
    acc = weight / pow(dist,2);
    actuated_particle->accel.x += dx * acc;
    actuated_particle->accel.y += dy * acc;
    ////Do not aplly relaxation at the bounthery wall  
    //int offset = actuated_particle->rad;
    //if (actuated_particle->locat.x > offset &&
    //    actuated_particle->locat.x < ofGetWindowWidth() - offset &&
    //    actuated_particle->locat.y > offset &&
    //    actuated_particle->locat.y < ofGetWindowHeight() - offset ){

    //    actuated_particle->relax_fact = 0.7;
    //}
} 

Electrical_Attraction::Electrical_Attraction(Particle* _host_particle) :
Interaction(_host_particle){
    name = "Electrical_Attraction";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void Electrical_Attraction::interact(Particle* actuated_particle){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.1;
    min_dist = 40;
    weight = max_dist*weight_fact;

    dist = host_particle->locat.distance(actuated_particle->locat);
    dx = actuated_particle->locat.x - host_particle->locat.x;
    dy = actuated_particle->locat.y - host_particle->locat.y;

    if (dist < min_dist) dist = min_dist;
    acc = weight / pow(dist,2);

    actuated_particle->accel.x += - dx * acc;
    actuated_particle->accel.y += - dy * acc;

    // //Over relaxation
    // if (dist == min_dist) {
    //     actuated_particle->relax_fact *= 0.95;
    //     //actuated_particle->relax_fact *= 0.7;
    // }
}

Wave_Source :: Wave_Source(Particle* _host_particle) :
Interaction(_host_particle){
    name = "Wave_Source";
    min_dist=80;
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    weight_fact = 0.05;
    weight = max_dist*weight_fact;
    timer = 0;
    wave_speed = 5;
    isAlive = true;
}

void Wave_Source :: run(){
    //Interaction :: run();
    vector<Particle*>::iterator actuatedParticle_it;

    for (actuatedParticle_it = actuated_particles->itemsVector.begin();
         actuatedParticle_it != actuated_particles->itemsVector.end();
         actuatedParticle_it++){

         interact(*actuatedParticle_it);
    }
   
    timer += wave_speed;
}

void Wave_Source :: interact(Particle* actuated_particle){
    //Particle* actuated_particle;
    float dist,acc,size_ds;
    ofPoint ds, dir, wavePos;

    ds.x = actuated_particle->locat.x - host_particle->locat.x;
    ds.y = actuated_particle->locat.y - host_particle->locat.y;
    size_ds = ofVec3f(0).distance(ds);
    dir.set(ds.x/size_ds,ds.y/size_ds);
    
    wavePos.set(host_particle->locat.x + timer * dir.x, host_particle->locat.y + timer * dir.y);
    dist = actuated_particle->locat.distance(wavePos);
    if (dist > max_dist) {
        host_particle->isAlive = false;
        isAlive = false;
    } else {

        if (dist < min_dist) dist = min_dist;

        acc = weight / pow(dist,2);

        ds.x = actuated_particle->locat.x - wavePos.x ;
        ds.y = actuated_particle->locat.y - wavePos.y;
        actuated_particle->accel.x += ds.x * acc;
        actuated_particle->accel.y += ds.y * acc;

//        cout<<"dir.x:"<<dir.x<<" wavePos.x:"<<wavePos.x<<" ds.x:"<<ds.x<<" dist:"<<dist<<endl;

        ////Do not aplly relaxation at the bounthery wall  
        //int offset = actuated_particle->rad;
        //if (actuated_particle->locat.x > offset &&
        //    actuated_particle->locat.x < ofGetWindowWidth() - offset &&
        //    actuated_particle->locat.y > offset &&
        //    actuated_particle->locat.y < ofGetWindowHeight() - offset ){

        //    actuated_particle->relax_fact = 0.9;
        //    //actuated_particle->relax_fact = 0.7;
        //}
    } 

    
}


Interaction* Interactions_Container::add_itemByName(string iName, Particle* _host_particle){

   Interaction* newInteraction = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
   } 

   if (iName.compare("Electrical_Repulsion") == 0){
       newInteraction = new Electrical_Repulsion(_host_particle);
   } else if (iName.compare("Electrical_Attraction") == 0){
       newInteraction = new Electrical_Attraction(_host_particle);
   } else if (iName.compare("Wave_Source") == 0){
       newInteraction = new Wave_Source(_host_particle);
   }
   /*
    .
    .
    .
       Add new item types
   */

   add(newInteraction);

   return newInteraction;
}


