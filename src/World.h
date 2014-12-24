class World {
    public:
        World_Camera camera;
        ofLight light;
        Items_Factory nature;
        PointersVector<Particle*> particles;
        PointersVector<Tag*> tags;
        PointersVector<Controller*> controllers;
        World();
        Tag* create_tag(string iName="");
        void remove_tag(Tag* tag);
        Controller* create_controller(string iName, bool isActive=true);
        Controller* create_controller(const type_info& controller_type, bool isActive=true);
        Controller* add_controller(Controller* controller, bool isActive=true);
        Particle* create_particle(string iName, bool isActive=true);
        Particle* create_particle(const type_info& particle_type, bool isActive=true);
        PointersVector<Particle*> get_particle_by_typeid(const type_info& particle_typeid);
        Particle* get_particle_by_id(Particle* particle_ptr);
        void remove_particle(Particle* particle_ptr);
        void remove_particles(PointersVector<Particle*>* particles);
        PointersVector<Particle*>* update();
        void draw();
};
