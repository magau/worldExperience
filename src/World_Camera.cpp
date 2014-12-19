#include "testApp.h"

World_Camera::World_Camera() : ofCamera(), Item() {
   
   travel_distance_factor = 10.;
   set_callback("tilt",(void (Item::*)(shared_variable*)) (&World_Camera::tilt_shv));
   set_callback("pan",(void (Item::*)(shared_variable*)) (&World_Camera::pan_shv));
   set_callback("travel",(void (Item::*)(shared_variable*)) (&World_Camera::travel_shv));
}

void World_Camera::travel_shv(shared_variable* shv_imput_param){

    if( shv_imput_param->type_enum == IP_BOOL) {

        bool reverse = static_cast<Item_Parameter<bool>*>(shv_imput_param->value)->value;
        int direction;

        if (reverse)
            direction = -1;
        else
            direction = 1;

        setPosition(getPosition() + (direction * travel_distance_factor * getZAxis()));
    }
}

void World_Camera::tilt_shv(shared_variable* shv_imput_param){
    Item_Parameter<int> view_angle(pair<int,int>(0,360));
    shared_variable shv_view_angle(&view_angle,IP_INT);
    map_shv_parameter(&shv_view_angle, shv_imput_param);

    ofVec3f eulerAngles = getOrientationEuler();
    ofQuaternion q(view_angle.value,ofVec3f(1,0,0),eulerAngles.z,ofVec3f(0,0,1),eulerAngles.y,ofVec3f(0,1,0));
    setOrientation(q);
}

void World_Camera::pan_shv(shared_variable* shv_imput_param){
    Item_Parameter<int> view_angle(pair<int,int>(-180,180));
    shared_variable shv_view_angle(&view_angle,IP_INT);
    map_shv_parameter(&shv_view_angle, shv_imput_param);

    ofVec3f eulerAngles = getOrientationEuler();
    ofQuaternion q(eulerAngles.x,ofVec3f(1,0,0),eulerAngles.z,ofVec3f(0,0,1),view_angle.value,ofVec3f(0,1,0));
    //ofQuaternion q(eulerAngles.x,ofVec3f(1,0,0),view_angle.value,ofVec3f(0,1,0),eulerAngles.z,ofVec3f(0,0,1));
    setOrientation(q);
    //ofQuaternion q = getOrientationQuat();
    //q.makeRotate(view_angle.value,ofVec3f(0,1,0));
}

