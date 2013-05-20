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

         interact(&(*actuatedParticle_it)->props);
    }
}

/*
void Interaction::update(Particle_props* p_props){

}
*/


Electrical_Repulsion::Electrical_Repulsion(Particle_props* host_props) :
Interaction(host_props){
    //props = init_props;
    name = "Electrical_Repulsion";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}


void Electrical_Repulsion::interact(Particle_props* actuatedParticle_props){
    float dist,dx,dy,weight,weight_fact,acc;
    //Particle* actuated_particle;

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
    //Particle* actuated_particle;

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
    //     actuated_particle->props.relax_fact *= 0.95;
    //     //actuated_particle->props.relax_fact *= 0.7;
    // }
}

Interaction* Interactions_Container::add_itemByName(string iName, Particle_props* init_props){

   Interaction* newInteraction = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
       //cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("Electrical_Repulsion") == 0){
       newInteraction = new Electrical_Repulsion(init_props);
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("Electrical_Attraction") == 0){
       newInteraction = new Electrical_Attraction(init_props);
       //add(new DerivedParticle());
       //cout<<"add item, iName:"<<iName<<endl;
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


