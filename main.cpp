//Author : Ruben Rehal
//Date : November 18, 2024
//Hierarchical Text Classification

#include <iostream>
#include "textClass.hpp"

int main () {

    Trie trie;
    std::string command;

    std::string label;
    std::string filename;

    while ( std::cin >> command ){
        
        if ( command == "LOAD" ) {
            std::getline(std::cin, filename);
            filename = filename.substr(filename.find_first_not_of(" \t")); // Trim leading spaces
            trie.load(filename);
        }
        else if ( command == "INSERT" ) {
            std::getline(std::cin, label);
            label = label.substr(label.find_first_not_of(" \t")); // Trim leading spaces
            trie.insert(label);
        } 
        else if ( command == "CLASSIFY" ) {
            std::getline(std::cin, label);
            label = label.substr(label.find_first_not_of(" \t")); // Trim leading spaces
            trie.classify(label);
        }
        else if ( command == "ERASE" ) {
            std::getline(std::cin, label);
            label = label.substr(label.find_first_not_of(" \t")); // Trim leading spaces
            trie.erase(label);
        }
        else if ( command == "PRINT" ) {
            trie.print();
        }
        else if ( command == "EMPTY" ) {
            trie.empty();
        }
        else if ( command == "CLEAR" ) {
            trie.clear(); 
            std::cout << "success" << std::endl;
        }
        else if ( command == "SIZE" ) {
            trie.size();
        }
        else if ( command == "EXIT" ) {
            break;
        }
    }

    return 0;
}
