class Tag : public Item {
    public:
        ofEvent<bool_attr> bool_event;
        ofEvent<int_attr> int_event;
        ofEvent<float_attr> float_event;
        ofEvent<ofVec3f_attr> ofVec3f_event;
        ofEvent<ofColor_attr> ofColor_event;

        Particles_Container particles;
        Interactions_Container interactions;
        Behaviors_Container behaviors;
        Tag (World* _world);
        ~Tag();
        void add_particle(Particle* particle);
        void add_particles(vector<Particle*> added_particles);
        void remove_particle(Particle* particle);
        //void free(Item* item);
        void free_particle(Particle* particle);
        void remove_particles(vector<Particle*> added_particles);
        //void add_action(Action* action);
        //Action* add_action(string action_name);
        //void remove_action(Action* interaction);
        //void remove_actions();
        void add_interaction(Interaction* interaction);
        Interaction* add_interaction(string interaction_name);
        void remove_interaction(Interaction* interaction);
        void remove_interactions();
        void add_behavior(Behavior* behavior);
        Behavior* add_behavior(string behavior_name);
        void remove_behavior(Behavior* behavior);
        void remove_behaviors();
        void run();
        //void actuate();

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
