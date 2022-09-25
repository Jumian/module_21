#include <iostream>
#include "fstream"
#include "vector"
#include "sstream"

std::string filepath = "C:\\Users\\Azamat\\CLionProjects\\Skillbox\\module_21\\Skillbox_cpp_21_1\\resources\\accounts.txt";

struct transaction {
    std::string name;
    std::string surname;
    std::string date;
    int ammount;
};

std::vector<transaction> trans;


std::string  input (std::string prompt){
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

bool isNumber(std::string str){
    if (str.size()==0) return false;
    for(int i=0;i<str.size();++i) if (str[i]<'0'||str[i]>'9') return false;
    return true;
}

bool dataIsValid(std::string date){
    int D=0,M=0,Y=0;
    char dayChr[3]={0,},monthChr[3]={0,},yearChr[10]={0,};
    std::stringstream ssDate(date);
    if(!ssDate.eof())ssDate.getline((char*)dayChr,   3,'.');
    if(!ssDate.eof())ssDate.getline((char*)monthChr, 3,'.');
    if(!ssDate.eof())ssDate.getline((char*)yearChr,  10,'.');
    if(isNumber(dayChr)) D = std::stoi(dayChr);
    if(isNumber(monthChr)) M = std::stoi(monthChr);
    if(isNumber(yearChr)) Y = std::stoi(yearChr);
    return (D > 0 && (
            (D<=31 && (M==1||M==3||M==5||M==7||M==8||M==10||M==12)) ||
            (D<=30 && (M==4||M==6||M==9||M==11))       ||
            (M==2  && ((D<=29 && (Y%4==0 && Y%100!=0)) ||
                       (D<=28 && ((Y%4==0 && Y%100==0)  || Y%4!=0)) ))));
}

void append(transaction & trans){
    std::ofstream file(filepath,std::ios::app);
    file <<
        trans.name      <<" "<<
        trans.surname   <<" "<<
        trans.date      <<" "<<
        trans.ammount   <<std::endl;
    file.close();
}

transaction pull(std::stringstream &stream){
    transaction new_trans;
    stream >>
        new_trans.name>>
        new_trans.surname>>
        new_trans.date>>
        new_trans.ammount;
    return new_trans;
}

void print(){
    for(int i=0;i<trans.size();++i){
        std::cout<<
                 trans[i].date       <<"\t"<<
                 trans[i].surname    <<"\t"<<
                 trans[i].name       <<"\t"<<
                 trans[i].ammount    <<std::endl;
    }
}
void list(){
    std::ifstream file(filepath);
    std::string buf;

    while(!file.eof()){
        std::getline(file,buf);
        if(buf!="") {
            std::stringstream stream(buf);
            trans.push_back(pull(stream));
        }
    }
    file.close();
    print();
    std::cout <<std::endl;
}

transaction fill(){
    std::string date;
    transaction trans;
    trans.name = input("Input name:");
    trans.surname = input("Input surname:");
    do{date = input("Input date:");}
    while(!dataIsValid(date));
    trans.date = date;
    std::string ammount = input("Input ammount:");
    trans.ammount=std::stoi(ammount);
    return trans;
}

int main() {
    std::string command=input("Input command[add,list]:");
    if (command=="list"){
        list();
    } else if(command=="add"){
        transaction new_trans(fill());
        append(new_trans);
    }
    std::cout << "Program finished" << std::endl;
    return 0;
}
