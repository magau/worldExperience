class Master_Particle : public Particle{
    public:
        string default_Particle;
        string default_Interaction;
        //unordered_map<float> interactions_master;
        Particles_Container* slaveParticles;
        Master_Particle(World* _world);
        //set up the system particles initial position
        Particles_Container* create_slaveContainer();
        Particle* create_slaveParticle();
        void run();
        virtual void setup();//unordered_map<int> setupParameters);
};


class RegularGrid_MP : public Master_Particle{
    public:
        int particles_distance;
        float windowRatio;
        RegularGrid_MP(World* _world);
        void setup();
        //void setup(unordered_map<int> setupParameters);
        //void setup(int particles_distance, float windowRatio);
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

