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
<<<<<<< HEAD
=======
        //typedef tr1::unordered_map<char, int> ofVec3f_props;
        unordered_map<string, ofVec3f> ofVec3f_dict;
        //unordered_map<string, float> float_dict;
        //unordered_map<string, int> int_dict;
        //unordered_map<string, bool> bool_dict;
>>>>>>> cdbb2411b3da385291c1fe721803d2518652e7a8
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
<<<<<<< HEAD
        World* world;
        Particle_props();
        void test();
};

=======
        Particle_props();
        World* world;
};


>>>>>>> cdbb2411b3da385291c1fe721803d2518652e7a8
