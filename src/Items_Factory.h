class Items_Factory{
    public:
        Particle*    create_particle(const type_info& _type_id);
        Behavior*    create_behavior(const type_info& _type_id);
        Interaction* create_interaction(const type_info& _type_id);
        Particle*    create_particle(string name);
        Behavior*    create_behavior(string name);
        Interaction* create_interaction(string name);
};


