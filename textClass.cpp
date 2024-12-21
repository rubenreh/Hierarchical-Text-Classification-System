// Author : Ruben Rehal
// Date : November 18, 2024
// Hierarchical Text Classification


#include "textClass.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "socket.hpp"


Node::Node() {
    terminal = false;
    label = "";
    for (int i{0}; i < 15; i++) {
        children[i] = nullptr;
    }
}

Node::~Node() {
    for (int i{0}; i < 15; i++) {
        if (children[i] != nullptr) {
            delete children[i];
            children[i] = nullptr;
        }
    }
}


Trie::Trie() {
    root = nullptr;
    itemcount = 0;
}

Trie::~Trie() {
    clear();
}

void Trie::load(std::string filename) {
    std::ifstream file(filename);           // Open File Stream
    std::string line;
    bool inserted;
    
    // Read file line-by-line
    while (std::getline(file, line)) {
        if (!line.empty()) {  
            inserted = place(line);  
        }
    }
    file.close();
    std::cout << "success" << std::endl;
}


bool Trie::place(std::string path) {
    std::istringstream stream(path);
    std::string single_label;
    Node* current = root;

    bool increment = false;

    Node* previous = current;

    // Create root if it doesn't exist
    if (current == nullptr) {
        root = new Node();
        current = root;
    }

    bool exists = true;         // Assume path exists until proven otherwise

    while (std::getline(stream, single_label, ',')) {
        bool found = false;
        int empty_slot = -1;

        // Search for the label among children
        for (int i = 0; i < 15; i++) {
            if (current -> children[i] != nullptr) {
                if (current -> children[i] -> label == single_label) {
                    current = current -> children[i];
                    found = true;
                    break;
                }
            } else if (empty_slot == -1) {
                empty_slot = i;
            }
        }

        // If label not found, create a new node
        if (!found) {
            if (empty_slot != -1) {
                current -> children[empty_slot] = new Node();
                current -> children[empty_slot] -> label = single_label;
                current -> children[empty_slot] -> terminal = false;
                current = current -> children[empty_slot];
                exists = false;         // New path inserted
            } else {
                // No available slot to insert new child
                return true; // Indicate failure to insert
            }
        }
        previous = current;
    }

    // After traversing all labels, mark the node as terminal
    if (current -> terminal) {
        return true; // Classification already exists
    } else {
        if (children_empty(current)) {
            current -> terminal = true;
                itemcount++;
                return false;
        } else {
            return true;
        }
    }
}

void Trie::insert(std::string path) {
    try {
        // Validate input: no uppercase letters
        for (char c : path) {
            if (isupper(c)) throw illegal_exception();
        }

        bool insertion = place(path);

        if (!insertion) {
            std::cout << "success" << std::endl;
        } else {
            std::cout << "failure" << std::endl;
        }
        
    } catch (illegal_exception&) {
        std::cout << "illegal argument" << std::endl;
        return;
    }
}


void Trie::classify(std::string targetLabel) {
    try {
        // Validate input: no uppercase letters
        for (char c : targetLabel) {
            if (isupper(c)) throw illegal_exception();
        }

        if (root == nullptr) {
            std::cout << "failure" << std::endl;
            return;
        }

        Node* current = root;
        std::string classification = "";

        while (current != nullptr) {
            // Build list of available labels at current level
            std::string labelList = "";

            for (int i{0}; i < 15; i++) {
                if (current -> children[i] != nullptr) {
                    if (!labelList.empty()) {
                        labelList += ",";
                    }
                    labelList += current -> children[i] -> label;
                }
            }

            if (labelList.empty()) {
                break;
            }

            std::string next_label = labelText(targetLabel, labelList);
            if (next_label.empty()) {
                break;
            }

            Node* next_node = nullptr;
            for (int i{0}; i < 15; i++) {
                if (current -> children[i] != nullptr &&
                    current -> children[i] -> label == next_label) {
                    next_node = current -> children[i];
                    
                    if (!classification.empty()) {
                        classification += ",";
                    }
                    classification += next_label;
                    break;
                }
            }
            if (next_node == nullptr) {
                break;
            }
            current = next_node;
        }

        if (classification.empty()) {
            std::cout << "failure" << std::endl;
        } else {
            std::cout << classification << std::endl;
        }

    } catch (const illegal_exception&) {
        std::cout << "illegal argument" << std::endl;
        return;
    }
}

