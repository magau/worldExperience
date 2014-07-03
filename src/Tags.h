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
        void remove_particles(PointersVector<Particle*> added_particles);

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

        template<typename T>
        void add_listener_to_particles(string event_name, Item* host_item_ptr) {
                                       //void (*callback)(pair<pair<string,Item*>,Item_Parameter<T>>& keypair_val)){
            ofEvent<pair<string,Item_Parameter<T>>>* event_ptr = host_item_ptr->get_event<T>(event_name);
            set_event<T>(event_name, event_ptr, host_item_ptr);
            PointersVector<Particle*>::iterator iter_particle;
            for (iter_particle = particles.begin();
                iter_particle != particles.end();
                iter_particle++){
                (*iter_particle)->add_listener<T>(event_ptr);
            }
        }

        template<typename T>
        void remove_listener_from_particles(string event_name, Item* host_item_ptr) {
            ofEvent<pair<string,Item_Parameter<T>>>* event_ptr = host_item_ptr->get_event<bool>(event_name);
            erase_event<T>(event_name, host_item_ptr);
            PointersVector<Particle*>::iterator iter_particle;
            for (iter_particle = particles.begin();
                iter_particle != particles.end();
                iter_particle++){
                (*iter_particle)->remove_listener<T>(event_ptr);
            }
        }


        void remove_listener_from_particles(string event_name);
};


