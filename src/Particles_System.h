
class Master_Particle : public Particle{
    public:
        string default_Particle;
        string default_Interaction;
        //unordered_map<float> interactionsMaster;
        Particles_Container* slaveParticles;
        Master_Particle(Particle_props init_props=Particle_props());
        //void add_itemByName(string iName="",Particle_props init_props=Particle_props());
        //set up the system particles initial position
        void create_slaveContainer();
        void create_slaveParticle(Particle_props init_props);
        virtual void setup();//unordered_map<int> setupParameters);
        //call the run() method for every particles
        virtual void run();
        //virtual void interact(Base_ParticlesSystem* actuated_PS);
};


/*
class Derived_ParticlesSystem : public Base_ParticlesSystem{
    public:
        Derived_ParticlesSystem();
};
*/

class RegularGrid_MP : public Master_Particle{
    public:
        RegularGrid_MP(Particle_props init_props);
        //void setup(Particle_props init_props, unordered_map<int> setupParameters);
        void setup(int particles_distance, float windowRatio);
};

/*
class mouse_ParticlesSystem : public Interactions_System {
    public:
        vector <Interaction_I> interactions;
        void setup();
        void update(ofVec3f locat);
        void run(vector<Particle>* particlesVect_ptr);
};

class mouseParticlesGenerator_ParticlesSystem : public Interactions_System {
    public:
        //vector <Interaction_IV> interactions;
        int min_dist; 
        u_int default_type;
        void setup();
        void update(ofVec3f locat);
        void run(vector<Particle>* particlesVect_ptr);
};
*/

//class ParticlesSystems_Container : public Pointers_Container<Master_Particle*>{
//    public:
//        void add_itemByName(string iName,Particle_props init_props);
//};


