#include "testApp.h"


Particle :: Particle (Particle_props init_props){
    props = init_props;
}

void Particle :: run() {
    behave();
    interact();
    update();
}

// Method to display
void Particle :: display() {

}

void Particle :: update() {
    props.ofVec3f_map["vel"] += props.ofVec3f_map["acc"];
    elastic_boundery();
    props.ofVec3f_map["loc"] += props.ofVec3f_map["vel"];
    //Aplly relax_fact
    props.ofVec3f_map["vel"] *= ofVec3f(props.relax_fact);
    props.relax_fact = 1.0;
    //bound_particles_location();

    // Clear accelaration to allow comulative 
    // interactions and order independency:
    props.ofVec3f_map["acc"] = ofVec3f(0);
}

void Particle :: behave() {
        for(vector<Behavior*>::iterator IterBehav = behaviors.itemsVector.begin();
                                        IterBehav != behaviors.itemsVector.end();
                                        IterBehav++){
            (*IterBehav)->run();
        }
}

void Particle :: interact() {
    Interaction* temp_interaction_ptr; 

    if ( interactions.itemsVector.size() > 0){
        
        for(vector<Interaction*>::iterator IterInterac = interactions.itemsVector.end()-1;
                                        IterInterac >= interactions.itemsVector.begin();
                                        IterInterac--){
            temp_interaction_ptr = *IterInterac;
            temp_interaction_ptr->run();
            if(!temp_interaction_ptr->isAlive) {
cout<<"pop dead interaction"<<endl;
                interactions.pop(IterInterac);
            }
        }
    }
}

/*
void Particle :: bound_particles_location(){
   int offset = props.rad;

   if (props.locat.x < offset){
       props.locat.x = offset;
   } else if (props.locat.x > ofGetWindowWidth()-offset){
       props.locat.x = ofGetWindowWidth()-offset;
   }
   if (props.locat.y < offset){
       props.locat.y = offset;
   } else if (props.locat.y > ofGetWindowHeight()-offset){
       props.locat.y = ofGetWindowHeight()-offset;
   }
}

void Particle :: set_speedLimit(int maxSpeed){
   
   if (props.veloc.x < -1 * maxSpeed){
       props.veloc.x = -1 * maxSpeed;
   } else if (props.veloc.x > maxSpeed){
       props.veloc.x = maxSpeed;
   }
   if (props.veloc.y < -1 * maxSpeed){
       props.veloc.y = -1 * maxSpeed;
   } else if (props.veloc.y > maxSpeed){
       props.veloc.y = maxSpeed;
   }
}
*/

void Particle :: elastic_boundery(){
   int offset = props.int_map["rad"];

   //Elastic bounds
   if ( (props.ofVec3f_map["loc"].x <= offset &&  props.ofVec3f_map["vel"].x < 0) ||
        (props.ofVec3f_map["loc"].x >= ofGetWindowWidth()-offset &&  props.ofVec3f_map["vel"].x > 0) ){
       props.ofVec3f_map["vel"].x *= -1;
   }
   if ( (props.ofVec3f_map["loc"].y <= offset && props.ofVec3f_map["vel"].y < 0) ||
        (props.ofVec3f_map["loc"].y >= ofGetWindowHeight()-offset && props.ofVec3f_map["vel"].y > 0) ){
       props.ofVec3f_map["vel"].y *= -1;
   }
}

Circle::Circle(Particle_props init_props) :
                     Particle(init_props){
    name="P_Circle";
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(props.ofColor_map["surf"]);
    ofEllipse(props.ofVec3f_map["loc"].x,props.ofVec3f_map["loc"].y,props.int_map["rad"],props.int_map["rad"]);
}

Particle* Particles_Container::add_itemByName(string iName,Particle_props init_props){

   Particle* newParticle = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
   } 

   if (iName.compare("baseP") == 0){
       newParticle = new Particle(init_props);
   } else if (iName.compare("P_Circle") == 0){
       newParticle = new Circle(init_props);
   } else if (iName.compare("MP_RegGrid") == 0){
       newParticle = new RegularGrid_MP(init_props);
   }

   /*
    .
    .
    .
       Add new item types
   */

   add(newParticle);

   return newParticle;

}


// This two methods must be transfered to the Master_Particle class, in Future...

void Particles_Container::attachInteraction_one2one(string iName, Particles_Container* actuated_particles){
//    typename vector<Particles*>::iterator particle_it;
//    for (particle_it = itemsVector.begin();
//         particle_it != itemsVector.end();
//         particle_it++){
//        particle = *particle_it;
//        particle->interactions.        
//
//    }
//
}

void Particles_Container::attachInteraction_many2one(string iName, Particles_Container* actuated_particles){

}

