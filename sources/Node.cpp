#include "Node.hpp"
using namespace ariel;

// constructor
Node::Node(int data)
    : data_(data), next_(nullptr), prev_(nullptr), nextPrime_(nullptr), prevPrime_(nullptr)
{
    this->isPrime_ = this->checkIsPrime();
}

// helper function
bool Node::checkIsPrime()
{
    if (this->data_ < 2)
        return false;
    for (int i = 2; i * i <= this->data_; i++)
    {
        if (this->data_ % i == 0)
            return false;
    }
    return true;
}

// getters
int Node::getData()
{
    return this->data_;
}
Node *Node::getNext()
{
    return this->next_;
}
Node *Node::getPrev()
{
    return this->prev_;
}
Node *Node::getNextPrime()
{
    return this->nextPrime_;
}
Node *Node::getPrevPrime()
{
    return this->prevPrime_;
}
bool Node::getIsPrime()
{
    return this->isPrime_;
}

// setters
void Node::setNext(Node *next)
{
    this->next_ = next;
}
void Node::setPrev(Node *prev)
{
    this->prev_ = prev;
}
void Node::setNextPrime(Node *nextPrime)
{
    this->nextPrime_ = nextPrime;
}
void Node::setPrevPrime(Node *prevPrime)
{
    this->prevPrime_ = prevPrime;
}

bool Node::operator==(const Node &other)
{
    return (this->data_ == other.data_);
}
