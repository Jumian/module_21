#include <iostream>
#include "vector"

enum BUILDING_T{
    HOUSE,
    BATH,
    GARAGE,
    BARN
};

enum ROOM_T{
    BEDROOM,
    KITCHEN,
    BATHROOM,
    CHILDRENSROOM,
    LOUNGE
};

std::vector<std::string> building_t_str={"HOUSE","BATH","GARAGE","BARN"};
std::vector<std::string> room_t_str={"BEDROOM", "KITCHEN","BATHROOM","CHILDREN'S ROOM","LOUNGE"};

struct room{
    float area;
    ROOM_T r_type;
};

struct floor{
    int number;
    float height;
    std::vector<room> rooms;
};

struct building{
    float area;
    bool chimney;
    BUILDING_T b_type;
    std::vector<floor> floors;
};

struct site{
    float area;
    std::vector<building> buildings_v;
};

struct village{
    float area;
    std::vector<site> sites;
};



int input(std::string prompt){
    int res;
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
void print_delimiter(int layer,std::string str){
    for(int i=0;i<12-layer;++i) std::cout<<"=";
    std::cout<<" "<<str<<" ";
    for(int i=0;i<12-layer;++i) std::cout<<"=";
    std::cout<<std::endl;
}

enum ROOM_T input_room_t(){
    std::cout << "Input ";
    for(int i=0;i<room_t_str.size();++i){
        std::cout<<i<<")"<<room_t_str[i]<<" ";
    }
    int inputval = input("\nType:");
    if(inputval>=0&&inputval<room_t_str.size())
        return (ROOM_T)inputval;
    return BEDROOM;
}

enum BUILDING_T input_building_t(){
    for(int i=1;i<building_t_str.size();++i){
        std::cout<<i<<")"<<building_t_str[i]<<" ";
    }
    int inputval= input("\nInput type number:");
    if(inputval>0&&inputval<building_t_str.size())
        return (BUILDING_T)inputval;
    else return HOUSE;
}

struct room complete_room(){


}

void complete_rooms(std::vector<room> &rooms,int max){
    struct room new_room;
    for (int i=0;i<max;++i){
        print_delimiter(9,"Room #"+std::to_string(i+1)+". Start");
        new_room.r_type= input_room_t();
        new_room.area=inputf("Input room #"+ std::to_string(i+1)+" area:");
        rooms.push_back(new_room);
        print_delimiter(9,"Room #"+std::to_string(i+1)+". Complete");
    }
}

void complete_floors(std::vector<floor> &floors,int max){
    struct floor new_floor;
    for(int i=0;i<max;++i){
        print_delimiter(7,"Floor #"+std::to_string(i+1)+". Start");
        new_floor.number=i+1;
        new_floor.height=inputf("Input floor #"+ std::to_string(new_floor.number)+" height:");
        int room_number= input("Input number of rooms[2..4]:");
        complete_rooms(new_floor.rooms,room_number<2?2:(room_number<5?room_number:4));
        floors.push_back(new_floor);
        print_delimiter(7,"Floor #"+std::to_string(i+1)+". Complete");
    }
}

bool input_chimney(){
    return input("Is there a chimney[1-YES]:")==1;
}

void complete_building(std::vector<building> &buildings_v,int max){
    struct building new_building;
    for(int i=1;i<max;++i){
        print_delimiter(3,"Building #"+std::to_string(i+1)+". Start");
        new_building.b_type=input_building_t();

        if(new_building.b_type<=BATH) new_building.chimney=input_chimney();
        else new_building.chimney=false;
        buildings_v.push_back(new_building);
        print_delimiter(3,"Building #"+std::to_string(i+1)+". Complete");
    }
    new_building.floors.clear();
    print_delimiter(3,"Building #1 House. Start");
    new_building.b_type=HOUSE;
    new_building.area=inputf("Input building area:");
    new_building.chimney=input_chimney();
    int floors_number=input("Input number of floors[1..3]:");
    complete_floors(new_building.floors,floors_number<0?1:(floors_number<4?floors_number:3));
    buildings_v.push_back(new_building);
    print_delimiter(3,"Building #1 House. Complete");
}

void complete_sites(std::vector<site> &sites,int max){
    struct site new_site;
    for(int i=0;i<max;++i){
        print_delimiter(1,"Site #"+std::to_string(i+1)+". Start");
        new_site.area= inputf("Input site #"+ std::to_string(i+1)+" area:");
        complete_building(new_site.buildings_v,input("Input number of buildings:"));
        sites.push_back(new_site);
        print_delimiter(1,"Site #"+std::to_string(i+1)+". Complete");
    }
}

float buildings_area(std::vector<building> &building){
    float result=0;
    for(int i=0;i<building.size();++i) result+=building[i].area;
    return result;
}
float sites_buildings_area(std::vector<site> &sites){
    float result=0;
    for(int i=0; i < sites.size(); ++i) result+=buildings_area(sites[i].buildings_v);
    return result;
}

float sites_area(std::vector<site> &sites){
    float result=0;
    for(int i=0; i < sites.size(); ++i) result+=sites[i].area;
    return result;
}


float area_usage(struct village &village_struct){
    return sites_buildings_area(village_struct.sites)/sites_area(village_struct.sites)*100;
}

int main() {
    struct village village_struct;
    complete_sites(village_struct.sites,input("Input number of sites in village:"));
    std::cout << "Area usage is " << area_usage(village_struct) << "percent\n";
}
