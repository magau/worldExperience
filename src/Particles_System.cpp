#include "testApp.h"

Master_Particle::Master_Particle() : Particle(){
    default_Particle = "Particle";
    set_world((World*)NULL);
}

void Master_Particle::setup(){}

void Master_Particle::run(){}

Particle* Master_Particle::create_slaveParticle(){
    //create newParticle add particle to worldParticles 
    Particle* newParticle = get_world()->create_particle(default_Particle);
    //slaveParticles->add(newParticle,false);
    return newParticle;
}

RegularGrid_MP::RegularGrid_MP() : Master_Particle(){
    default_Particle = "Circle";
    //particles_distance = 15;
    particles_distance = 30;
    windowRatio = 4.0/5;
}

void RegularGrid_MP::setup(){
    //This method ("constructor") builds a 2D regular grid particles system.
    // particles_distance - pixels
    // grid_size - [0 < grid_size <1] Relative to window size.
    u_int i,j,win_w,win_h,grd_w,grd_h;
    ofPoint grid_offset;
    ofVec3f temp_locat;
    int grid_ds;
    ofPoint grid_num;
    Particle* slave_particle;

    grid_ds = particles_distance;
    win_w = ofGetWindowWidth();
    win_h = ofGetWindowHeight();
    grd_w = round(win_w*windowRatio);
    grd_h = round(win_h*windowRatio);

    grid_offset.x = (win_w - grd_w)/2;
    grid_offset.y = (win_h - grd_h)/2;
    grid_num.set(grd_w/grid_ds , grd_h/grid_ds);
    //grid_num.set(2 , 2);


    for (i=0; i<grid_num.y; i++){

        temp_locat.y = i*grid_ds + grid_offset.y;

        for (j=0; j<grid_num.x; j++){

            temp_locat.x = j * grid_ds + grid_offset.x;

            slave_particle = create_slaveParticle();

            //cout << "slave particle:" << slave_particle->get_type_name() << endl;
            slave_particle->set<ofVec3f>("loc", temp_locat);
            slave_particle->set<float>("relax", 1.0);
            slave_particle->set<ofColor>("color", ofColor(255));
            slave_particle->set<int>("rad", 9, pair<int,int>(0,500));
        }
    }
}
