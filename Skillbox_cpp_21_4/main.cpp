#include <iostream>
#include "vector"
#include "cstdlib"
#include "fstream"
#include "ctime"

std::string filepath="C:\\Users\\Azamat\\CLionProjects\\Skillbox\\module_21\\Skillbox_cpp_21_4\\resources\\save.bin";


enum COMMAND{
    NONE=-1,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SAVE,
    LOAD
};

struct coord{
    int x,y;
};

bool inRange(struct coord &coord){
    return (coord.x>=0 && coord.x<20) && (coord.y>=0 &&coord.y<20);
}

struct person {
    int health;
    int armor;
    int damage;
    bool npc;
    struct coord coords;
    std::string name;
};

void placeOnField(std::vector<person> &persons);

int input(std::string prompt){
    int res;
    std::cout << prompt;
    std::cin >>res;
    return res;
}

std::string inputs(std::string prompt){
    std::string res;
    std::cout << prompt;
    std::cin >>res;
    return res;
}

float inputf(std::string prompt){
    float res;
    std::cout << prompt;
    std::cin >>res;
    return res;
}


void print_stat(const std::vector<person> &persons){
    return;
    std::string gap="\t\t";
    for(int i=0;i<persons.size();++i){
        std::cout << persons[i].name<<"\t";}
    std::cout<< std::endl;
    for(int i=0;i<persons.size();++i){
        std::cout << (persons[i].npc?"Enemy":"Player")<<gap;}
    std::cout<< std::endl;
    for(int i=0;i<persons.size();++i){
        std::cout << "H:"<<persons[i].health<<gap; }
    std::cout << std::endl;
    for(int i=0;i<persons.size();++i){
        std::cout <<"A:" <<persons[i].armor<<gap;}
    std::cout<< std::endl;
    for(int i=0;i<persons.size();++i){
        std::cout << "D:"<<persons[i].damage<<gap;}
    std::cout<< std::endl;
    for(int i=0;i<persons.size();++i){
        std::cout <<"X:"<< persons[i].coords.x<<gap;}
    std::cout<< std::endl;
    for(int i=0;i<persons.size();++i){
        std::cout <<"Y:"<< persons[i].coords.y<<gap;}
    std::cout<< std::endl;
}

void print_field(std::vector<person> &persons){
    char field[20][20];
    std::string gap="\t";
    for(int i=0;i<20*20;++i) field[i/20][i%20]='.';
    for(int i=0;i<persons.size();++i) {
        if (persons[i].health>0&&persons[i].npc) field[persons[i].coords.x][persons[i].coords.y] = 'E';
        else if (persons[i].health>0) field[persons[i].coords.x][persons[i].coords.y] = 'P';
    }

    for (int y=19;y>=0;--y){
        for(int x=0;x<20;++x){
            std::cout << field[x][y]<<" ";
        }
        switch (y) {
            case 8:
                for(int i=0;i<persons.size();++i)
                    std::cout << persons[i].name<<"   ";
                break;
            case 7:
                for(int i=0;i<persons.size();++i)
                    std::cout << (persons[i].npc?"Enemy":"Player")<<gap;
                break;
            case 6:
                for(int i=0;i<persons.size();++i)
                    std::cout << "H:"<<persons[i].health<<gap;
                break;
            case 5:
                for(int i=0;i<persons.size();++i){
                    std::cout <<"A:" <<persons[i].armor<<gap;}
                break;
            case 4:
                for(int i=0;i<persons.size();++i){
                    std::cout << "D:"<<persons[i].damage<<gap;}
                break;
            case 3:
                for(int i=0;i<persons.size();++i){
                    std::cout <<"X:"<< persons[i].coords.x<<gap;}
                break;
            case 2:
                for(int i=0;i<persons.size();++i){
                    std::cout <<"Y:"<< persons[i].coords.y<<gap;}
                break;
        }
        std::cout << std::endl;
    }
}

void init(std::vector<person> &persons){
    srand(time(nullptr));
    persons.clear();
    for (int i =0 ;i<5;++i){
        struct person new_person;
        new_person.name="Enemy #" + std::to_string(i+1);
        new_person.health=rand()%100+50;
        new_person.damage=rand()%15+15;
        new_person.armor=rand()%50;
        new_person.npc=true;
        persons.push_back(new_person);
    }
    struct person new_person;
    new_person.npc=false;
    new_person.name = inputs("Input your name:");
    new_person.health = input("Input health:");
    new_person.armor= input("Input armor:");
    new_person.damage=input("Input damage:");
    persons.push_back(new_person);
    placeOnField(persons);
}

bool coords_match(struct coord &coord1,struct coord &coord2){
    return (coord1.x==coord2.x && coord1.y==coord2.y);
}

bool notCollide(std::vector<person> &persons,struct coord &coord){
    for (int i=0;i<persons.size();++i){
        if (coords_match(persons[i].coords,coord)) return false;
    }
    return true;
}

