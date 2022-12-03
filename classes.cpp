class Entity {
    private:       
        int health;    //10
        int strength;  //1 - 3
        int defense;   //1 - 2
        int healing;   // 0 - 2
    protected:
        int pos;   // 0 - x*y
    public:
        int get_health() {
            return health;
        }

        int get_strength() {
            return strength;
        }

        int get_defense() {
            return defense;
        }

        int get_pos() {
            return pos;
        }

        void set_health(int x) {
            health = x;
        }

        void set_strength(int x) {
            strength = x;
        }

        void set_defense(int x) {
            defense = x;
        }
};

class Vampire: public Entity {
    private:
        
    protected:
        //edo erxontai ta protected apo hyperclass
    public:
        //edo erxontai ta public apo hyperclass
        Vampire(int s,int d,int p) {
            set_health(10);
            set_strength(s);
            set_defense(d);
            pos = p;
        }
};

class Werewolf: public Entity {
    private:
        
    protected:
        //edo erxontai ta protected apo hyperclass
    public:
        //edo erxontai ta public apo hyperclass
        Werewolf(int s,int d,int p) {
            set_health(10);
            set_strength(s);
            set_defense(d);
            pos = p;
        }
};

class Avatar: public Entity {
    private:

    public:
        Avatar(int p) {
            pos = p;
        }
};





class Obstacles {
    protected:
        int pos;
    public:
        int get_pos() {
            return pos;
        }
};

class Trees: public Obstacles {
    public:
        Trees(int p) {
            pos = p;
        }

};

class Lakes: public Obstacles {
    public:
        Lakes(int p) {
            pos = p;
        }
};


class Potion: public Obstacles {
    public:
        Potion(int p) {
            pos = p;
        }
};


void attack() {

}

void heal_ally() {
    
}