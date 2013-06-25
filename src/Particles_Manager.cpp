#include "testApp.h"

World :: World() {
    particles.name = "C_World";
    particles.id = -1;
    groups.add(&particles,false);
}

Particles_Container* World::create_group(string iName){
    //create System systemParticles Particles_Container.
    Particles_Container* newGroup;
    newGroup = new Particles_Container;
    newGroup->name = iName;
    groups.add(newGroup);
    return newGroup;
}

Particle* World::create_particle(string iName){
    //create newParticle add particle to worldParticles and 
    //systemParticles Particles_Container
    Particle* newParticle;
    newParticle = particles.add_itemByName(iName, this);
    return newParticle;
}

Particles_Container* World :: update(){
    Particle* temp_particle_ptr;
    for(vector<Particle*>::iterator IterPart = particles.itemsVector.begin();
                                    IterPart != particles.itemsVector.end();
                                    IterPart++){
        temp_particle_ptr = *IterPart;
        temp_particle_ptr->run();
        if(!temp_particle_ptr->isAlive){
            remove_particle(temp_particle_ptr);
        }
    }
    return &(particles);
}

void World :: remove_particle(Particle* particle_ptr){
   
    particles.pop_itemById(particle_ptr->id);

}

void World::draw(){
    for(vector<Particle*>::iterator IterPart = particles.itemsVector.begin();
                                    IterPart != particles.itemsVector.end();
                                    IterPart++){
        (*IterPart)->display();
    }
}

Manager_KeyboardInterface::Manager_KeyboardInterface(){
    particle_name["1"] = "P_Base";
    particle_name["2"] = "P_Circle";
    particle_name["3"] = "MP_RegGrid";

    interaction_name["1"] = "I_ElectRepulsion";
    interaction_name["2"] = "I_ElectAttraction";
    interaction_name["3"] = "I_WaveSource";
 
    behavior_name["1"] = "B_GravityGlue";
    behavior_name["2"] = "B_MouseTracking";

    buffer_particle    = (int)NULL;
    buffer_interaction = (int)NULL;
    buffer_behavior    = (int)NULL;
    buffer_group       = (int)NULL;

    isListening = false;
    msg.erase();
    reset_objects();
    reset_actions(); 
} 

void Manager_KeyboardInterface::get_availableItems_names(unordered_map<string,string> names_map){
    unordered_map<string,string>::const_iterator item_name;
    
    for(item_name = names_map.begin();
         item_name != names_map.end();
         item_name++){
        cout<<item_name->first<<" - "<<item_name->second<<endl;
    }
}

void Manager_KeyboardInterface::reset_objects(){

    particle    = false;
    group       = false;
    behavior    = false;
    interaction = false;
}

void Manager_KeyboardInterface::reset_actions(){

    create = false;
    remove = false;
    get    = false;
    set    = false;
    add    = false;
}

void Manager_KeyboardInterface::start(World* _world){
    //Can't add 'world' inside constructor because
    //this class is instantiated at the testApp.h file.
    world = _world;
    //buffer_group = &(world->particles);
}

void Manager_KeyboardInterface::decode_kb_msg(string encoded_msg){

    if (create){

        if(particle){
            
            obj_name = particle_name[encoded_msg];

        } else if(interaction){

            obj_name = interaction_name[encoded_msg];

        } else if(behavior){

            obj_name = behavior_name[encoded_msg];

        } else if(group){

            obj_name = encoded_msg;

        }

        msg += "/" + obj_name;

    } else {

        obj_id = atoi(encoded_msg.c_str());

        msg += "/" + encoded_msg;

    }

    isListening = false;
    cout<<"END"<<endl;
    cout<<"msg:"<<msg<<endl;
}

