#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class BaseParticle{
    public:
        string name;
        int id;
        BaseParticle ();
};

class DerivedParticle : public BaseParticle{
    public:
        DerivedParticle();
};

template <typename IType>
class Base_ItemsSystem{
    public:
        int id;
        string name;
        string default_addedItemName;
        vector<IType> itemsVector;
        vector<int> freeIdBuff;

        Base_ItemsSystem();
        void add(IType item);
        void set_default_itemName(string iName);
        void pop(int index=(int)NULL);
        void pop_itemById(int id);
        void pop_itemByName(string iName);
        void clear();
        vector <IType> get_itemsByName(string iName="all");
        virtual void add_itemByName(string iName="");
        virtual void setup();
        virtual void update();
        virtual void run();
        /*
         "reset_itemTypeById" should be implemented in order to replace
         old items by newers of diferent types, passing the properties
         you plane to keep with from one to the other.
        */
        virtual void reset_itemTypeById(int id, string iName="");
};

class Base_ParticlesSystem : public Base_ItemsSystem<BaseParticle*>{
    public:
        Base_ParticlesSystem();
        void add_itemByName(string iName="");
        void setup();
};

class Derived_ParticlesSystem : public Base_ParticlesSystem{
    public:
        Derived_ParticlesSystem();
};

class Base_World : public Base_ItemsSystem<Base_ParticlesSystem*>{
    public:
        Base_World();
        void add_itemByName(string iName="");
};


