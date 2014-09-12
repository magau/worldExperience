class World_Camera : public ofCamera, public Item{
    public:
        World_Camera(){
           set_callback("orbit_x",(void (Item::*)(shared_variable*)) (&World_Camera::orbit_x));
           set_callback("orbit_y",(void (Item::*)(shared_variable*)) (&World_Camera::orbit_y));
        }

        void orbit_x(shared_variable* shv_imput_param){
            Item_Parameter<float> view_angle(0.0,pair<float,float>(-18.0,18.0));
            shared_variable shv_view_angle(&view_angle,IP_FLOAT);
            map_shv_parameter(&shv_view_angle, shv_imput_param);
            //testing...
            cout << "x viewing angle:" << view_angle.value <<endl;
        }

        void orbit_y(shared_variable* shv_imput_param){
            Item_Parameter<float> view_angle(0.0,pair<float,float>(-18.0,18.0));
            shared_variable shv_view_angle(&view_angle,IP_FLOAT);
            map_shv_parameter(&shv_view_angle, shv_imput_param);
            //testing...
            cout << "y viewing angle:" << view_angle.value <<endl;
        }
};

class World {
    public:
        World_Camera camera;
        Items_Factory nature;
        PointersVector<Particle*> particles;
        PointersVector<Tag*> tags;
        PointersVector<Controller*> controllers;
        World();
        Tag* create_tag(string iName="");
        void remove_tag(Tag* tag);
        Controller* create_controller(string iName, bool isActive=true);
        Controller* create_controller(const type_info& controller_type, bool isActive=true);
        Particle* create_particle(string iName, bool isActive=true);
        Particle* create_particle(const type_info& particle_type, bool isActive=true);
        PointersVector<Particle*> get_particle_by_typeid(const type_info& particle_typeid);
        Particle* get_particle_by_id(int particle_id);
        void remove_particle(Particle* particle_ptr);
        PointersVector<Particle*>* update();
        void draw();
};
