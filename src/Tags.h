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
        void add_Particle(Particle* particle);
        void add_Interaction(Interaction* interaction);
        void add_Behavior(Behavior* behavior);
        void run();
        void behave();
        void interact();
};


