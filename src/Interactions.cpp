#include "testApp.h"

Interaction::Interaction(Particle_props* host_props){
    props = host_props;
}

void Interaction::interact(Particle_props* actuatedParticle_props){

}

void Interaction::run(){
    vector<Particle*>::iterator actuatedParticle_it;

  cout<<" loop over actuated_particles start"<<endl;
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

    dist = props->locat.distance(actuatedParticle_props->locat);
    dx = actuatedParticle_props->locat.x - props->locat.x;
    dy = actuatedParticle_props->locat.y - props->locat.y;
    acc = weight / pow(dist,2);
    actuatedParticle_props->accel.x += dx * acc;
    actuatedParticle_props->accel.y += dy * acc;
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

    dist = props->locat.distance(actuatedParticle_props->locat);
    dx = actuatedParticle_props->locat.x - props->locat.x;
    dy = actuatedParticle_props->locat.y - props->locat.y;

    if (dist < min_dist) dist = min_dist;
    acc = weight / pow(dist,2);

    actuatedParticle_props->accel.x += - dx * acc;
    actuatedParticle_props->accel.y += - dy * acc;

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
    wave_speed = 4;
    isAlive = true;
}

void Wave_Source :: interact(Particle_props* actuatedParticle_props){
    //Particle* actuated_particle;
    float dist,acc,size_ds;
    ofPoint ds, dir, wavePos;

//    props->isAlive = false;
    //for (u_int j=0; j<particlesVect_ptr->size(); j++){
    //    actuated_particle = &(*particlesVect_ptr)[j];
    ds.x = actuatedParticle_props->locat.x - props->locat.x;
    ds.y = actuatedParticle_props->locat.y - props->locat.y;
    size_ds = ofDist(0,0,ds.x,ds.y);
    //size_ds = ofVec3f(0).distance(ds);
    dir.set(ds.x/size_ds,ds.y/size_ds);
    
    wavePos.set(props->locat.x + timer * dir.x, props->locat.y + timer * dir.y);
    dist = ofDist(actuatedParticle_props->locat.x,actuatedParticle_props->locat.y,wavePos.x,wavePos.y);
   // dist = actuatedParticle_props->locat.distance(wavePos);
    if (dist > max_dist) {
        props->isAlive = false;
        isAlive = false;
    } else {

        if (dist < min_dist) dist = min_dist;
        //dist = ofDist(actuatedParticle_props->locat.x,actuatedParticle_props->locat.y,wavePos.x,wavePos.y);

        //dist = ofDist(actuatedParticle_props->loc.x,actuatedParticle_props->loc.y,props->loc.x,props->loc.y);
        //if (dist < min_dist) dist = 25;//min_dist;
        acc = weight / pow(dist,2);

        //ds.x = actuatedParticle_props->loc.x - props->loc.x ;
        //ds.y = actuatedParticle_props->loc.y - props->loc.y ;
        ds.y = actuatedParticle_props->locat.y - wavePos.y;
        actuatedParticle_props->accel.x += ds.x * acc;
        actuatedParticle_props->accel.y += ds.y * acc;

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
        timer += wave_speed;
    } 

   //if (props->isAlive) timer += wave_speed;
    
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


