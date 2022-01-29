#include <iostream>
#include "menu.h"

using namespace std;

/**
 * @brief Menu where users choose if they want to search for the stops by their codes or if he wants to
 * see the closest stops to some coordinates
 */
void displayMainMenu(){
    cout << "-------------MENU-------------"<<endl;
    cout << "[1] Choose stops by their code"<<endl;
    cout << "[2] Choose stops by coordinates" << endl;
    cout << "[0] Exit"<<endl;
}

/**
 * @brief Menu where users choose if they want to see the travel path from day lines, night lines or both
 */
void displayTimeOfTheDay(){
    cout << "-------------MENU-------------"<<endl;
    cout<< "Search for:"<<endl;
    cout << "[0] All lines (day and night)"<<endl;
    cout << "[1] Day lines" << endl;
    cout << "[2] Night lines" << endl;
}

/**
 *@brief Menu where users choose which method to use for the path that connects the stops
 */
void displaysMethods(){
    cout << "-----------METHODS------------"<<endl;
    cout << "[1] Best price"<<endl;
    cout << "[2] Less changes between lines" << endl;
    cout << "[3] Less bus stops" << endl;
    cout << "[4] Smallest distance" << endl;
    cout << "[0] Exit"<<endl;
}