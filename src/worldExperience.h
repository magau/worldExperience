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
        unordered_map<string, ofVec3f> ofVec3f_map;
        unordered_map<string, ofColor> ofColor_map;
        unordered_map<string, int> int_map;
        unordered_map<string, float> float_map;
        unordered_map<string, bool> bool_map;

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

