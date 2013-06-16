class World{
    public:
        Particles_Container particles;
        Groups_Container groups;
        //void add_ParticleSystemByType();
        World();
        Particles_Container* create_group(string iName="Generic");
        Particle* create_particle(string iName);
        void remove_particle(Particle* particle_ptr);
        Particles_Container* update();
        void draw();
};

class Manager_KeyboardInterface{
    public:
        World* world;
        Particles_Container* buffer_group;
        Particle* buffer_particle;
        Interaction* buffer_interaction;
        Behavior* buffer_behavior; 
        string temp_msg, msg, action, obj;
        bool isListening, mainObj, create, remove, get, set, add, particle, group, behavior, interaction;
        void start(World* _world);
        void listen(int key);
};
