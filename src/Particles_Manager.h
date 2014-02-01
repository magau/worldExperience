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
        Particles_Container* buffer_particles_group;
        Interactions_Container* buffer_interactions_group;
        Behaviors_Container* buffer_behaviors_group;
        Particle* buffer_particle;
        Interaction* buffer_interaction;
        Behavior* buffer_behavior; 
        vector <Particle*> buffer_particles_vector;
        vector <Interaction*> buffer_interactions_vector;
        vector <Behavior*> buffer_behaviors_vector;
        vector <Particles_Container*> buffer_groups_vector;
        string temp_msg, msg, action, obj, obj_name;
        bool isListening, by_name, by_id, create, remove, get, set, add, particle, particles, group, groups, behavior, behaviors, interaction, interactions;
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
        // This functio gets behaviors from a vector<Particle*>
        // and stors them in the buffer_behaviors_vector 
        void get_behaviors_by_name(string& obj_name, vector<Particle*>* source_items);
        void get_interactions_by_name(string& obj_name, vector<Particle*>* source_items);
        
};
