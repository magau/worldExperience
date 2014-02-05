#include "testApp.h"


Particle :: Particle (World* _world){

    name="P_Base";
    world = _world;
    ofVec3fPtr_map["loc"]      = &locat;
    ofVec3fPtr_map["vel"]      = &veloc;
    ofVec3fPtr_map["acc"]      = &accel;
    ofColorPtr_map["color"]    = &color;
    intPtr_map["rad"]          = &rad;
    floatPtr_map["relax_fact"] = &relax_fact;
    boolPtr_map["isAlive"]     = &isAlive;
    isAlive = true;
    isActive = true;
}

Particle :: ~Particle (){
    vector<Particles_Container*>::iterator iterGroup;

    cout<<"destructing particle; id:"<<id<<endl;

    for (iterGroup = groups.itemsVector.begin();
         iterGroup != groups.itemsVector.end();
         iterGroup++){
        (*iterGroup)->pop_itemById(id);
    }

    behaviors.erase_all();
    interactions.erase_all();
}

void Particle :: setup() {

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
    veloc += accel;
    elastic_boundery();
    locat += veloc;
    //Aplly relax_fact
    veloc *= ofVec3f(relax_fact);
    relax_fact = 1.0;
    //bound_particles_location();

    // Clear accelaration to allow comulative 
    // interactions and order independency:
    accel = ofVec3f(0);
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
cout<<"erase dead interaction"<<endl;
                interactions.erase(IterInterac);
            }
        }
    }
}

/*
void Particle :: bound_particles_location(){
   int offset = rad;

   if (locat.x < offset){
       locat.x = offset;
   } else if (locat.x > ofGetWindowWidth()-offset){
       locat.x = ofGetWindowWidth()-offset;
   }
   if (locat.y < offset){
       locat.y = offset;
   } else if (locat.y > ofGetWindowHeight()-offset){
       locat.y = ofGetWindowHeight()-offset;
   }
}

void Particle :: set_speedLimit(int maxSpeed){
   
   if (veloc.x < -1 * maxSpeed){
       veloc.x = -1 * maxSpeed;
   } else if (veloc.x > maxSpeed){
       veloc.x = maxSpeed;
   }
   if (veloc.y < -1 * maxSpeed){
       veloc.y = -1 * maxSpeed;
   } else if (veloc.y > maxSpeed){
       veloc.y = maxSpeed;
   }
}
*/

void Particle :: elastic_boundery(){
    int offset = rad;

    //Elastic bounds
    if ( (locat.x <= offset &&  veloc.x < 0) ||
         (locat.x >= ofGetWindowWidth()-offset &&  veloc.x > 0) ){
        veloc.x *= -1;
    }
    if ( (locat.y <= offset && veloc.y < 0) ||
         (locat.y >= ofGetWindowHeight()-offset && veloc.y > 0) ){
        veloc.y *= -1;
    }
}

void Particle::set_var(string var_name, ofVec3f var_ptr){

    ofVec3fPtr_map[var_name] = new ofVec3f(var_ptr); 
    
}

ofVec3f* Particle::get_ofVec3f(string var_name){
    //cout << var_name << ": " << (*(ofVec3fPtr_map[var_name])) << endl;
    return ofVec3fPtr_map[var_name];
    //unordered_map<string, ofVec3f*>::iterator iter_map_ptr = ofVec3fPtr_map.find(var_name);
    //if (iter_map_ptr == ofVec3fPtr_map.end()) {
    //    var_ptr = (ofVec3f*)NULL;
    //} else {
    //    cout << "var_name:" << var_name << " var_value:" << *(ofVec3fPtr_map[var_name]) << endl;
    //    var_ptr = ofVec3fPtr_map[var_name];
    //}
    //return;
    //for( iter_map_ptr = ofVec3fPtr_map.begin();
    //     iter_map_ptr < ofVec3fPtr_map.end();
    //     iter_map_ptr++ ){
    //    if(iter_map_ptr->first == var_name)
    //        var_ptr = iter_map_ptr->second;
    //        return;
    //} 
}

Circle::Circle(World* _world) : Particle(_world){
    name="P_Circle";
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(color);
    ofEllipse(locat.x,locat.y,rad,rad);
}

Particle* Particles_Container::add(Particle* particle, bool mainContainer){
    Pointers_Container<Particle*>::add(particle, mainContainer);
    if(!mainContainer) {
        particle->groups.add(this,false);
    }
    return particle;
}

Particle* Particles_Container::add_itemByName(string iName, World* _world){

   Particle* newParticle = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
   } 

   if (iName.compare("P_Base") == 0){
       newParticle = new Particle(_world);
   } else if (iName.compare("P_Circle") == 0){
       newParticle = new Circle(_world);
   } else if (iName.compare("MP_RegGrid") == 0){
       newParticle = new RegularGrid_MP(_world);
   }

   /*
    .
    .
    .
       Add new item types
   */
//cout<<"add_itemByName... rad = "<<rad<<endl;
//*(intPtr_map["rad"]) = 10;
//cout<<"add_itemByName...*intPtr_map['rad'] = "<<*(newParticle->intPtr_map["rad"])<<endl;
//cout<<"add_itemByName... rad = "<<newParticle->rad<<endl;

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

