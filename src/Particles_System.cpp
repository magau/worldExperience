#include "testApp.h"

Particles_System::Particles_System(Particle_props init_props) :
                 Particle(init_props){
    name = "basePS";
    default_Particle = "baseP";
    default_Interaction = "baseI";
}

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

void Particles_System::create_systemParticles(){
    //create System systemParticles Particles_Container.
    systemParticles = new Particles_Container;
    systemParticles->name = "Generic";
    world->groups.add(systemParticles); 
}

void Particles_System::create_particle(Particle_props init_props){
    //create newParticle add particle to worldParticles and 
    //systemParticles Particles_Container
    Particle* newParticle;
    newParticle = new Particle(init_props);
    world->particles.add(newParticle);
    systemParticles->add(newParticle,false);
}

/*
Derived_ParticlesSystem::Derived_ParticlesSystem() :
                         Pointers_Container<Particle*>(init_props){
    name = "derivedPS";
    default_addedItemName = "baseP";
}
*/

RegularGrid_PS::RegularGrid_PS(Particle_props init_props) :
                             Particles_System(init_props){
    name = "PS_RegGrid";
    default_Particle = "P_Circle";
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
    create_systemParticles();

    for (i=0; i<grid_num.y; i++){
        //init_props.loc.y = i*grid_ds + grid_offset.y;
        init_props.locat.y = i*grid_ds + grid_offset.y;
        for (j=0; j<grid_num.x; j++){
            init_props.locat.x = j * grid_ds + grid_offset.x;
            create_particle(init_props);
        }
    }
}

//void ParticlesSystems_Container::add_itemByName(string iName,Particle_props init_props){
//   if (iName.size() == 0){
//       iName = default_addedItemName;
//   } 
//
//   if (iName.compare("") == 0){
//       add(new Particles_System(init_props));
//   } else if (iName.compare("PS_RegGrid") == 0){
//       add(new RegularGrid_PS(init_props));
//   }
//   /*
//    .
//    .
//    .
//       Add new item types
//   */
//}


