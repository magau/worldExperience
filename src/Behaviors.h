class Master_Particle;
class Tag;

class Behavior : public Action{
    public:
        Behavior();
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
    private:
        string location_key;
};

class MouseTracking : public Behavior{
    public:
        MouseTracking();
        void run(Particle* _host_particle);
};
