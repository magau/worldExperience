class Control_Event : public Item{
    private:
        ofEvent<bool>* bool_event;
        ofEvent<int>* int_event;
        ofEvent<float>* float_event;
        ~Control_Event();
        Control_Event();
        string controlled_attr_name;
}
