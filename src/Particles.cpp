#include "testApp.h"

Particle :: Particle () : Item(){

    set_name(get_type_name());
    //cout << get_type_name() << " constructor..." << endl;
    loc = Item_Parameter<ofVec3f>(ofVec3f(0), pair<ofVec3f,ofVec3f> (ofVec3f(0),ofVec3f(0)));
    vel = Item_Parameter<ofVec3f>(ofVec3f(0), pair<ofVec3f,ofVec3f> (ofVec3f(0),ofVec3f(0)));
    acc = Item_Parameter<ofVec3f>(ofVec3f(0), pair<ofVec3f,ofVec3f> (ofVec3f(0),ofVec3f(0)));
    color = Item_Parameter<ofColor>(ofColor(0), pair<ofColor,ofColor> (ofColor(0),ofColor(0)));
    rad = Item_Parameter<int>(13, pair<int,int>(0,100));
    relax = Item_Parameter<float>(0);
    visible = Item_Parameter<bool>(true);
    set_variable("loc",&loc,IP_VEC3F);
    set_variable("vel",&vel,IP_VEC3F);
    set_variable("acc",&acc,IP_VEC3F);
    set_variable("color",&color,IP_COLOR);
    set_variable("rad",&rad,IP_INT);
    set_variable("relax",&relax,IP_FLOAT);
    set_variable("is_visible",&visible,IP_BOOL);
}

Particle :: ~Particle (){
    PointersVector<Tag*>::iterator iter_tag;
    for (iter_tag = tags.begin();
         iter_tag != tags.end();
         iter_tag++){
        (*iter_tag)->remove_particle(this);
    }
}

//bool Particle::is_visible() {
//    return visible.value;    
//};

//void Particle::set_visible(bool visible_val){
//    visible.value = visible_val;
//};

void Particle::setup(){}

void Particle::run(){update();}

// Method to display
void Particle::display() {}

const type_info& Particle::get_typeid() {
    return typeid(this);
}

void Particle :: update() {
    vel.value += acc.value;
    elastic_boundery();
    loc.value += vel.value;
    //Aplly relax_fact
    vel.value *= ofVec3f(relax.value);
    relax.value = 1.0;
    //bound_particles_location();

    // Clear accelaration to allow comulative 
    // interactions and order independency:
    acc.value = ofVec3f(0);
}


/*
void Particle :: bound_particles_location(){
   int offset = rad;

   if (locat.x < offset){
       locat.x = offset;
   } else if (locat.x > ofGetWindowWidth()-offset){
       locat.x = ofGetWindowWidth()-offset;
   }
   if (locat.y < offset){
       locat.y = offset;
   } else if (locat.y > ofGetWindowHeight()-offset){
       locat.y = ofGetWindowHeight()-offset;
   }
}

void Particle :: set_speedLimit(int maxSpeed){
   
   if (veloc.x < -1 * maxSpeed){
       veloc.x = -1 * maxSpeed;
   } else if (veloc.x > maxSpeed){
       veloc.x = maxSpeed;
   }
   if (veloc.y < -1 * maxSpeed){
       veloc.y = -1 * maxSpeed;
   } else if (veloc.y > maxSpeed){
       veloc.y = maxSpeed;
   }
}
*/

void Particle :: elastic_boundery(){
    //int offset = *get_item_parameter<int>("rad");
    int* offset = &get_item_parameter<int>("rad")->value;
    ofVec3f* locat = &loc.value;
    ofVec3f* veloc = &vel.value;

    //Elastic bounds
    if ( (locat->x <= *offset &&  veloc->x < 0) ||
         (locat->x >= ofGetWindowWidth() - *offset &&  veloc->x > 0) ){
        veloc->x *= -1;
    }
    if ( (locat->y <= *offset && veloc->y < 0) ||
         (locat->y >= ofGetWindowHeight() - *offset && veloc->y > 0) ){
        veloc->y *= -1;
    }
}

Circle::Circle() : Particle(){
    set_name(get_type_name());
}

const type_info& Circle::get_typeid() {
    return typeid(this);
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(color.value);
    ofVec3f* loc_val = &loc.value;
    int* rad_val = &rad.value;
    ofEllipse(loc_val->x,loc_val->y,*rad_val,*rad_val);
}

Sphere::Sphere() : Particle(){
    set_name(get_type_name());
    sphere.setRadius( rad.value );
    tmp_rad = rad.value;
    spin_fac = 1.5708/tmp_rad; // (pi/2)/r
}

const type_info& Sphere::get_typeid() {
    return typeid(this);
}

void Sphere :: display() {
    if (rad.value != tmp_rad and rad.value > 0){
        sphere.setRadius( rad.value );
        tmp_rad = rad.value;
        spin_fac = 1.5708/tmp_rad; // pi/(2*r)
    }
    ofSetColor(color.value);
    ofVec3f* loc_val = &loc.value;
    sphere.setPosition(loc_val->x, loc_val->y, 0);
    sphere.rotate(vel.value.y*spin_fac, 1.0, 0.0, 0.0);
    sphere.rotate(vel.value.x*spin_fac, 0, 1.0, 0.0);
    sphere.draw();
}

Line :: Line() : Particle(){
    set_name(get_type_name());
    color.value = ofColor(100,255,255);
}

const type_info& Line::get_typeid() {
    return typeid(this);
}

void Line :: update() {
    Particle::update();
    ofVec3f centroid2D = points.getCentroid2D();
    if (!(isnan(centroid2D.x) or isnan(centroid2D.y) or isnan(centroid2D.z)))
        loc.value = centroid2D;
    
    ofVec3f disp = vel.value;
    //for(vector<ofPoint>::iterator p_it = points.getVertices().begin();
    for(vector<glm::vec3>::iterator p_it = points.getVertices().begin();
                                  p_it != points.getVertices().end();
                                  p_it++)
        *p_it += disp;
    
}
void Line :: display() {
    ofSetColor(color.value);
    ofSetLineWidth(3);
    //ofPushMatrix();
    //ofVec3f disp = vel.value;
    //ofTranslate(disp);
    //ofTranslate(ofVec3f(0));
    points.draw();
    //ofPopMatrix();
}
