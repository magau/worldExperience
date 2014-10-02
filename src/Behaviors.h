class Master_Particle;
class Tag;

class Behavior : public Action{
    public:
        Behavior();
        virtual const type_info& get_typeid();
        string get_type_name();
    protected:
        int max_dist;
        int min_dist; 
        float weigth_fact;
};

class GravityGlue : public Behavior{
    public:
        GravityGlue();
        const type_info& get_typeid();
        string get_type_name();
        void run(Particle* _host_particle);
        void setup(Particle* _host_particle);
        void free(Particle* _host_particle);
        //void setup();
        void free();
    private:
        string location_key;
        Item_Parameter<float> weight_fac;
};

class MouseTracking : public Behavior{
    public:
        MouseTracking();
        const type_info& get_typeid();
        string get_type_name();
        void run(Particle* _host_particle);
        void setup(){};
};


