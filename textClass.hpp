//Author : Ruben Rehal
//Date : November 18, 2024
//Hierarchical Text Classification


#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include <string>

class illegal_exception : public std::exception {
public:
    // Override the what() function to provide a custom error message
    virtual const char* what() const noexcept override {
        return "illegal argument";
    }
};

class Node {
    public:
        std::string label;
        bool terminal;
        Node* children[15];

        Node();
        ~Node();
};

class Trie {
    private:
        Node* root;
        int itemcount;

        // Helper Functions
        bool place(std::string classification);
        bool children_empty(Node* node);
        void clear(Node* current);
        void resetCount();


    public:
        
        Trie();
        ~Trie();

        // Required Functions
        void load(std::string filename);
        void insert(std::string path);
        void classify(std::string targetLabel);
        void erase(std::string classification);
        void print();
        void print(Node* current, std::string path, std::string* result);
        void empty();
        void clear();
        void size();
};

#endif // TEXTCLASS_H
