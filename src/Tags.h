class Tag : public Item {
    public:
        Particles_Container particles;
        Actions_Container actions;
        Tag (World* _world);
        ~Tag();
        void add_particle(Particle* particle);
        void add_particles(vector<Particle*> added_particles);
        void remove_particle(Particle* particle);
        //void free(Item* item);
        void free_particle(Particle* particle);
        void remove_particles(vector<Particle*> added_particles);
        void add_action(Action* action);
        Action* add_action(string action_name);
        void remove_action(Action* interaction);
        void remove_actions();
        void add_interaction(Interaction* interaction);
        Interaction* add_interaction(string interaction_name);
        void remove_interaction(Interaction* interaction);
        void add_behavior(Behavior* behavior);
        Behavior* add_behavior(string behavior_name);
        void remove_behavior(Behavior* behavior);
        void run();
        void behave();
        void interact();
        void actuate();
};
