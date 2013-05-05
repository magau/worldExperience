
class Particles_Container : public Pointers_Container<Particle*>{
    
};

class Particles_System : public Particle{
    public:
        int id;
        string itemType;
        string default_Particle;
        string default_Interaction;
        ParticlesManager* manager;
        Particles_Container* hostParticles;
        Particles_Container* actuatedParticles;
        Particles_System(Particle_props init_props);
        //void add_itemByName(string iName="",Particle_props init_props=Particle_props());
        //set up the system particles initial position
        virtual void setup();//unordered_map<int> setupParameters);
        //call the run() method for every particles
        virtual void run();
        //virtual void interact(Base_ParticlesSystem* actuated_PS);
};


class ParticlesManager{
    public:
        Particles_Container worldParticles;
        Pointers_Container<Particles_Container*> groups;
        Pointers_Container<Particles_System*> systems;
        //void add_ParticleSystemByType();
};

/*
class Derived_ParticlesSystem : public Base_ParticlesSystem{
    public:
        Derived_ParticlesSystem();
};
*/

class RegularGrid_PS : public Particles_System{
    public:
        RegularGrid_PS(Particle_props init_props);
        //void setup(Particle_props init_props, unordered_map<int> setupParameters);
        void setup(int particles_distance, ofPoint grid_size=ofPoint(1));
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

