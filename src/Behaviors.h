class Master_Particle;
class Tag;

class Behavior : public Action{
    public:

        Behavior();
        /*
         * The purpose of the "setup" function is to add and/or
         * set sepecific variables required by the behavior to 
         * the particles taged with the tag host of this behavior.
         * This variables are used inside the "run" function of 
         * the behavior.
         * The "Particle" class have a set of unordered_maps
         * that can be used for this purpose. The name of the 
         * behavior that creates the variable shoud be contained
         * at the variable key to avoid override variables used
         * by other behaviors or interactions.
         */ 
        //virtual void setup(Particle* _host_particle);
        //virtual void setup();
        /*
         * The purpose of the "free" function is to delete
         * the variables added to the particles taged with 
         * the tag host of the behavior by the "setup" function.
         * This is called when ever a particle or the behavior
         * it self is removed from the host tag.
         */
        //virtual void free(Particle* _host_particle);
        //virtual void free(Item* _host_item);
        //virtual void run(Particle* _host_particle);
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
        void setup();
        void free();
        //void free(Item* _host_item);

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
