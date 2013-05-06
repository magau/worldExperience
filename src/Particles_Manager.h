class World{
    public:
        Particles_Container particles;
        Pointers_Container<Particles_Container*> groups;
        Pointers_Container<Particles_System*> systems;
        //void add_ParticleSystemByType();
};

class World_Manager{
    public:
        World* world;
};
