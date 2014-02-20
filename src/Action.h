class Tag;
class Item;

class Action : public Item{
    public:
        Action();
        void add_tag(Tag* tag);
        Tag* get_tag();
        virtual void setup(Action* host_action);
        virtual void setup(Interaction* host_particle);
        virtual void setup(Particle* host_particle);
        virtual void free(Particle* host_particle);
        virtual void setup();
        virtual void free();
        virtual void run();
        virtual void run(Particle* _host_particle);

    private:
        Tag* _tag;

};

class Actions_Container : public Pointers_Container<Action*>{
    public:
        Action* create_itemByName(string iName);
};

