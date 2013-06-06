class Groups_Container : public Pointers_Container<Particles_Container*>{

};

class World{
    public:
        Particles_Container particles;
        Groups_Container groups;
        //void add_ParticleSystemByType();
        Particles_Container* create_group(string iName="Generic");
        Particle* create_particle(string iName);
        void remove_particle(Particle* particle_ptr);
        Particles_Container* update();
        void draw();
};

class Manager_KeyboardInterface{
    public:
        Particles_Container* buffer_group;
        Particle* buffer_particle;
        string msg;
        bool isListening, create, remove, get, set, add, particle, group, behavior, interaction;
        void start();
        void listen(int key);
};
