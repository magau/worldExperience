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

        virtual void setup();
        virtual void run();
        virtual void update();
        virtual void display();
        virtual const type_info& get_typeid();
        //bool is_visible();
        //void set_visible(bool _is_visible);
        //void bound_particles_location();
        //void set_speedLimit(int max_speed);
        void elastic_boundery();
};

class Circle : public Particle{
    public:
        Circle ();
        const type_info& get_typeid();
        void display();
};

class Sphere : public Particle{
    public:
        Sphere ();
        ofSpherePrimitive sphere;
        int tmp_rad;
        float spin_fac;
        const type_info& get_typeid();
        void display();
};

class Line : public Particle{
    public:
        Line();
        const type_info& get_typeid();
        void update();
        void display();
        ofPolyline points;
};

