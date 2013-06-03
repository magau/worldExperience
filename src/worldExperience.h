//#include "ofMain.h"

//#include <iostream>
//#include <vector>
//#include <string>
//#include <iterator>
//#include <unordered_map> 
//using namespace std;

class World;

class Particle_props{
    public:
        ofVec3f locat;
        ofVec3f veloc;
        ofVec3f accel;
        //ofPoint loc;
        //ofPoint vel;
        //ofPoint acc;
        ofColor color;
        int rad;
        float relax_threshold;
        float relax_fact;
        bool isAlive;
        World* world;
        Particle_props();
        void test();
};

