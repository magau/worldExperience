class Tag : public Item {
    public:
        ofEvent<bool_attr> bool_event;
        ofEvent<int_attr> int_event;
        ofEvent<float_attr> float_event;
        ofEvent<ofVec3f_attr> ofVec3f_event;
        ofEvent<ofColor_attr> ofColor_event;

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

        void add_listener_to_particles(string attr_name);
        //template <typename T>
        //void add_listener_to_particles(ofEvent<T>* event){
        //    vector<Particle*>::iterator iter_particle;
        //    for (iter_particle = particles.itemsVector.begin();
        //         iter_particle < particles.itemsVector.end();
        //         iter_particle++){
        //        (*iter_particle)->add_listener(*event);
        //    } 
        //}

        //void add_bool_listener_to_particles(ofEvent<bool_attr>* event);
};


