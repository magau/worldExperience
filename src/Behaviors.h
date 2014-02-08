class Particle;
class Interaction;
class Behavior;
class Master_Particle;
class Tag;

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

class Behavior : public Item{
    public:

        Behavior();
        /*
         * The purpose of the "setup" function is to add and/or
         * set sepecific variables required by the behavior to 
         * the particles taged with the tag hoast of this behavior.
         * This variables are used inside the "run" function of 
         * the behavior.
         * The "Particle" clase have a set of unordered_maps
         * that can be used for this purpose. The name of the 
         * behavior that creates the variable shoud be contained
         * at the variable key to avoid override variables used
         * by other behaviors or interacions.
         */ 
        virtual void setup(Particle* _host_particle);
        /*
         * The purpose of the "free" function is to delete
         * the variables added to the particles taged with 
         * the tag hoast of the behavior by the "setup" function.
         * This is called when ever a particle or the behavior
         * it self is removed from the hoast tag.
         */
        virtual void free(Particle* _host_particle);
        virtual void run(Particle* _host_particle);
    protected:
        int max_dist;
        int min_dist; 
        float weigth_fact;
};

class GravityGlue : public Behavior{
    public:
        GravityGlue();
        void run(Particle* _host_particle);
        void setup(Particle* _host_particle);
        void free(Particle* _host_particle);

    private:
        string location_key;
};

class MouseTracking : public Behavior{
    public:
        MouseTracking();
        void run(Particle* _host_particle);
};

class Behaviors_Container : public Pointers_Container<Behavior*>{
    public:
        Behavior* create_itemByName(string iName);
};
