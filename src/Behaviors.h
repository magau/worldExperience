//#include "testApp.h"
//#include "ofMain.h"

class Behavior{
    public:
        int id;
        string name;
        Particle* host_particle;
        bool isAlive, isActive;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        World* world;
        Behavior(Particle* host_particle);
        virtual void run();
};

class GravityGlue : public Behavior{
    public:
        ofVec3f locat;
        GravityGlue(Particle* host_particle);
        void run();
};

class MouseTracking : public Behavior{
    public:
        MouseTracking(Particle* host_particle);
        void run();
};

class Behaviors_Container : public Pointers_Container<Behavior*>{
    public:
        Behavior* add_itemByName(string iName, Particle* host_particle);
};
