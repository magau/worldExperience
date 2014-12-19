class Master_Particle;
class Tag;

class Behavior : public Action{
    public:
        Behavior();
        virtual const type_info& get_typeid();
    protected:
        int max_dist;
        int min_dist; 
        float weigth_fact;
};

class GravityGlue : public Behavior{
    public:
        GravityGlue();
        const type_info& get_typeid();
        void update_particle(Particle* _host_particle);
        void setup_particle(Particle* _host_particle);
        void free(Particle* _host_particle);
        void free();
    private:
        string location_key;
        Item_Parameter<float> weight_fac;
};

class MouseTracking : public ofThread, public Behavior {
    public:
        int x,y;
        MouseTracking();
        ~MouseTracking();
        const type_info& get_typeid();
        void update_particle(Particle* _host_particle);
        void threadedFunction(){
            while(true){
                lock();
                x = ofGetMouseX();
                y = ofGetMouseY();
                unlock();
            }
        }

};

class ParticlesManager : Behavior{
    public:
        Item_Parameter_VectorOfofVect3f particles_tracker;
        const type_info& get_typeid();
        void update_particle(Particle* _host_particle);
        void setup_particle(Particle* _host_particle);
        void free(Particle* _host_particle);
        void create_particle();
        void erase_particle();
};

