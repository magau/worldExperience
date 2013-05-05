#include "testApp.h"


Particle :: Particle (Particle_props init_props){
    props = init_props;
}

void Particle :: run() {
    update();
    display();
}

// Method to display
void Particle :: display() {
    //ofColor(...);
    //ofFill();
    //ofSetColor(props.color);
    //ofEllipse(props.locat.x,props.locat.y,props.rad,props.rad);
}

void Particle :: update() {
    props.veloc += props.accel;
//    enable_screenElasticBoundery();
    props.locat += props.veloc;
    //Aplly relax_fact
    props.veloc *= ofVec3f(props.relax_fact);
//    bound_particles_location();
    //props.vel = ofPoint(0);
    props.accel = ofVec3f(0);
    props.relax_fact = 1.0;
//cout<<"props.vel:"<<props.vel<<" props.loc:"<<props.loc<<endl;
    // Clear accelaration to allow comulative 
    // interactions and order independency:
}

/*
void Particle :: bound_particles_location(){
   int offset = props.rad;

   if (props.locat.x < offset){
       props.locat.x = offset;
   } else if (props.locat.x > ofGetWindowWidth()-offset){
       props.locat.x = ofGetWindowWidth()-offset;
   }
   if (props.locat.y < offset){
       props.locat.y = offset;
   } else if (props.locat.y > ofGetWindowHeight()-offset){
       props.locat.y = ofGetWindowHeight()-offset;
   }

}

void Particle :: set_speedLimit(int maxSpeed){
   
   if (props.veloc.x < -1 * maxSpeed){
       props.veloc.x = -1 * maxSpeed;
   } else if (props.veloc.x > maxSpeed){
       props.veloc.x = maxSpeed;
   }
   if (props.veloc.y < -1 * maxSpeed){
       props.veloc.y = -1 * maxSpeed;
   } else if (props.veloc.y > maxSpeed){
       props.veloc.y = maxSpeed;
   }
}

void Particle :: enable_screenElasticBoundery(){
   int offset = props.rad;

   //Elastic bounds
   if ( props.locat.x <= offset || props.locat.x >= ofGetWindowWidth()-offset ){
       props.veloc.x *= -1;
   }
   if ( props.locat.y <= offset || props.locat.y >= ofGetWindowHeight()-offset ){
       props.veloc.y *= -1;
   }
}
*/

Circle::Circle(Particle_props init_props) :
                     Particle(init_props){
    itemType="P_Circle";
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(props.color);
    ofEllipse(props.locat.x,props.locat.y,props.rad,props.rad);
}
/*
InteractiveParticle::InteractiveParticle(Particle_props init_props) :
                     Particle(init_props){
    itemType="IP_1";
}

void InteractiveParticle::run(){
// for interaction in itemsVector
// interaction.run()
}

DerivedParticle::DerivedParticle(Particle_props init_props) :
                 Pointers_Container<Particle*>(init_props){
    itemType="derivedP";
}
*/


