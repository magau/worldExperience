class World{
    public:
        Items_Fabric nature;
        Particles_Container particles;
        Tags_Container tags;
        World();
        Tag* create_tag(string iName="");
        void remove_tag(Tag* tag);
        Action* create_action(string iName);
        Behavior* create_behavior(string iName);
        Interaction* create_interaction(string iName);
        Particle* create_particle(string iName);
        void add_particle(Particle* particle);
        void remove_particle(Particle* particle_ptr);
        Particles_Container* update();
        void draw();
};

