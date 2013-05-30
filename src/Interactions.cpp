#include "testApp.h"

Interaction::Interaction(Particle_props* host_props){
    props = host_props;
}

void Interaction::interact(Particle_props* actuatedParticle_props){

}

void Interaction::run(){
    vector<Particle*>::iterator actuatedParticle_it;

    for (actuatedParticle_it = actuated_particles->itemsVector.begin();
         actuatedParticle_it != actuated_particles->itemsVector.end();
         actuatedParticle_it++){

         interact(&(**actuatedParticle_it).props);
    }
}

Electrical_Repulsion::Electrical_Repulsion(Particle_props* host_props) :
Interaction(host_props){
    name = "Electrical_Repulsion";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}


void Electrical_Repulsion::interact(Particle_props* actuatedParticle_props){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.2;
    //weight_fact = 0.25;

    weight = max_dist*weight_fact;

    dist = props->ofVec3f_map["loc"].distance(actuatedParticle_props->ofVec3f_map["loc"]);
    dx = actuatedParticle_props->ofVec3f_map["loc"].x - props->ofVec3f_map["loc"].x;
    dy = actuatedParticle_props->ofVec3f_map["loc"].y - props->ofVec3f_map["loc"].y;
    acc = weight / pow(dist,2);
    actuatedParticle_props->ofVec3f_map["acc"].x += dx * acc;
    actuatedParticle_props->ofVec3f_map["acc"].y += dy * acc;
    ////Do not aplly relaxation at the bounthery wall  
    //int offset = actuatedParticle_props->rad;
    //if (actuatedParticle_props->locat.x > offset &&
    //    actuatedParticle_props->locat.x < ofGetWindowWidth() - offset &&
    //    actuatedParticle_props->locat.y > offset &&
    //    actuatedParticle_props->locat.y < ofGetWindowHeight() - offset ){

    //    actuatedParticle_props->relax_fact = 0.7;
    //}
} 

Electrical_Attraction::Electrical_Attraction(Particle_props* host_props) :
Interaction(host_props){
    name = "Electrical_Attraction";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void Electrical_Attraction::interact(Particle_props* actuatedParticle_props){
    float dist,dx,dy,weight,weight_fact,acc;

    weight_fact = 0.1;
    min_dist = 40;
    weight = max_dist*weight_fact;

    dist = props->ofVec3f_map["loc"].distance(actuatedParticle_props->ofVec3f_map["loc"]);
    dx = actuatedParticle_props->ofVec3f_map["loc"].x - props->ofVec3f_map["loc"].x;
    dy = actuatedParticle_props->ofVec3f_map["loc"].y - props->ofVec3f_map["loc"].y;

    if (dist < min_dist) dist = min_dist;
    acc = weight / pow(dist,2);

    actuatedParticle_props->ofVec3f_map["acc"].x += - dx * acc;
    actuatedParticle_props->ofVec3f_map["acc"].y += - dy * acc;

    // //Over relaxation
    // if (dist == min_dist) {
    //     actuatedParticle_props->relax_fact *= 0.95;
    //     //actuatedParticle_props->relax_fact *= 0.7;
    // }
}

Wave_Source :: Wave_Source(Particle_props* host_props) :
Interaction(host_props){
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

         interact(&(**actuatedParticle_it).props);
    }
   
    timer += wave_speed;
}

void Wave_Source :: interact(Particle_props* actuatedParticle_props){
    //Particle* actuated_particle;
    float dist,acc,size_ds;
    ofPoint ds, dir, wavePos;

    ds.x = actuatedParticle_props->ofVec3f_map["loc"].x - props->ofVec3f_map["loc"].x;
    ds.y = actuatedParticle_props->ofVec3f_map["loc"].y - props->ofVec3f_map["loc"].y;
    size_ds = ofVec3f(0).distance(ds);
    dir.set(ds.x/size_ds,ds.y/size_ds);
    
    wavePos.set(props->ofVec3f_map["loc"].x + timer * dir.x, props->ofVec3f_map["loc"].y + timer * dir.y);
    dist = actuatedParticle_props->ofVec3f_map["loc"].distance(wavePos);
    if (dist > max_dist) {
        props->bool_map["isAlive"] = false;
        isAlive = false;
    } else {

        if (dist < min_dist) dist = min_dist;

        acc = weight / pow(dist,2);

        ds.x = actuatedParticle_props->ofVec3f_map["loc"].x - wavePos.x ;
        ds.y = actuatedParticle_props->ofVec3f_map["loc"].y - wavePos.y;
        actuatedParticle_props->ofVec3f_map["acc"].x += ds.x * acc;
        actuatedParticle_props->ofVec3f_map["acc"].y += ds.y * acc;

//        cout<<"dir.x:"<<dir.x<<" wavePos.x:"<<wavePos.x<<" ds.x:"<<ds.x<<" dist:"<<dist<<endl;

        ////Do not aplly relaxation at the bounthery wall  
        //int offset = actuatedParticle_props->rad;
        //if (actuatedParticle_props->locat.x > offset &&
        //    actuatedParticle_props->locat.x < ofGetWindowWidth() - offset &&
        //    actuatedParticle_props->locat.y > offset &&
        //    actuatedParticle_props->locat.y < ofGetWindowHeight() - offset ){

        //    actuatedParticle_props->relax_fact = 0.9;
        //    //actuatedParticle_props->relax_fact = 0.7;
        //}
    } 

    
}


Interaction* Interactions_Container::add_itemByName(string iName, Particle_props* init_props){

   Interaction* newInteraction = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
   } 

   if (iName.compare("Electrical_Repulsion") == 0){
       newInteraction = new Electrical_Repulsion(init_props);
   } else if (iName.compare("Electrical_Attraction") == 0){
       newInteraction = new Electrical_Attraction(init_props);
   } else if (iName.compare("Wave_Source") == 0){
       newInteraction = new Wave_Source(init_props);
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


