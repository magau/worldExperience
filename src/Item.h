class World;
class Particle;
class Interaction;
class Behavior;

class Item{

    public:
        Item();
        string get_name();
        int get_id();
        World* get_world();
        bool is_alive();
        bool is_active();
        void set_name(string _name);
        void set_id(int _id);
        void set_world(World* _world);
        void set_live_state(bool live_state);
        void set_active_state(bool active_state);

        //The main base classes are friends because only the extreme
        //qualified team members are supposed to rewrite them. heheh!!
        friend class Particle; 
        friend class Interaction; 
        friend class Behavior; 
        friend class Master_Particle; 
        friend class Tag; 

    private:
        World* world;
        bool isAlive, isActive;
        int id;
        string name;
};

class Items_Fabric{
    public:
        Particle*    create_particle(string name);
        Behavior*    create_behavior(string name);
        Interaction* create_interaction(string name);
};
