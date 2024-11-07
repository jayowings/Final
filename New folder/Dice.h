class Dice{
    public:
        int value;
        bool save = false;
        void roll(){
            this->value = (rand() % 6) + 1;
        };
};