void Manager_KeyboardInterface::stateFabric_update(string _msg){
    // This method decodes OSC like messages with purpose of
    // update state variables.
    int pos;
    string _action, _obj, _id;

    pos = _msg.find("/");
    _action = _msg.substr(0,pos);
    _msg.replace(0,pos+1,"");
    pos = _msg.find("/");
    _obj = _msg.substr(0,pos);
    _msg.replace(0,pos+1,"");
    _id = _msg;

    reset_actions();
    reset_objects();

    if (_action.compare("CREATE") == 0){
        create = true;
    } else if (_action.compare("REMOVE") == 0) {
        remove = true;
    } else if (_action.compare("GET") == 0) {
        get    = true;
    } else if (_action.compare("SET") == 0) {
        set    = true;
    } else if (_action.compare("ADD") == 0) {
        add    = true;
    }

    if (_obj.compare("PARTICLE") == 0){
        particle    = true;
    } else if (_obj.compare("GROUP") == 0) {
        group       = true;
    } else if (_obj.compare("BEHAVIOR") == 0) {
        behavior    = true;
    } else if (_obj.compare("INTERACTION") == 0) {
        interaction = true;
    }

    
    cout<<"action:"<<_action<<" obj:"<<_obj<<" id:"<<_id<<endl;
}

void Manager_KeyboardInterface::stateFabric_decode(){
   vector<Particle*>::iterator iterPart;

   if (create){

       if (particle) {

           buffer_particle = world->create_particle(obj_name);

           if (buffer_group != int(NULL) && buffer_group != &(world->particles)){

               buffer_group->add(buffer_particle, false);
 
           }

           //provisorio...
           *(buffer_particle->ofColorPtr_map["color"]) = ofColor(255,0,0);
           *(buffer_particle->ofVec3fPtr_map["loc"]) = ofVec3f(ofGetMouseX(),ofGetMouseY());
           *(buffer_particle->intPtr_map["rad"]) = 10;

           buffer_group = (int)NULL;

       } else if (group){

           buffer_group = world->create_group(obj_name);

           buffer_particle = (int)NULL;
           
       } else if (behavior){

           if (buffer_particle != (int)NULL) {

               cout<<"create buffer_behavior..."<<endl;
               buffer_behavior = buffer_particle->behaviors.add_itemByName(obj_name,buffer_particle);
               buffer_interaction = (int)NULL;

           } else if (buffer_group != (int)NULL) {

               cout<<"create buffer_behaviors..."<<endl;
               buffer_behaviors.clear();

               for(iterPart = buffer_group->itemsVector.begin();
                    iterPart != buffer_group->itemsVector.end();
                    iterPart++){
                   cout<<"iter name:"<<(*iterPart)->name<<" iter id:"<<(*iterPart)->id<<endl;
                   buffer_behaviors.add((*iterPart)->behaviors.add_itemByName(obj_name,*iterPart),false);
               }

               cout<<"end create buffer_behaviors."<<endl;
               buffer_interactions.clear();

           }

       } else if (interaction){

           if (buffer_particle != (int)NULL) {

               buffer_interaction = buffer_particle->interactions.add_itemByName(obj_name,buffer_particle);
               buffer_behavior = (int)NULL;

           } else if (buffer_group != (int)NULL) {

               buffer_interactions.clear();

               for(iterPart = buffer_group->itemsVector.begin();
                    iterPart != buffer_group->itemsVector.end();
                    iterPart++){
                   buffer_interactions.add((*iterPart)->interactions.add_itemByName(obj_name,*iterPart),false);
               }

               buffer_behaviors.clear();

           }

       }

   } else if (add){

       if (particle) {

           if (buffer_group != (int)NULL && buffer_particle != (int)NULL) {

               buffer_group->add(buffer_particle,false);

           }

       } else if (group) {
           
           if (buffer_interaction != (int)NULL) {
               
               buffer_interaction->actuated_particles = world->groups.get_itemById(obj_id);

           }

       }

   } else if (get){

       if (particle) {

           if (buffer_group != (int)NULL){

               buffer_particle = buffer_group->get_itemById(obj_id);
               buffer_group = (int)NULL;

           } else {

               cout<<"ERROR - group not in buffer";

           }

       } else if (group){

           buffer_group = world->groups.get_itemById(obj_id);
           buffer_particle = (int)NULL;

       } else if (interaction){

           buffer_interaction = buffer_particle->interactions.get_itemById(obj_id);
           buffer_behavior = (int)NULL;

       } else if (behavior){

           buffer_behavior = buffer_particle->behaviors.get_itemById(obj_id);
           buffer_interaction = (int)NULL;

       }

   } else if (remove){

       if (particle){

           cout<<"group id:"<<buffer_group->id<<endl;

           if (buffer_group == &(world->particles)){

               world->remove_particle(buffer_particle);

           } else {

               buffer_group->pop_itemById(buffer_particle->id,false);

           }

       } else if (interaction) {

           if (buffer_particle == (int)NULL){

              cout<<"ERROR - particle not in buffer";

           } else {

              cout<<"particle id:"<<buffer_particle->id<<endl;
              buffer_particle->interactions.pop_itemById(buffer_interaction->id);

           }

       } else if (behavior) {

           if (buffer_particle == (int)NULL){

              cout<<"ERROR - particle not in buffer";

           } else {

              cout<<"particle id:"<<buffer_particle->id<<endl;
              buffer_particle->behaviors.pop_itemById(buffer_behavior->id);

           }

       }

   }

/*
   if (!get) {

       //buffer_group = int(NULL);
       buffer_group = &(world->particles);
       buffer_particle = int(NULL);
       buffer_interaction = int(NULL);
       buffer_behavior = int(NULL);
   }
*/

    msg.erase();

}

