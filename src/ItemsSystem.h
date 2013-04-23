#include "ofMain.h"

class Particle_props{
    public:
        ofVec3f locat;
        ofVec3f veloc;
        ofVec3f accel;
        ofPoint loc;
        ofPoint vel;
        ofPoint acc;
        ofColor color;
        int rad;
        float relax_threshold;
        float relax_fact;
        bool isAlive;
        Particle_props();
};

template <typename IType>
class Base_ItemsSystem{
    public:
        string name;
        int id;
        Particle_props props;
        string default_addedItemName;
        vector<IType> itemsVector;
        vector<int> freeIdBuff;

        Base_ItemsSystem(Particle_props init_props=Particle_props());
        void add(IType item);
        void set_default_itemName(string iName);
        void pop(int index=(int)NULL, bool erase=true);
        void pop_itemById(int id, bool erase=true);
        void pop_itemByName(string iName, bool erase=true);
        void clear(bool erase=true);
        vector <IType> get_itemsByName(string iName="all");
        virtual void add_itemByName(string iName="", Particle_props init_props=Particle_props());
        virtual void setup();
        virtual void update();
        virtual void run();
        /*
         "reset_itemTypeById" should be implemented in order to replace
         old items by newers of diferent types, passing the properties
         you plane to keep with from one to the other.
        virtual void reset_itemTypeById(int id, string iName="");
        */
};


