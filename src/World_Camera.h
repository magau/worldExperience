class World_Camera : public ofCamera, public Item{
    public:
        float travel_distance_factor;
        World_Camera();
        void travel_shv(shared_variable* shv_imput_param);
        void tilt_shv(shared_variable* shv_imput_param);
        void pan_shv(shared_variable* shv_imput_param);
};
