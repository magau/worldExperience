class Master_Particle : public Particle{
    public:
        string default_Particle;
        //Particles_Container* slaveParticles;
        Master_Particle();
        //set up the system particles initial position
        Particle* create_slaveParticle();
        void run();
        virtual void setup();
};

class RegularGrid_MP : public Master_Particle{
    public:
        int particles_distance;
        float windowRatio;
        RegularGrid_MP();
        void setup();
};

