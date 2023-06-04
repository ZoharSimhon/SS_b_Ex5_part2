#pragma once
#include <iostream>

using namespace std;

namespace ariel
{
    class Node
    {
    private:
        int data_;
        Node *next_;
        Node *prev_;
        Node *nextPrime_;
        Node *prevPrime_;
        bool isPrime_;

        // helper functions
        bool checkIsPrime();

    public:
        // constructors
        // Node(int data, Node *nextPrime, Node *prevPrime);
        Node(int data);

        // getters
        int getData();
        Node *getNext();
        Node *getPrev();
        Node *getNextPrime();
        Node *getPrevPrime();
        bool getIsPrime();
        // setters
        void setNext(Node *next);
        void setPrev(Node *prev);
        void setNextPrime(Node *nextPrime);
        void setPrevPrime(Node *prevPrime);

        // ~Node(){}

        bool operator==(const Node &other);
    };
}