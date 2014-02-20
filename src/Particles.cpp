#include "testApp.h"

Particle :: Particle () : Item(){

    name = "P_Base";
    rad = 6;
    ofVec3fPtr_map["loc"]      = &locat;
    ofVec3fPtr_map["vel"]      = &veloc;
    ofVec3fPtr_map["acc"]      = &accel;
    ofColorPtr_map["color"]    = &color;
    intPtr_map["rad"]          = &rad;
    floatPtr_map["relax_fact"] = &relax_fact;
    boolPtr_map["isAlive"]     = &isAlive;
}

Particle :: Particle (World* _world){
    Particle ();
    set_world(_world);
}

Particle :: ~Particle (){
    vector<Tag*>::iterator iter_tag;
    for (iter_tag = tags.itemsVector.begin();
         iter_tag < tags.itemsVector.end();
         iter_tag++){
        (*iter_tag)->remove_particle(this);
    }
}

void Particle::setup(){}

void Particle::run(){update();}

// Method to display
void Particle :: display() {}

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

Circle::Circle() : Particle(){
    set_name("P_Circle");
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(color);
    ofEllipse(locat.x,locat.y,rad,rad);
}

Particle* Particles_Container::create_itemByName(string iName){

    Items_Fabric nature;
    if (iName.size() == 0)
        iName = default_addedItemName;
    Particle* newParticle = nature.create_particle(iName);
    add(newParticle);

    return newParticle;

}
