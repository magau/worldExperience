class Items_Fabric{
    public:
        Particle*    create_particle(string name);
        Behavior*    create_behavior(string name);
        Interaction* create_interaction(string name);
        Action*      create_action(string name);
};

class World{
    public:
        Items_Fabric nature;
        Particles_Container particles;
        Tags_Container tags;
        World();
        Tag* create_tag(string iName="");
        void remove_tag(Tag* tag);
        Behavior* create_behavior(string iName);
        Interaction* create_interaction(string iName);
        Action* create_action(string iName);
        Particle* create_particle(string iName, bool materialize=true);
        void activate_particle(Particle* particle);
        void remove_particle(Particle* particle_ptr);
        Particles_Container* update();
        void draw();
};
