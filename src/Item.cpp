#include "testApp.h"

Item::Item(){
    //cout << "item constructor..." << endl;
    is_alive = Item_Parameter<bool>(true);
    is_active = Item_Parameter<bool>(true);
    set_variable("is_alive", &is_alive, IP_BOOL);
    set_variable("is_active", &is_active, IP_BOOL);
    set_name(get_type_name());
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
    for(unordered_map<string,pair<void*,pair<arg_t,bool>>>::iterator var_it = var_ptr_map.begin();
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

arg_t  Item::get_event_arg_t(string event_name, Item* host_item_ptr) {
    string var_key;
    if (host_item_ptr == NULL)
        var_key=string(event_name + ":" + to_string((long unsigned int)this));
    else
        var_key=string(event_name + ":" + to_string((long unsigned int)host_item_ptr));

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

void* Item::create_var_ptr(arg_t type_enum){
    void* var_ptr = NULL;
    switch (type_enum) {
        case EVENT_IP_BOOL:
            var_ptr = new ofEvent<pair<string,Item_Parameter<bool>>>;
            break;
        case EVENT_IP_INT:
            var_ptr = new ofEvent<pair<string,Item_Parameter<int>>>;
            break;
        case EVENT_IP_FLOAT:
            var_ptr = new ofEvent<pair<string,Item_Parameter<float>>>;
            break;
        case EVENT_IP_DOUBLE:
            var_ptr = new ofEvent<pair<string,Item_Parameter<double>>>;
            break;
        case IP_INT:
            var_ptr = new Item_Parameter<int>;
            break;
        case IP_FLOAT:
            var_ptr = new Item_Parameter<float>;
            break;
        case IP_BOOL:
            var_ptr = new Item_Parameter<bool>;
            break;
        case IP_VEC3F:
            var_ptr = new Item_Parameter<ofVec3f>;
            break;
        case IP_COLOR:
            var_ptr = new Item_Parameter<ofColor>;
            break;
        case CTRL_INT:
            var_ptr = new pair<vector<string>,pair<Item_Parameter<int>, ofEvent<pair<string,Item_Parameter<int>>>>>;
            break;
        case T_NULL:
            cout << "Can't create new variable! arg_t not defined for this type!!" << endl;
            break;
        default:
            cout << "Can't create new variable! arg_t not defined for this type!!" << endl;
            break;
    }
    return var_ptr;
}

void Item::erase_var_ptr(void* var_value, arg_t type_enum){
    switch (type_enum) {
        case EVENT_IP_BOOL:
            delete static_cast<ofEvent<pair<string,Item_Parameter<bool>>>*>(var_value); 
            break;
        case EVENT_IP_INT:
            delete static_cast<ofEvent<pair<string,Item_Parameter<int>>>*>(var_value);
            break;
        case EVENT_IP_FLOAT:
            delete static_cast<ofEvent<pair<string,Item_Parameter<float>>>*>(var_value); 
            break;
        case EVENT_IP_DOUBLE:
            delete static_cast<ofEvent<pair<string,Item_Parameter<double>>>*>(var_value); 
            break;
        case IP_INT:
            delete static_cast<Item_Parameter<int>*>(var_value); 
            break;
        case IP_FLOAT:
            delete static_cast<Item_Parameter<float>*>(var_value); 
            break;
        case IP_BOOL:
            delete static_cast<Item_Parameter<bool>*>(var_value); 
            break;
        case IP_VEC3F:
            delete static_cast<Item_Parameter<ofVec3f>*>(var_value); 
            break;
        case IP_COLOR:
            delete static_cast<Item_Parameter<ofColor>*>(var_value); 
            break;
        case CTRL_INT:
            delete static_cast<pair<vector<string>,pair<Item_Parameter<int>, ofEvent<pair<string,Item_Parameter<int>>>>>*>(var_value);
            break;
        case T_NULL:
            cout << "arg_t not defined for this type!!" << endl;
            break;
        default:
            cout << "arg_t not defined for this type!!" << endl;
            break;
    }
}

void Item::set_variable(string var_name, void* var_ptr, arg_t type_enum, Item* host_item_ptr){

    shared_variable_value raw_value;

    if (host_item_ptr == NULL)
        host_item_ptr = this;

    shared_variable_key key;
    key.host_item = host_item_ptr;
    key.name      = var_name;

    string var_key = string(var_name + ":" + to_string((long unsigned int)host_item_ptr));

    // Add an existent poiter as a new element.
    bool is_new_var = false;
    unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
    unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>::iterator shvar_map_it = shared_variables_map.find(key);

    if (var_ptr == NULL) {
        // Create a new element.
        is_new_var = true;
        var_ptr = create_var_ptr(type_enum);
    }

    if (map_it == var_ptr_map.end() and shvar_map_it == shared_variables_map.end()) {
        // Add element.
        var_ptr_map[var_key] = pair<void*,pair<arg_t,bool>>(var_ptr, pair<arg_t,bool>(type_enum,is_new_var));

        raw_value.value     = var_ptr;
        raw_value.type_enum = type_enum;
        raw_value.is_new    = is_new_var;
        shared_variables_map[key] = raw_value;

        //cout << "add new variable:" << key.name << endl;
    } else if(type_enum == T_NULL) {
        // Enumerator arg_t not defined for this type.
        stringstream error_msg;
        error_msg << "Enumerator arg_t not defined for this type." <<
                     "; variable name:" << var_name;
        //throw runtime_error(error_msg.str());
        cout << error_msg.str() << endl;
    } else {
        // Replace element.
        //cout << "overwiting var:" << var_key << " value:" << old_var->value << endl;

        bool* el_is_new_var;
        arg_t* el_type_enum;
        void** el_value;

        if(map_it != var_ptr_map.end()) {
            el_is_new_var = &(map_it->second.second.second);
            el_type_enum = &(map_it->second.second.first);
            el_value = &(map_it->second.first);
        } else {// if(shvar_map_it == shared_variables_map.end()) {
            el_is_new_var = &(shvar_map_it->second.is_new);
            el_type_enum = &(shvar_map_it->second.type_enum);
            el_value = &(shvar_map_it->second.value);
        }

        if (*el_is_new_var) {
            erase_var_ptr(*el_value, *el_type_enum);
        }

        if(*el_type_enum != type_enum) {
            // Element already exists with diferent arg_t.
            stringstream error_msg;
            error_msg << "Replacing variable of arg_t: " <<
                         *el_type_enum << " by other of arg_t: " << type_enum <<
                         "; variable name: " << var_name;
            //throw runtime_error(error_msg.str());
            cout << error_msg.str() << endl;
            *el_type_enum = type_enum;
        } 


        *el_value = var_ptr;
        *el_is_new_var = is_new_var;
    }

    //cout << "variable name:" << key.name << endl;
    //cout << "key.name: " << key.name << "; key.host_item->get_name():" << key.host_item->get_name() << endl;
    //cout << "shared_variables_map[key].type_enum: " << shared_variables_map[key].type_enum << "; shared_variables_map[key].is_new:" << shared_variables_map[key].is_new << endl;

}

pair<void*,arg_t> Item::get_variable(string var_name, Item* host_item_ptr){
    pair<void*,arg_t> result(NULL,T_NULL);

    shared_variable_value raw_value;

    if (host_item_ptr == NULL)
        host_item_ptr = this;
    
    shared_variable_key key;
    key.host_item = host_item_ptr;
    key.name      = var_name;
    
    string var_key = string(var_name + ":" + to_string((long unsigned int)host_item_ptr));

    unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
    unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>::iterator shvar_map_it = shared_variables_map.find(key);


    if(map_it == var_ptr_map.end()) {
        // Element doesn't exists.
        stringstream error_msg;
        error_msg << "get undefined variable: " << var_name;
        cout << error_msg.str() << endl;
        //throw runtime_error(error_msg.str());
    } else {
        bool* el_is_new_var;
        arg_t* el_type_enum;
        void** el_value;

        if(map_it != var_ptr_map.end()) {
            el_is_new_var = &(map_it->second.second.second);
            el_type_enum = &(map_it->second.second.first);
            el_value = &(map_it->second.first);
        } else {// if(shvar_map_it != shared_variables_map.end()) {
            el_is_new_var = &(shvar_map_it->second.is_new);
            el_type_enum = &(shvar_map_it->second.type_enum);
            el_value = &(shvar_map_it->second.value);
        }


        result = pair<void*,arg_t>(*el_value, *el_type_enum);
        //cout << result->value << endl;
    }
    return result;
}


void Item::erase_variable(string var_name, Item* host_item_ptr){
    string var_key;
    if (host_item_ptr == NULL)
        var_key=string(var_name + ":" + to_string((long unsigned int)this));
    else
        var_key=string(var_name + ":" + to_string((long unsigned int)host_item_ptr));

    unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
    if(map_it == var_ptr_map.end()) {
        // Element doesn't exists.
        stringstream error_msg;
        error_msg << "erase undefined variable " << var_name;
        cout << error_msg.str() << endl;
        //throw runtime_error(error_msg.str());
    } else {
        if (map_it->second.second.second){
            arg_t type_enum = map_it->second.second.first;
            if(type_enum == T_NULL) {
                // Enumerator arg_t not defined for this type.
                stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else { 
                switch (type_enum) {
                    case EVENT_IP_BOOL:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<bool>>>*>(map_it->second.first); 
                        break;
                    case EVENT_IP_INT:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<int>>>*>(map_it->second.first);
                        break;
                    case EVENT_IP_FLOAT:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<float>>>*>(map_it->second.first); 
                        break;
                    case EVENT_IP_DOUBLE:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<double>>>*>(map_it->second.first); 
                        break;
                    case IP_INT:
                        delete static_cast<Item_Parameter<int>*>(map_it->second.first); 
                        break;
                    case IP_FLOAT:
                        delete static_cast<Item_Parameter<float>*>(map_it->second.first); 
                        break;
                    case IP_BOOL:
                        delete static_cast<Item_Parameter<bool>*>(map_it->second.first); 
                        break;
                    case IP_VEC3F:
                        delete static_cast<Item_Parameter<ofVec3f>*>(map_it->second.first); 
                        break;
                    case IP_COLOR:
                        delete static_cast<Item_Parameter<ofColor>*>(map_it->second.first); 
                        break;
                    case CTRL_INT:
                        delete static_cast<pair<vector<string>,pair<Item_Parameter<int>, ofEvent<pair<string,Item_Parameter<int>>>>>*>(map_it->second.first);
                        break;
                    case T_NULL:
                        cout << "arg_t not defined for this type!!" << endl;
                        break;
                    default:
                        cout << "arg_t not defined for this type!!" << endl;
                        break;
                }
            }
        }

        var_ptr_map.erase(map_it);
    }
}

void Item::erase_item_parameter(string var_name, Item* host_item_ptr){
    erase_variable(var_name, host_item_ptr);
}

void Item::erase_event(string var_name, Item* host_item_ptr) {
    erase_variable(var_name, host_item_ptr);
}

void Item::erase_ctrl(string event_name, Item* host_item_ptr){
    erase_variable(event_name, host_item_ptr);
}

void Item::remove_listener(string event_name, Item* host_ctrl_ptr){
    //pair<void*,arg_t> raw_event = get_variable(event_name,host_ctrl_ptr);

    //ofRemoveListener(*event, this ,& Item::map_parameter);
}

void Item::map_parameter(string var_name, void* param, Item* host_item_ptr){
    //pair<void*,arg_t> current_var = get_variable(string var_name,host_item_ptr);
    //.... do something to the current_var ....
}
