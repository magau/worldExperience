//#include "testApp.h"
//#include "ofMain.h"

class Behavior{
    public:
        int id;
        string name;
        Particle_props* props;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        World* world;
        Behavior(Particle_props* host_props);
        virtual void run();//Particle_props* p_props);
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


