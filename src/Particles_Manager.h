class World{
    public:
        Particles_Container particles;
        Tags_Container tags;
        World();
        Tag* create_tag(string iName="");
        void remove_tag(Tag* tag);
        Particle* create_particle(string iName);
        void add_particle(Particle* particle);
        void remove_particle(Particle* particle_ptr);
        Particles_Container* update();
        void draw();
};

