#include <iostream>
#include "vector"
#include "cmath"
enum COMMAND{
    ADD,
    SUBSTRUCT,
    SCALE,
    LENGTH,
    NORMALIZE,
    NONE
};

std::vector<std::string> COMMAND_STR={
        "ADD",
        "SUBSTRUCT",
        "SCALE",
        "LENGTH",
        "NORMALIZE",
        "NONE"
};

struct vect{
    float x;
    float y;
};

void print_vec(struct vect vec){
    std::cout << "Vector X:"<<vec.x<<" Y:"<<vec.y<<"\n";
}

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

struct vect input_vector(){
    struct vect new_vect;
    new_vect.x=inputf("Input X:");
    new_vect.y=inputf("Input Y:");
    return new_vect;
}


enum COMMAND input_command_t(){
    std::cout << "Choose command ";
    for(int i=0;i<COMMAND_STR.size();++i){
        std::cout<<i<<")"<<COMMAND_STR[i]<<" ";
    }
    int inputval = input("\ncommand number:");
    if(inputval>=0&&inputval<COMMAND_STR.size())
        return (COMMAND)inputval;
    return NONE;
}

struct vect add(const struct vect &vect1,const struct vect &vect2){
    struct vect new_vect;
    new_vect.x=vect1.x+vect2.x;
    new_vect.y=vect1.y+vect2.y;
    return new_vect;
}

struct vect substruct(const struct vect &vect1,const struct vect &vect2){
    struct vect new_vect;
    new_vect.x=vect1.x-vect2.x;
    new_vect.y=vect1.y-vect2.y;
    return new_vect;
}

struct vect scale(const struct vect &vect1,float scale){
    struct vect new_vect;
    new_vect.x=vect1.x*scale;
    new_vect.y=vect1.y*scale;
    return new_vect;
}

float veclength(const struct vect &vect){
    return sqrt(vect.x*vect.x+vect.y*vect.y);
}

struct vect normalize(const struct vect &vect){
    struct vect new_vect;
    float length = veclength(vect);
    new_vect.x=vect.x/length;
    new_vect.y=vect.y/length;
    return new_vect;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    COMMAND command = input_command_t();
    switch (command){
        case  ADD:{
            std::cout << "Vector 1:"<<std::endl;
            struct vect vect1 = input_vector();
            std::cout << "Vector 2:"<<std::endl;
            struct vect vect2 = input_vector();
            print_vec(add(vect1,vect2));
            break;
        }
        case  SUBSTRUCT:{
            std::cout << "Vector 1:"<<std::endl;
            struct vect vect1 = input_vector();
            std::cout << "Vector 2:"<<std::endl;
            struct vect vect2 = input_vector();
            print_vec(substruct(vect1,vect2));
            break;}
        case SCALE: {
            std::cout << "Vector:"<<std::endl;
            struct vect vector = input_vector();
            float vecscale = inputf("Input scale");
            print_vec(scale(vector, vecscale));
            break;
        }
        case LENGTH: {
            std::cout << "Vector:"<<std::endl;
            struct vect vector = input_vector();
            std::cout << "Vector length:" << veclength(vector) << std::endl;
            break;
        }
        case NORMALIZE: {
            std::cout << "Vector:"<<std::endl;
            struct vect vector = input_vector();
            print_vec(normalize(vector));
            break;
        }
        case NONE:
        default:
            break;
    }
}
