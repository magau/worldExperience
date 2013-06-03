//#include "testApp.h"
//#include "ofMain.h"

class Behavior{
    public:
        u_int id;
        string name;
        Particle_props* props;
        bool isAlive, isActive;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        World* world;
        Behavior(Particle_props* host_props);
        virtual void run();
};

class GravityGlue : public Behavior{
    public:
        ofVec3f locat;
        GravityGlue(Particle_props* host_props);
        void run();
};

class MouseTracking : public Behavior{
    public:
        MouseTracking(Particle_props* host_props);
        void run();
};

class Behaviors_Container : public Pointers_Container<Behavior*>{
    public:
        Behavior* add_itemByName(string iName, Particle_props* host_props);
};
