//class Particles_Container;
//class Tag;
class Tags_Container;// : public Pointers_Container<Tag*>{};

class Interaction : public Action {
    public:

        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        PointersVector<Tag*> actuated_tags;

        Interaction();
        const type_info& get_typeid();
        virtual void run(){Action::run();};
        virtual void run(Particle* _host_particle);
        virtual void interact(Particle* actuated_particle, Particle* _host_particle);
        void add_actuated_tag(Tag* tag);
        void remove_actuated_tag(Tag* tag);
        
    protected:
        Tag* tag;
};

class Electrical_Repulsion : public Interaction{
    public:
        Electrical_Repulsion();
        const type_info& get_typeid();
        void interact(Particle* actuated_particle, Particle* _host_particle);
    private:
        Item_Parameter<float> weight_fac;
};

class Electrical_Attraction : public Interaction{
    public:
        Electrical_Attraction();
        const type_info& get_typeid();
        void interact(Particle* actuated_particle, Particle* _host_particle);
};

class Wave_Source : public Interaction{
    public:
        int wave_speed;
        float weight,weight_fact;

        Wave_Source();
        const type_info& get_typeid();
        void interact(Particle* actuated_particle, Particle* _host_particle);
        void run(Particle* _host_particle);
};


class DrawLine : public Interaction {
    public:
        DrawLine();
        const type_info& get_typeid();
        void interact(Particle* actuated_particle, Particle* _host_particle);
        void run(Particle* _host_particle);
        void setup();
        void setup(Particle* _host_particle);
        void free();
        void free(Particle* host_particle);
        //PointersVector<Particle*> lines;
        //PointersVector<Tag*> lines_vertices;
};


/*
class Interaction_IV : public Interaction{
    public:
        ofVec3f temp_loc;
        //vector <Interaction_III> generated_interactions;
        Interaction_IV(Particle* _host_particle);
        void interact(Particle* actuated_particle);
};
*/

//class Interactions_Container : public Pointers_Container<Interaction*>{};
