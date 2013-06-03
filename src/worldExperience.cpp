#include "testApp.h"

void Particle_props :: test(){

    //ofVec3f_dict.insert(ofVec3f_dict::value_type("loc", ofVec3f(float(NULL))));
}

Particle_props :: Particle_props(){
    
    locat = ofVec3f(float(NULL));
    veloc = ofVec3f(float(NULL));
    accel = ofVec3f(float(NULL));
    color = ofColor(float(NULL));
    rad = int(NULL);
    relax_fact = float(NULL);
    isAlive = true;

    //ofVec3fPtr_map["loc"]      = &locat;
    //ofVec3fPtr_map["vel"]      = &veloc;
    //ofVec3fPtr_map["acc"]      = &accel;
    //ofColorPtr_map["color"]    = &color;
    //intPtr_map["rad"]          = &rad;
    //floatPtr_map["relax_fact"] = &relax_fact;
    //boolPtr_map["isAlive"]     = &isAlive;

    //*(intPtr_map["rad"]) = 10;

//cout<<"Particle_props contructur... rad = "<<rad<<endl;
}
