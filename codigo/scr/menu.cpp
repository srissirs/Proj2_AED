#include <iostream>
#include "menu.h"

using namespace std;
void displayMainMenu(){
    cout << "-------------MENU-------------"<<endl;
    cout << "[0] Choose stops by their code"<<endl;
    cout << "[1] Choose stops by coordinates" << endl;
}

void displayTimeOfTheDay(){
    cout << "-------------MENU-------------"<<endl;
    cout<< "Search for:"<<endl;
    cout << "[0] All lines (day and night)"<<endl;
    cout << "[1] Day lines" << endl;
    cout << "[2] Night lines" << endl;
}

void displaysMethods(){
    cout << "-----------METHODS------------"<<endl;
    cout << "[0] Best price (less zones)"<<endl;
    cout << "[1] Less changes between lines" << endl;
    cout << "[2] Less bus stops" << endl;
    cout << "[3] Smallest distance" << endl;
}