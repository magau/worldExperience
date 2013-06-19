#include "testApp.h"

World :: World() {
    particles.name = "C_World";
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

void Manager_KeyboardInterface::start(World* _world){
    world = _world;
    isListening = false;
    obj.erase();
    msg.erase();
}

void Manager_KeyboardInterface::listen(int key){
   vector<Particle*> :: iterator IterPart;
   vector<Particles_Container*> :: iterator IterGroup;
   Particles_Container* temp_groupPtr;

   if(ofGetKeyPressed(13)) {
       //RETURN

       if(isListening && (create || action.compare("CREATE"))){

           if(obj.compare("PARTICLE") == 0){

cout<<"aqui"<<endl;
               switch(atoi(temp_msg.c_str())) {
                   case 1:
                       temp_msg = "P_Base";
                       break;
                   case 2:
                       temp_msg = "P_Circle";
                       break;
                   case 3:
                       temp_msg = "MP_RegGrid";
                       break;
               }

           } else if(obj.compare("INTERACTION") == 0){

               switch(atoi(temp_msg.c_str())) {
                   case 1:
                       temp_msg = "I_ElectRepulsion";
                       break;
                   case 2:
                       temp_msg = "I_ElectAttraction";
                       break;
                   case 3:
                       temp_msg = "I_WaveSource";
                       break;
               }

           } else if(obj.compare("BEHAVIOR") == 0){

               switch(atoi(temp_msg.c_str())) {
                   case 1:
                       temp_msg = "B_GravityGlue";
                       break;
                   case 2:
                       temp_msg = "B_MouseTracking";
                       break;
               }

           }
       }

       msg += "/" + temp_msg;
       isListening = false;
       cout<<"END"<<endl;
       cout<<"temp_msg:"<<temp_msg<<endl;

       if (create || action.compare("CREATE") == 0){
           if (particle || obj.compare("PARTICLE") == 0) {

               buffer_particle = world->create_particle(temp_msg);

               if (buffer_group != int(NULL)){
                   buffer_group->add(buffer_particle, false);
               }

               //provisorio...
               *(buffer_particle->ofColorPtr_map["color"]) = ofColor(255,0,0);
               *(buffer_particle->ofVec3fPtr_map["loc"]) = ofVec3f(ofGetMouseX(),ofGetMouseY());
               *(buffer_particle->intPtr_map["rad"]) = 10;

           } else if (group || obj.compare("GROUP") == 0){

               buffer_group = world->create_group(temp_msg);

           }

       } else if (get || action.compare("GET") == 0){

           if (particle || obj.compare("PARTICLE") == 0) {

               buffer_particle = world->particles.get_itemById(atoi(temp_msg.c_str()));

           } else if (group || obj.compare("GROUP") == 0){

               buffer_group = world->groups.get_itemById(atoi(temp_msg.c_str()));

           }
          
       }

       if (!get && action.compare("GET") != 0) {

           buffer_group = int(NULL);
           buffer_particle = int(NULL);
           buffer_interaction = int(NULL);
           buffer_behavior = int(NULL);
       }

       obj.erase();
       msg.erase();

   } else if(ofGetKeyPressed(9)) {
       //CTRL + I
       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT":"EXIT INSERT")<<endl;
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
       create = true;
       remove = false;
       get    = false;
       set    = false;
       add    = false;
       action = "CREATE";
       cout<<action<<endl;

   } else if(ofGetKeyPressed(18)){
       //CTRL + R
       create = false;
       remove = true;
       get    = false;
       set    = false;
       add    = false;
       action = "REMOVE";
       cout<<action<<endl;


   } else if(ofGetKeyPressed(7)){
       //CTRL + G
       create = false;
       remove = false;
       get    = true;
       set    = false;
       add    = false;
       action = "GET";
       cout<<action<<endl;


   } else if(ofGetKeyPressed(19)){
       //CTRL + S
       create = false;
       remove = false;
       get    = false;
       set    = true;
       add    = false;
       action = "SET";
       cout<<action<<endl;


   } else if(ofGetKeyPressed(1)){
       //CTRL + A
       create = false;
       remove = false;
       get    = false;
       set    = false;
       add    = true;
       action = "ADD";
       cout<<action<<endl;


   } else if(ofGetKeyPressed(112)){
       // P
       particle    = true;
       group       = false;
       behavior    = false;
       interaction = false;
       obj = "PARTICLE";
       msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

       if (buffer_group == int(NULL)){
           temp_groupPtr = &(world->particles);
       } else {
           temp_groupPtr = buffer_group;
       }

       if(action.compare("CREATE") || create){

           cout<<"1 - P_Base"<<endl;
           cout<<"2 - P_Circle"<<endl;
           cout<<"3 - MP_RegGrid"<<endl;

       } else if(action.compare("GET") || get) {

           cout<<"group:"<<(temp_groupPtr->name)<<" size:"<<(temp_groupPtr->itemsVector.size())<<endl;
           for(IterPart = temp_groupPtr->itemsVector.begin();
                IterPart != temp_groupPtr->itemsVector.end();
                IterPart++){
               cout<<"name:"<<(*IterPart)->name<<" id:"<<(*IterPart)->id<<endl;
           }
       }

       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT":"EXIT INSERT")<<endl;

   } else if(ofGetKeyPressed(103)){
       // G
       particle    = false;
       group       = true;
       behavior    = false;
       interaction = false;
       obj = "GROUP";
       msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;
       if(action.compare("GET") || get) {
           for(IterGroup = world->groups.itemsVector.begin();
               IterGroup != world->groups.itemsVector.end();
               IterGroup++){
               cout<<"name:"<<(*IterGroup)->name<<" id:"<<(*IterGroup)->id<<endl;
           }
       }

       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT":"EXIT INSERT")<<endl;

   } else if(ofGetKeyPressed(98)){
       // B
       particle    = false;
       group       = false;
       behavior    = true;
       interaction = false;
       obj = "BEHAVIOR";
       msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

       if(action.compare("CREATE") || create){

           cout<<"1 - B_GravityGlue"<<endl;
           cout<<"2 - B_MouseTracking"<<endl;

       }

       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT":"EXIT INSERT")<<endl;

   } else if(ofGetKeyPressed(105)){
       // I
       particle    = false;
       group       = false;
       behavior    = false;
       interaction = true;
       obj = "INTERACTION";
       msg = action + "/" + obj;
       cout<<obj<<endl;
       cout<<msg<<endl;

       if(action.compare("CREATE") || create){

           cout<<"1 - I_ElectRepulsion"<<endl;
           cout<<"2 - I_ElectAttraction"<<endl;
           cout<<"3 - I_WaveSource"<<endl;

       }

       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT":"EXIT INSERT")<<endl;
   }


}

