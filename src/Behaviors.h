//#include "testApp.h"
//#include "ofMain.h"

class Behavior{
    public:
        int id;
        string itemType;
        Particle_props* props;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        ParticlesManager* manager;
        Behavior(Particle_props* host_props);
        void run();//Particle_props* p_props);
};

class Behaviors_Container : public Pointers_Container<Behavior*>{
    public:
        void add_itemByName(string iName, Particle_props* init_props);
};


