#include "testApp.h"

Particle_props :: Particle_props(){
    locat = ofVec3f(float(NULL));
    veloc = ofVec3f(float(NULL));
    accel = ofVec3f(float(NULL));
    color = ofColor(float(NULL));
    rad = int(NULL);
    relax_fact = float(NULL);
    isAlive = true;
}
