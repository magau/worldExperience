#include "ofMain.h"
#include "ItemsSystem.h"

//#include <iostream>
//#include <vector>
//#include <string>
//#include <iterator>
//using namespace std;

class Base_ParticlesSystem;

class Interaction {
    public:
        int id;
        string name;
        Particle_props props;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        vector<Base_ParticlesSystem>* world_ptr;
        Interaction(Particle_props init_props);
        virtual void run(Particle_props* actuatedParticle_props, Particle_props* p_props);
        virtual void update(Particle_props* p_props);
};

class Interaction_I : public Interaction{
    public:
        Interaction_I(Particle_props init_props);
        void run(Particle_props* actuatedParticle_props, Particle_props* p_props);
};

/*
class Interaction_II : public Interaction{
    public:
        Interaction_II(Particle_props init_props);
        void run(vector<Particle>* particlesVect_ptr);
};

class Interaction_III : public Interaction{
    public:
        Interaction_III(Particle_props init_props);
        void run(vector<Particle>* particlesVect_ptr);
};

class Interaction_IV : public Interaction{
    public:
        ofVec3f temp_loc;
        //vector <Interaction_III> generated_interactions;
        Interaction_IV(Particle_props init_props);
        void run(vector<Particle>* particlesVect_ptr);
};
*/

class BaseParticle: public Base_ItemsSystem<Interaction*>{
    public:
        BaseParticle (Particle_props init_props);
        //virtual void setup(Particle_props _props);
        void add_itemByName(string iName="",Particle_props init_props=Particle_props());
        virtual void run();
        virtual void update();
        virtual void display();
        void bound_particles_location();
        void set_speedLimit(int max_speed);
        void enable_screenElasticBoundery();
};

//class InteractiveParticle : public BaseParticle{
//    public:
//        InteractiveParticle (Particle_props init_props);
//        virtual void run(vector<BaseParticle>* actuated_particlesVect_ptr);
//        //virtual void interact(Particle* actuated_particle);
//        virtual void interact(vector<BaseParticle>* particlesVect_ptr);
//};
//
///*
//class DerivedParticle : public BaseParticle{
//    public:
//        DerivedParticle(Particle_props init_props);
//};
//*/
//
//class Base_ParticlesSystem : public Base_ItemsSystem<BaseParticle*>{
//    public:
//        Base_ParticlesSystem(Particle_props init_props);
//        void add_itemByName(string iName="",Particle_props init_props=Particle_props());
//        //set up the system particles initial position
//        virtual void setup();//unordered_map<int> setupParameters);
//        //call the run() method for every particles
//        virtual void run();
//        virtual void interact(Base_ParticlesSystem* actuated_PS);
//};

/*
class Derived_ParticlesSystem : public Base_ParticlesSystem{
    public:
        Derived_ParticlesSystem();
};
*/

//class RegularGrid_ParticlesSystem : public Base_ParticlesSystem{
//    public:
//        RegularGrid_ParticlesSystem(Particle_props init_props);
//        //void setup(Particle_props init_props, unordered_map<int> setupParameters);
//        void setup(int particles_distance, ofPoint grid_size=ofPoint(1));
//};
//
///*
//class mouse_ParticlesSystem : public Interactions_System {
//    public:
//        vector <Interaction_I> interactions;
//        void setup();
//        void update(ofVec3f locat);
//        void run(vector<Particle>* particlesVect_ptr);
//};
//
//class mouseParticlesGenerator_ParticlesSystem : public Interactions_System {
//    public:
//        //vector <Interaction_IV> interactions;
//        int min_dist; 
//        u_int default_type;
//        void setup();
//        void update(ofVec3f locat);
//        void run(vector<Particle>* particlesVect_ptr);
//};
//*/
//
//class Base_World : public Base_ItemsSystem<Base_ParticlesSystem*>{
//    public:
//        Base_World();
//        void add_itemByName(string iName="",Particle_props init_props=Particle_props());
//};
//