void Trie::erase(std::string classification) {
    try {
        for (char c : classification) {
            if (isupper(c)) throw illegal_exception();
        }

        if ( root == nullptr ) {
            std::cout << "failure" << std::endl;
            resetCount();
            return;
        }

	    std::istringstream stream(classification);
        std::string single_label;

        Node* current = root;
        Node* previous = current;

        bool update = false;
        bool decrement = false;
	
        while(std::getline(stream,single_label,',')){
            bool found = false;

            for ( int i{0}; i < 15; i++ ) {
                if (  (current -> children[i] != nullptr) && (current -> children[i] -> label == single_label) ) {
                    current = current -> children[i];
                    found = true;
                }
            }
            if ( !found ) {
                std::cout << "failure" << std::endl;
                resetCount();
                return;
            }

            if ( children_empty(current) && (current -> label == single_label) ) {
                for ( int i{0}; i < 15; i++ ) {
                    if ( (previous -> children[i] != nullptr) && (previous -> children[i] -> label == single_label) ) {
                        previous -> children[i] = nullptr;
                        delete current;

                        if ( children_empty(previous) ) {
                            decrement = false;
                        }
                        else if ( !children_empty(previous) ) {
                            decrement = true;
                        }
                        update = true;
                    }
                }
            }
            previous = current;
        }

        // If we loose a leaf
        if ( decrement ) {
            itemcount--;
        }
        // If nothing changed (unable to delete)
        if ( !update ) {
            std::cout << "failure" << std::endl;
        }
        else if ( update ) {
            std::cout << "success" << std::endl;
        }
        resetCount();

    } catch (const illegal_exception&) {
        std::cout << "illegal argument" << std::endl;
    }
}

void Trie::resetCount(){
    if ( children_empty(root) ) {
        itemcount = 0;
        root = nullptr;
    }
}

void Trie::print() {
    if (root == nullptr || children_empty(root)) {
        std::cout << "trie is empty" << std::endl;
        return;
    }
    std::string result = "";
    print(root, "", &result);
    
    if (!result.empty() && result.back() == '_') {
        result.pop_back();
    }
    std::cout << result << std::endl;
}

void Trie::print(Node* current, std::string path, std::string* result) {
    if (current->terminal && children_empty(current)) {
        *result += path + "_";
    }
    for (int i{0}; i < 15; i++) {
        if (current -> children[i] != nullptr) {
            std::string newPath = path.empty() ? current -> children[i] -> label
                                               : path + "," + current -> children[i]->label;
            print(current -> children[i], newPath, result);
        }
    }
}

void Trie::empty() {
    if (root == nullptr || children_empty(root)) {
        std::cout << "empty 1" << std::endl;
    } else {
        std::cout << "empty 0" << std::endl;
    }
}

// Checks if each child in a Node are nullptr, and thus empty
bool Trie::children_empty(Node* node) {
    for (int i{0}; i < 15; i++) {
        if (node -> children[i] != nullptr) {
            return false;
        }
    }
    return true;
}

void Trie::clear() {
    clear(root);
    root = nullptr;
    itemcount = 0;
}

void Trie::clear(Node* current) {
    if (current == nullptr) {
        itemcount = 0;
        return;
    }
    for (int i = 0; i < 15; i++) {
        if (current -> children[i] != nullptr) {
            clear(current -> children[i]);
            current -> children[i] = nullptr;
        }
    }
    delete current;
}

void Trie::size() {
    std::cout << "number of classifications is " << itemcount << std::endl;
}
