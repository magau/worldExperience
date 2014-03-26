class Controller : public Item {
    public:
        ofEvent<bool> iterate_variable;
        string var_name;
        bool notify;
        bool _rise;
        void notify(){ofNotifyEvent(iterate_variable,rise,this);}
        void set_val(bool rise){_rise = rise;}
}
