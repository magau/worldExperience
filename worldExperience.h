#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class BaseParticle{
    public:
        string iType;
        int id;
        BaseParticle ();
};

class DerivedParticle : public BaseParticle{
    public:
        DerivedParticle();
};

class Base_ParticlesSystem{
    public:
        int id;
        string psType;
        string default_iType;
        vector<BaseParticle*> itemsVector;
        vector<int> freeIdBuff;

        Base_ParticlesSystem();
        template <class IType>
        void add(IType item);
        void add_itemByType(string iType="");
        void set_default_pType(string iType);
        void pop(int index=(int)NULL);
        void pop_itemById(int id);
        void pop_itemByType(string iType);
        void reset_itemTypeById(int id, string iType="");
        void clear();
        void setup();
        vector <BaseParticle*> get_itemsByType(string iType="all");
};

class Derived_ParticlesSystem : public Base_ParticlesSystem{
    public:
        Derived_ParticlesSystem();
};

//class World{
//    public:
//    vector<Base_ParticlesSystem> base_particles_sys;
//    void add(string psType="basePS",string iType="baseP");
//    void get_info(string psType="all");
//};


