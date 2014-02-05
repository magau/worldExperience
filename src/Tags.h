class Tag{
    public:
        int id;
        string name;
        World* world;
        bool isAlive, isActive;

        Particles_Container particles;
        Interactions_Container interactions;
        Behaviors_Container behaviors;
        Tag (World* _world);
        ~Tag();
        void add_particle(Particle* particle);
        void add_particles(vector<Particle*> added_particles);
        void add_interaction(Interaction* interaction);
        Interaction* add_interaction(string interaction_name);
        void add_behavior(Behavior* behavior);
        Behavior* add_behavior(string behavior_name);
        void run();
        void behave();
        void interact();
};


