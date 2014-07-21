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
    for(unordered_map<string,pair<void*,pair<arg_t,bool>>>::const_iterator var_it = var_ptr_map.begin();
        var_it != var_ptr_map.end(); var_it++) {
        //cout << "var:" << var_it->first << endl;
        size_t str_token = var_it->first.find(":");
        string var_name = var_it->first.substr(0,str_token);
        Item* host_item = (Item*) strtoul(var_it->first.substr(str_token+1).c_str(),NULL,0);
        cout << "var:" << var_name << " - " << host_item->get_name() << endl;
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

arg_t  Item::get_event_arg_t(string event_name, Item* item_ptr) {
    string var_key;
    if (item_ptr == NULL)
        var_key=string(event_name + ":" + to_string((long unsigned int)this));
    else
        var_key=string(event_name + ":" + to_string((long unsigned int)item_ptr));

    unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
    arg_t event_arg_t = T_NULL;
    //unordered_map <string,arg_t>::iterator map_it = events_arg_t_map.find(event_name);
    if (map_it == var_ptr_map.end())
       cout << "Invalid event name:" << event_name << "." << endl;
    else
       event_arg_t = map_it->second.second.first;
    //   event_arg_t = map_it->second;
    return event_arg_t;
}


