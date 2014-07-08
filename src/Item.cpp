#include "testApp.h"

Item::Item(){
    //cout << "item constructor..." << endl;
    is_alive = Item_Parameter<bool>(true);
    is_active = Item_Parameter<bool>(true);
    set_item_parameter<bool>("is_alive",&is_alive);
    set_item_parameter<bool>("is_active",&is_active);
}

Item :: ~Item(){
    /* delete added variables. */
}

const type_info& Item::get_typeid(){
    return typeid(this);
}

string Item::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

string Item::get_name(){return name;}

void Item::print_shared_var_names(){
    for(unordered_map<string,pair<void*,pair<size_t,bool>>>::const_iterator var_it = var_ptr_map.begin();
        var_it != var_ptr_map.end(); var_it++) {
        //cout << "var:" << var_it->first << endl;
        size_t str_token = var_it->first.find(":");
        string var_name = var_it->first.substr(0,str_token);
        Item* host_item = (Item*) strtoul(var_it->first.substr(str_token+1).c_str(),NULL,0);
        cout << "var:" << var_name << " - " << host_item->get_name() << endl;
    }
}

void Item::print_events_names(){
    for(unordered_map<string,pair<void*,pair<size_t,bool>>>::const_iterator var_it = events_ptr_map.begin();
        var_it != events_ptr_map.end(); var_it++) {
        size_t str_token = var_it->first.find(":");
        string event_name = var_it->first.substr(0,str_token);
        Item* host_item = (Item*) strtoul(var_it->first.substr(str_token+1).c_str(),NULL,0);
        cout << "event:" << event_name << " - " << host_item->get_name() << endl;
    }
}

int    Item::get_id(){return id;}

World* Item::get_world(){return world;}

void   Item::set_name(string _name){name=_name;}

void   Item::set_id(int _id){id=_id;}

void   Item::set_world(World* _world){world=_world;}

void   Item::iterate_attribute(string attr_name, bool forward){}

void   Item :: setup(){}

void   Item :: run(){}

