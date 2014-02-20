#include "testApp.h"

Action::Action() : Item(){}
void Action::add_tag(Tag* tag){_tag = tag;}
Tag* Action::get_tag(){return _tag;}
void Action::setup(Action* particle){}
void Action::setup(Interaction* particle){}
void Action::setup(Particle* particle){}
void Action::free(Particle* particle){}
void Action::setup(){}
void Action::free(){}
void Action::run(Particle* _host_particle){}

Action* Actions_Container::create_itemByName(string iName){

    Items_Fabric nature;
    if (iName.size() == 0)
        iName = default_addedItemName;
    Action* newAction = nature.create_action(iName);
    add(newAction);

    return newAction;
}