void placeOnField(std::vector<person> &persons){
    for (int i=0;i<persons.size();++i) {
        struct coord new_coord;
        do {
            new_coord.x=rand()%20;
            new_coord.y=rand()%20;
        } while (!notCollide(persons,new_coord));
        persons[i].coords=new_coord;
    }
}
void save(std::vector<person> &persons){
    std::ofstream file(filepath,std::ios::binary);
    if(file.is_open()){
        int size=persons.size();
        file.write((char*)&size, sizeof(size));
        for (int i=0;i<persons.size();++i){
            file.write((char*)&persons[i].health, sizeof(persons[i].health));
            file.write((char*)&persons[i].armor, sizeof(persons[i].armor));
            file.write((char*)&persons[i].damage, sizeof(persons[i].damage));
            file.write((char*)&persons[i].coords, sizeof(persons[i].coords));
            file.write((char*)&persons[i].npc, sizeof(persons[i].npc));
            size=persons[i].name.size();
            file.write((char*)&size, sizeof(int));
            file.write(persons[i].name.c_str(), size);
        }
        file.close();
    }
}

void load(std::vector<person> &persons){
    std::ifstream file(filepath,std::ios::binary);
    if(file.is_open()){
        const int name_buf_size=40;
        char namebuf[name_buf_size]={0,};
        persons.clear();
        int vec_size=0,size =0;
        file.read((char*)&vec_size, sizeof(vec_size));
        for (int i=0;i<vec_size;++i){
            struct person new_person;
            file.read((char*)&new_person.health, sizeof(new_person.health));
            file.read((char*)&new_person.armor, sizeof(new_person.armor));
            file.read((char*)&new_person.damage, sizeof(new_person.damage));
            file.read((char*)&new_person.coords, sizeof(new_person.coords));
            file.read((char*)&new_person.npc, sizeof(new_person.npc));
            file.read((char*)&size, sizeof(size));
            file.read(namebuf, (size<name_buf_size?size:name_buf_size-1));
            namebuf[size]=0;
            new_person.name=namebuf;
            persons.push_back(new_person);
        }
        file.close();
    } else init(persons);
}

bool game_over(std::vector<person> &persons){
    int enemy_health_total=0;
    for(int i=0;i<persons.size();++i) {
        if (!persons[i].npc&&persons[i].health==0) {
            std::cout<<"=== PLAYER LOSE ===\n";
            return true;
        }
        if (persons[i].npc) enemy_health_total+=persons[i].health;
    }
    if (enemy_health_total==0) {
        std::cout<<"=== PLAYER WIN ===\n";
        return true;
    }
    return false;
}

COMMAND get_command(){
    COMMAND command=SAVE;
    do{
       std::string commands=inputs("Input command:\n");
       if (commands=="w") command = UP;
       else if(commands=="s") command=DOWN;
       else if (commands=="a") command=LEFT;
       else if (commands=="d") command=RIGHT;
       else if (commands=="load") command=LOAD;
       else if (commands=="save") command=SAVE;
       else command=NONE;
    } while (command<=NONE || command>LOAD);
    return command;
}

struct coord move(const struct coord &coord1,const struct coord &move){
    struct coord new_coord;
    new_coord.x=coord1.x+move.x;
    new_coord.y=coord1.y+move.y;
    return new_coord;
}

struct coord get_move(COMMAND comm){
    coord new_move;
    new_move.x=0;new_move.y=0;
    switch (comm) {
        case UP:
            new_move.y = 1;
            break;
        case DOWN:
            new_move.y = -1;
            break;
        case LEFT:
            new_move.x = -1;
            break;
        case RIGHT:
            new_move.x = 1;
            break;
        case SAVE:
        case LOAD:
        case NONE:
        default:
            break;
    }
    return new_move;
}

COMMAND generate_move_command(){return (COMMAND)(rand()%4);}

void attack(const struct person &attacker, struct person &victim){
    victim.armor-=attacker.damage;
    if (victim.armor < 0) {
        victim.health+=victim.armor;
        victim.armor=0;
    }
    if(victim.health < 0)victim.health=0;
}

void game(std::vector<person> &persons){
    init(persons);
    print_field(persons);
    while(!game_over(persons)){
        COMMAND comm;
        for(int i=0;i<persons.size();++i){
            if (!persons[i].npc) print_field(persons);
            struct coord new_move = (persons[i].npc?
                    get_move(generate_move_command()):
                    get_move(get_command()));
            struct coord new_coord = move(persons[i].coords, new_move);
            bool no_collides = notCollide(persons, new_coord);
            if(no_collides &&
               inRange(new_coord)){
                persons[i].coords=new_coord;
            } else if (!no_collides){
                for (int k=0;k<persons.size();++k){
                    if (coords_match(persons[k].coords,new_coord)&&
                        persons[i].npc!=persons[k].npc){
                        attack(persons[i],persons[k]);
                    };
                }
            }
        }
        switch (comm) {
            case UP:
            case DOWN:
            case LEFT:
            case RIGHT:
                break;
            case LOAD:
                load(persons);
                break;
            case SAVE:
                save(persons);
                break;
            default:
                break;
        }

    }
}

int main() {
    std::vector<person> persons;

//    init(persons);
//    save(persons);
    load(persons);

    game(persons);
}
