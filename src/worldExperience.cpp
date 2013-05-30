#include "testApp.h"

void Particle_props :: test(){

    //ofVec3f_dict.insert(ofVec3f_dict::value_type("loc", ofVec3f(float(NULL))));
}

Particle_props :: Particle_props(){
    
    ofVec3f_map["loc"] = ofVec3f(float(NULL));
    ofVec3f_map["vel"] = ofVec3f(float(NULL));
    ofVec3f_map["acc"] = ofVec3f(float(NULL));
    ofColor_map["surf"] = ofColor(float(NULL));
    int_map["rad"] = int(NULL);
    float_map["relax_fact"] = float(NULL);
    bool_map["isAlive"] = bool(NULL);

    locat = ofVec3f(float(NULL));
    veloc = ofVec3f(float(NULL));
    accel = ofVec3f(float(NULL));
    color = ofColor(float(NULL));
    rad = int(NULL);
    relax_fact = float(NULL);
    isAlive = true;
}
