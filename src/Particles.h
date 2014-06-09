class Particle : public Item {
    public:
        Item_Parameter<ofVec3f> loc, vel, acc;
        Item_Parameter<ofColor> color;
        Item_Parameter<int> rad;
        Item_Parameter<float> relax;
        Item_Parameter<bool> visible;

        PointersVector<Tag*> tags;

        Particle ();
        ~Particle();

        virtual string get_type_name();
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
        const type_info& get_typeid();
        string get_type_name();
        void display();
};



