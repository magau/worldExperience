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
        Behavior();
        Behavior(Particle* host_particle);
        virtual void setup(Particle* _host_particle);
        virtual void free(Particle* _host_particle);
        virtual void run(Particle* _host_particle = (Particle*)NULL);
};

class GravityGlue : public Behavior{
    public:
        ofVec3f locat;
        GravityGlue();
        GravityGlue(Particle* host_particle);
        void run(Particle* _host_particle = (Particle*)NULL);
        void setup(Particle* _host_particle);
        void free(Particle* _host_particle);
};

class MouseTracking : public Behavior{
    public:
        MouseTracking();
        MouseTracking(Particle* host_particle);
        void run(Particle* _host_particle = (Particle*)NULL);
};

class Behaviors_Container : public Pointers_Container<Behavior*>{
    public:
        Behavior* add_itemByName(string iName, Particle* host_particle=(Particle*)NULL);
        //Behavior* add_itemByName(string iName);
};
