class Tag : public Item {
    public:
        PointersVector<Particle*> particles;
        //PointersVector<Action*> actions;
        PointersVector<Interaction*> interactions;
        PointersVector<Behavior*> behaviors;
        Tag (World* _world);
        ~Tag();
        void add_particle(Particle* particle);
        void add_particles(PointersVector<Particle*> added_particles);
        Particle* get_particle_by_id(int particle_id);
        PointersVector<Particle*> get_particles_by_typeid(const type_info& particle_typeid);
        void remove_particle(Particle* particle);
        void free_particle(Particle* particle);
        void setup_particle(Particle* particle);
        void remove_particles(PointersVector<Particle*>* particles_selection=NULL);

        void setup_action(Action* action, bool isActive);

        Behavior* create_behavior(string behavior_name, bool isActive=true);
        Behavior* create_behavior(const type_info& behavior_typeid, bool isActive=true);
        PointersVector<Behavior*> get_behaviors_by_typeid(const type_info& behavior_typeid);
        Behavior* get_behavior_by_id(int behavior_id);
        void remove_behavior(Behavior* behavior);
        void remove_behaviors();

        Interaction* create_interaction(string interaction_name, bool isActive=true);
        Interaction* create_interaction(const type_info& interaction_typeid, bool isActive=true);
        Interaction* get_interaction_by_id(int interaction_id);
        PointersVector<Interaction*> get_interactions_by_typeid(const type_info& interaction_typeid);
        void remove_interaction(Interaction* interaction);
        void remove_interactions();

        void run();

        void set_listener(Button* button);
        void remove_listener(Button* button);
        void remove_attached_buttons();
        void free_attached_buttons(Particle* particle);
        void setup_attached_buttons(Particle* particle);
};


