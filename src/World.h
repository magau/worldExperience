class World{
    public:
        Items_Factory nature;
        PointersVector<Particle*> particles;
        PointersVector<Tag*> tags;
        World();
        Tag* create_tag(string iName="");
        void remove_tag(Tag* tag);
        Particle* create_particle(string iName, bool isActive=true);
        Particle* create_particle(const type_info& particle_typeid, bool isActive=true);
        PointersVector<Particle*> get_particle_by_typeid(const type_info& particle_typeid);
        Particle* get_particle_by_id(int particle_id);
        void remove_particle(Particle* particle_ptr);
        PointersVector<Particle*>* update();
        void draw();
};
