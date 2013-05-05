#include "testApp.h"

Particles_System::Particles_System(Particle_props init_props) :
                 Particle(init_props){
    itemType = "basePS";
    default_Particle = "baseP";
    default_Interaction = "baseI";
}

//void Particles_System::add_itemByName(string iName,Particle_props init_props){
//   if (iName.size() == 0){
//       iName = default_addedItemName;
//   } 
//
//   if (iName.compare("baseP") == 0){
//       add(new Particle(init_props));
//   } else if (iName.compare("IP_1") == 0){
//       add(new InteractiveParticle(init_props));
//   }
//   /*
//    .
//    .
//    .
//       Add new item types
//   */
//}

void Particles_System::setup(){
//    for (int i=0;i<10;i++){
//        if (i<5){
//            add(new Particle());
//        } else {
//            add(new DerivedParticle());
//        }
//    }
}

//void Base_ParticlesSystem::interact(Base_ParticlesSystem* actuated_PS){
////    for (u_int i=0; i<itemsVector.size(); i++){
////        itemsVector[i].interact( &(actuated_PS->itemsVector) );
////    }
//}
//
void Particles_System::run(){

}

/*
Derived_ParticlesSystem::Derived_ParticlesSystem() :
                         Pointers_Container<Particle*>(init_props){
    itemType = "derivedPS";
    default_addedItemName = "baseP";
}
*/

RegularGrid_PS::RegularGrid_PS(Particle_props init_props) :
                             Particles_System(init_props){
    itemType = "regGidPS";
    default_Particle = "baseP";
}

void RegularGrid_PS::setup(int particles_distance, ofPoint grid_size){
    //This method ("constructor") builds a 2D regular grid particles system.
    // particles_distance - pixels
    // grid_size - [0 < grid_size <1] Relative to window size.
    u_int i,j,win_w,win_h,grd_w,grd_h;
    Particle_props init_props;
    ofPoint grid_offset;
    int grid_ds;
    ofPoint grid_num;

    init_props.veloc.set(0,0);
    init_props.accel.set(0,0);
    init_props.rad = 6;
    init_props.relax_fact = 1.0;
    init_props.color = ofColor(255);

    grid_ds = particles_distance;
    win_w = ofGetWindowWidth();
    win_h = ofGetWindowHeight();
    grd_w = round(win_w*grid_size.x);
    grd_h = round(win_h*grid_size.y);
    //grid_offset.x = (win_w - (grd_w-2*grid_ds)/grid_ds * grid_ds)/2;
    //grid_offset.y = (win_h - (grd_h-2*grid_ds)/grid_ds * grid_ds)/2;
    //grid_num.set(1+(win_w-2*grid_offset.x)/grid_ds,1+(win_h-2*grid_offset.y)/grid_ds);

    grid_offset.x = (win_w - grd_w)/2;
    grid_offset.y = (win_h - grd_h)/2;
    grid_num.set(grd_w/grid_ds , grd_h/grid_ds);

////One particle for testing
//grid_num.set(1);
//init_props.loc.x = win_w/2;//
//init_props.loc.y = win_h/2;//
    for (i=0; i<grid_num.y; i++){
        //init_props.loc.y = i*grid_ds + grid_offset.y;
        init_props.locat.y = i*grid_ds + grid_offset.y;
        for (j=0; j<grid_num.x; j++){
            //init_props.loc.x = j * grid_ds + grid_offset.x;
            init_props.locat.x = j * grid_ds + grid_offset.x;
            manager->worldParticles.add(new Particle(init_props));
        }
    }
}


