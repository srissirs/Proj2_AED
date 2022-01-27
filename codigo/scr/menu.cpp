#include <iostream>
#include "menu.h"

using namespace std;
void displayMainMenu(){
    cout << "-------------MENU-------------"<<endl;
    cout << "[1] Choose stops by their code"<<endl;
    cout << "[2] Choose stops by coordinates" << endl;
    cout << "[0] Exit"<<endl;
}

void displayStopsCodeMenu(){
    cout << "-------------MENU-------------"<<endl;
    cout << "[0] Choose stops by their code"<<endl;
    cout << "[1] Choose stops by coordinates" << endl;
}


void displaysCoordinatesMenu(){
    cout << "-------------MENU-------------"<<endl;
    cout << "[0] Choose stops by their code"<<endl;
    cout << "[1] Choose stops by coordinates" << endl;
}


void displaysMethods(){
    cout << "-----------METHODS------------"<<endl;
    cout << "[1] Best price"<<endl;
    cout << "[2] Less changes between lines" << endl;
    cout << "[3] Less bus stops" << endl;
    cout << "[4] Smallest distance" << endl;
    cout << "[0] Exit"<<endl;
}