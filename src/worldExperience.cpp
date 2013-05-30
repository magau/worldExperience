#include "testApp.h"

Particle_props :: Particle_props(){

    
    //typename unordered_map<string,ofVec3f> :: ofVec3f_dict.insert(ofVec3f_dict::value_type("loc", ofVec3f(float(NULL))));
    //ofVec3f_dict.insert(ofVec3f_dict::value_type("loc", ofVec3f(float(NULL))));
    //ofVec3f_dict.insert(ofVec3f_dict::value_type("vel", ofVec3f(float(NULL))));
    //ofVec3f_dict.insert(ofVec3f_dict::value_type("acc", ofVec3f(float(NULL))));
    //int_dict.insert(int_dict::value_type("rad", int(NULL)));
    //float_dict.insert(float_dict::value_type("relax_fact", float(NULL)));
    //bool_dict.insert(bool_dict::value_type("isAlive", bool(NULL)));

    locat = ofVec3f(float(NULL));
    veloc = ofVec3f(float(NULL));
    accel = ofVec3f(float(NULL));
    color = ofColor(float(NULL));
    rad = int(NULL);
    relax_fact = float(NULL);
    isAlive = true;
}
