//class Particles_Container;
//class Tags_Container;

class Particle : public Item {
    public:
        ofVec3f locat, veloc, accel;
        ofColor color;
        int rad;
        float relax_fact;
        bool _is_visible;

        PointersVector<Tag*> tags;

        Particle ();
        ~Particle();

        virtual void setup();
        virtual void run();
        virtual void update();
        virtual void display();
        virtual const type_info& get_typeid();
        bool is_visible();
        void set_visible(bool _is_visible);
        //void bound_particles_location();
        //void set_speedLimit(int max_speed);
        void elastic_boundery();
};

class Circle : public Particle{
    public:
        Circle ();
        void display();
        const type_info& get_typeid();
};



