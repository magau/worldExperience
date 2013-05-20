#include "testApp.h"

Master_Particle::Master_Particle(Particle_props init_props) :
                 Particle(init_props){
    name = "basePS";
    default_Particle = "P_Circle";
    //default_Particle = "baseP";
    default_Interaction = "baseI";
}

void Master_Particle::setup(){
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

void Master_Particle::run(){

}

void Master_Particle::create_slaveContainer(){
    //create System slaveParticles Particles_Container.
    slaveParticles = new Particles_Container;
    slaveParticles->name = "Generic";
    props.world->groups.add(slaveParticles); 
}

void Master_Particle::create_slaveParticle(Particle_props init_props){
    //create newParticle add particle to worldParticles and 
    //slaveParticles Particles_Container
    Particle* newParticle;
    newParticle = props.world->particles.add_itemByName(default_Particle,init_props);
    slaveParticles->add(newParticle,false);
}

/*
Derived_ParticlesSystem::Derived_ParticlesSystem() :
                         Pointers_Container<Particle*>(init_props){
    name = "derivedPS";
    default_addedItemName = "baseP";
}
*/

RegularGrid_MP::RegularGrid_MP(Particle_props init_props) :
                             Master_Particle(init_props){
    name = "MP_RegGrid";
    default_Particle = "P_Circle";
    // provisorio:
    setup(15,4.0/5); 
}

void RegularGrid_MP::setup(int particles_distance, float windowRatio){
    //This method ("constructor") builds a 2D regular grid particles system.
    // particles_distance - pixels
    // grid_size - [0 < grid_size <1] Relative to window size.
    u_int i,j,win_w,win_h,grd_w,grd_h;
    Particle_props init_props;
    ofPoint grid_offset;
    int grid_ds;
    ofPoint grid_num;

    init_props.veloc.set(0);
    init_props.accel.set(0);
    init_props.rad = 6;
    init_props.relax_fact = 1.0;
    init_props.color = ofColor(255);
    init_props.world = props.world;

    grid_ds = particles_distance;
    win_w = ofGetWindowWidth();
    win_h = ofGetWindowHeight();
    grd_w = round(win_w*windowRatio);
    grd_h = round(win_h*windowRatio);
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
//cout<<"create_slaveContainer - start."<<endl;
    create_slaveContainer();
//cout<<"create_slaveContainer - done."<<endl;
    
    for (i=0; i<grid_num.y; i++){
        //init_props.loc.y = i*grid_ds + grid_offset.y;
        init_props.locat.y = i*grid_ds + grid_offset.y;
        for (j=0; j<grid_num.x; j++){
            init_props.locat.x = j * grid_ds + grid_offset.x;
//cout<<"create_slaveParticle - start."<<endl;
            create_slaveParticle(init_props);

//cout<<"init_props.locat:"<<init_props.locat.x<<";"<<init_props.locat.y<<endl;
//cout<<"create_slaveParticle - done."<<endl;
        }
    }
}

//void ParticlesSystems_Container::add_itemByName(string iName,Particle_props init_props){
//   if (iName.size() == 0){
//       iName = default_addedItemName;
//   } 
//
//   if (iName.compare("") == 0){
//       add(new Master_Particle(init_props));
//   } else if (iName.compare("PS_RegGrid") == 0){
//       add(new RegularGrid_MP(init_props));
//   }
//   /*
//    .
//    .
//    .
//       Add new item types
//   */
//}


