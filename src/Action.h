class Tag;
class Item;

class Action : public Item{
    public:
        Action();
        void add_tag(Tag* tag);
        Tag* get_tag();
        /*
         * The purpose of the "setup" function is to add and/or
         * set sepecific variables required by the action to 
         * the particles taged with the tag host of this action.
         * This variables are used inside the "run" function of 
         * the action.
         * The "Particle" class have a set of unordered_maps
         * that can be used for this purpose. The name and id of
         * the action that creates the variable shoud be contained
         * at the variable key to avoid override variables used
         * by other actions.
         */ 
        virtual void setup();
        virtual void setup(Particle* host_particle);
        /*
         * The purpose of the "free" function is to delete
         * the variables added to the particles taged with 
         * the tag host of the action by the "setup" function.
         * This is called when ever a particle or the action
         * it self is removed from the host tag.
         */
        virtual void free();
        virtual void free(Particle* host_particle);
        virtual void run();
        virtual void run(Particle* _host_particle);
    private:
        Tag* _tag;

};


