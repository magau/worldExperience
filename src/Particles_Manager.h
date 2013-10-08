class World{
    public:
        Particles_Container particles;
        Groups_Container groups;
        //void add_ParticleSystemByType();
        World();
        Particles_Container* create_group(string iName="Generic");
        Particle* create_particle(string iName);
        void remove_particle(Particle* particle_ptr);
        Particles_Container* update();
        void draw();
};

class Manager_KeyboardInterface{
    public:
        World* world;
        Particles_Container* buffer_group;
        Interactions_Container buffer_interactions;
        Behaviors_Container buffer_behaviors;
        Particle* buffer_particle;
        Interaction* buffer_interaction;
        Behavior* buffer_behavior; 
        vector <Particle*> particles_vector;
        vector <Interaction*> interactions_vector;
        vector <Behavior*> behaviors_vector;
        vector <Particles_Container*> groups_vector;
        string temp_msg, msg, action, obj, obj_name;
        bool isListening, by_name, by_id, create, remove, get, set, add, particle, particles, group, behavior, interaction;
        int obj_id;
        unordered_map<string, string> particle_name, interaction_name, behavior_name, group_name;

        Manager_KeyboardInterface(); 
        void start(World* _world);
        void listen(int key);
        void get_availableItems_names(unordered_map<string,string> names_map);
        void update_availableItems_names(unordered_map<string,string>* names_map, string new_entry);
        void reset_objects();
        void reset_actions();
        void decode_kb_msg(string encoded_msg);
        void stateFabric_update(string _msg);
        void stateFabric_decode();
};
