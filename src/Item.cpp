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

void Item::set_variable(string var_name, void* var_ptr, arg_t arg_num, Item* item_ptr){

    string var_key;
    if (item_ptr == NULL)
        var_key=string(var_name + ":" + to_string((long unsigned int)this));
    else
        var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));

    // Add an existent poiter as a new element.
    bool is_new_var = false;
    unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);

    if (var_ptr == NULL) {
        // Create a new element.
        is_new_var = true;
        switch (arg_num) {
            case EAT_BOOL:
                var_ptr = new ofEvent<pair<string,Item_Parameter<bool>>>;
                break;
            case EAT_INT:
                var_ptr = new ofEvent<pair<string,Item_Parameter<int>>>;
                break;
            case EAT_FLOAT:
                var_ptr = new ofEvent<pair<string,Item_Parameter<float>>>;
                break;
            case EAT_DOUBLE:
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
                cout << "Can't create new variable: " << var_name << " ; arg_t not defined for this type!!" << endl;
                break;
            default:
                cout << "Can't create new variable: " << var_name << " ; arg_t not defined for this type!!" << endl;
                break;
        }
    }

    if (map_it == var_ptr_map.end()) {
        // Add element.
        var_ptr_map[var_key] = pair<void*,pair<arg_t,bool>>(var_ptr, pair<arg_t,bool>(arg_num,is_new_var));

    } else if(arg_num == T_NULL) {
        // Enumerator arg_t not defined for this type.
        stringstream error_msg;
        error_msg << "Enumerator arg_t not defined for this type." <<
                     "; variable name:" << var_name;
        //throw runtime_error(error_msg.str());
        cout << error_msg.str() << endl;
    } else {
        // Replace element.
        //cout << "overwiting var:" << var_key << " value:" << old_var->value << endl;
        if (map_it->second.second.second) {
            switch (map_it->second.second.first) {
                case EAT_BOOL:
                    delete static_cast<ofEvent<pair<string,Item_Parameter<bool>>>*>(map_it->second.first); 
                    break;
                case EAT_INT:
                    delete static_cast<ofEvent<pair<string,Item_Parameter<int>>>*>(map_it->second.first);
                    break;
                case EAT_FLOAT:
                    delete static_cast<ofEvent<pair<string,Item_Parameter<float>>>*>(map_it->second.first); 
                    break;
                case EAT_DOUBLE:
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

        if(map_it->second.second.first != arg_num) {
            // Element already exists with diferent arg_t.
            stringstream error_msg;
            error_msg << "Replacing variable of arg_t: " <<
                         map_it->second.second.first << " by other of arg_t: " << arg_num <<
                         "; variable name: " << var_name;
            //throw runtime_error(error_msg.str());
            cout << error_msg.str() << endl;
            map_it->second.second.first = arg_num;
        } 


        map_it->second.first = var_ptr;
        map_it->second.second.second = is_new_var;
    }
}

void Item::erase_variable(string var_name, Item* item_ptr){
    string var_key;
    if (item_ptr == NULL)
        var_key=string(var_name + ":" + to_string((long unsigned int)this));
    else
        var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));

    unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
    if(map_it == var_ptr_map.end()) {
        // Element doesn't exists.
        stringstream error_msg;
        error_msg << "erase undefined variable " << var_name;
        cout << error_msg.str() << endl;
        //throw runtime_error(error_msg.str());
    } else {
        if (map_it->second.second.second){
            arg_t arg_num = map_it->second.second.first;
            if(arg_num == T_NULL) {
                // Enumerator arg_t not defined for this type.
                stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else { 
                switch (arg_num) {
                    case EAT_BOOL:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<bool>>>*>(map_it->second.first); 
                        break;
                    case EAT_INT:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<int>>>*>(map_it->second.first);
                        break;
                    case EAT_FLOAT:
                        delete static_cast<ofEvent<pair<string,Item_Parameter<float>>>*>(map_it->second.first); 
                        break;
                    case EAT_DOUBLE:
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

void Item::erase_item_parameter(string var_name, Item* item_ptr){
    erase_variable(var_name, item_ptr);
}

void Item::erase_event(string var_name, Item* item_ptr) {
    erase_variable(var_name, item_ptr);
}

void Item::erase_ctrl(string event_name, Item* item_ptr){
    erase_variable(event_name, item_ptr);
}

