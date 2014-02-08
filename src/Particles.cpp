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

void Particle :: setup() {}

void Particle :: run() {
    behave();
    interact();
    update();
}

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

void Particle :: behave() {
        for(vector<Behavior*>::iterator IterBehav = behaviors.itemsVector.begin();
                                        IterBehav != behaviors.itemsVector.end();
                                        IterBehav++){
            (*IterBehav)->run(this);
        }
}

void Particle :: interact() {
    Interaction* temp_interaction_ptr; 

    if ( interactions.itemsVector.size() > 0){
        
        for(vector<Interaction*>::iterator iter_interaction = interactions.itemsVector.end()-1;
                                        iter_interaction >= interactions.itemsVector.begin();
                                        iter_interaction--){
            temp_interaction_ptr = *iter_interaction;
            temp_interaction_ptr->run(this);
            if(!temp_interaction_ptr->isAlive) {
                cout<<"erase dead interaction"<<endl;
                interactions.erase(iter_interaction);
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

void Particle::set_ofVec3f(string var_name, ofVec3f var_ptr){
    ofVec3fPtr_map[var_name] = new ofVec3f(var_ptr); 
}

void Particle::delete_ofVec3f(string var_name){
    delete ofVec3fPtr_map[var_name]; 
    ofVec3fPtr_map.erase(var_name);    
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

//Circle::Circle(World* _world) : Particle(){

Circle::Circle() : Particle(){
    set_name("P_Circle");
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(color);
    ofEllipse(locat.x,locat.y,rad,rad);
}

Particle* Particles_Container::create_itemByName(string iName){//, World* _world){

    Items_Fabric nature;
    if (iName.size() == 0)
        iName = default_addedItemName;
    Particle* newParticle = nature.create_particle(iName);
    add(newParticle);

    return newParticle;

}