void Manager_KeyboardInterface::listen(int key){
   vector<Particle*> :: iterator IterPart;
   vector<Particles_Container*> :: iterator IterGroup;

   if(ofGetKeyPressed(13)) {
       //RETURN

       if(isListening){
           decode_kb_msg(temp_msg);
       } 

       //stateFabric_update(msg);

       stateFabric_decode();

   } else if(ofGetKeyPressed(9)) {
       //CTRL + I

       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT MODE:":"EXIT INSERT")<<endl;

   } else if(ofGetKeyPressed(5)) {
       //CTRL + E

       msg += "/" + temp_msg;
       isListening = false;
       cout<<"END"<<endl;
       cout<<"temp_msg:"<<temp_msg<<endl;

   } else if(isListening){

       if( key != 8 ){
           temp_msg += key;
       } else if (!temp_msg.empty()){
           temp_msg.erase(temp_msg.end() - 1);
       }
       //cout<<key<<endl;
       cout<<temp_msg<<endl;

   } else if(ofGetKeyPressed(3)){
       //CTRL + C

       reset_actions();
       create = true;
       msg = "CREATE";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(18)){
       //CTRL + R

       reset_actions();
       remove = true;
       msg ="REMOVE";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(7)){
       //CTRL + G

       reset_actions();
       get    = true;
       msg ="GET";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(19)){
       //CTRL + S
 
       reset_actions();
       set    = true;
       msg ="SET";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(1)){
       //CTRL + A

       reset_actions();
       add    = true;
       msg ="ADD";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(112)){
       // P

       reset_objects();
       particle    = true;
       msg += "/PARTICLE";

       if(create){

           get_availableItems_names(particle_name);

       } else if(get) {

           cout<<"group:"<<(buffer_group->name)<<" size:"<<(buffer_group->itemsVector.size())<<endl;
           buffer_group->show_items_name_and_id();

       }

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(103)){
       // G

       reset_objects();
       group       = true;
       msg += "/GROUP";

       if(get) {

           world->groups.show_items_name_and_id();

       } else if(add) {

           world->groups.show_items_name_and_id();

       }


       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(98)){
       // B

       reset_objects();
       behavior    = true;
       msg += "/BEHAVIOR";

       if(create){

           get_availableItems_names(behavior_name);

       } else if(get | remove) {

           if (buffer_particle == (int)NULL){
               cout<<"ERROR - particle not in buffer";
           } else {
               buffer_particle->behaviors.show_items_name_and_id();
           }
       }



       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(105)){
       // I

       reset_objects();
       interaction = true;
       msg += "/INTERACTION";

       if(create){

           get_availableItems_names(interaction_name);

       } else if(get | remove) {

           if (buffer_particle == (int)NULL){
               cout<<"ERROR - particle not in buffer";
           } else {
               buffer_particle->interactions.show_items_name_and_id();
           }
       }


       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;
   }

}

