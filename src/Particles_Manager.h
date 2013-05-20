class Groups_Container : public Pointers_Container<Particles_Container*>{

};

class World{
    public:
        Particles_Container particles;
        Groups_Container groups;
        //Pointers_Container<Particles_Container*> groups;
        //Pointers_Container<Particles_System*> systems;
        //void add_ParticleSystemByType();
};

class World_Manager{
    public:
        World* world;
        //Particles_Container* create_group(string iName="Generic");
        Particle* create_particle(string iName, Particle_props init_props=Particle_props());
        //Particles_Container* create_regularGrid(int particles_distance, float windowRatio);
        Particles_Container* update();
        void draw();
};

class Manager_KeyboardInterface{
    public:
        string msg;
        bool isListening;
        void start();
        void listen(int key);
};
