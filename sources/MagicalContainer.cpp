#include "MagicalContainer.hpp"
using namespace ariel;

MagicalContainer::MagicalContainer()
    : first_(nullptr), last_(nullptr), firstPrime_(nullptr), size_(0) {}

// helper functions
void MagicalContainer::insertToPrimes(Node *prevPrime, Node *newNode)
{
    // add the number to the first value
    if (prevPrime == nullptr)
    {
        // update the next to the current first prime
        newNode->setNextPrime(this->firstPrime_);
        // change the next Node
        if (this->firstPrime_ != nullptr)
            firstPrime_->setPrevPrime(newNode);
        // update the first
        this->firstPrime_ = newNode;
    }
    // add the number in the middle
    else
    {
        // define the next prime
        Node *nextPrime = prevPrime->getNextPrime();
        // update the prev & next of the new Node
        newNode->setNextPrime(nextPrime);
        newNode->setPrevPrime(prevPrime);
        // change the prev Node
        prevPrime->setNextPrime(newNode);
        // change the next Node
        if (nextPrime != nullptr)
            nextPrime->setPrevPrime(newNode);
        // update the last prime
        // else
        // this->lastPrime_ = newNode;
    }
}
void MagicalContainer::insertToNumbers(Node *prev, Node *newNode)
{
    // add the number to the first value
    if (prev == nullptr)
    {
        // update the next to the current first prime
        newNode->setNext(this->first_);
        // change the next Node
        if (this->first_ != nullptr)
            first_->setPrev(newNode);
        // update the first
        this->first_ = newNode;
    }
    // add the number in the middle
    else
    {
        // define the next prime
        Node *next = prev->getNext();
        // update the prev & next of the new Node
        newNode->setNext(next);
        newNode->setPrev(prev);
        // change the prev Node
        prev->setNext(newNode);
        // change the next Node
        if (next != nullptr)
            next->setPrev(newNode);
        // update the last Node
        else
            this->last_ = newNode;
    }
}
void MagicalContainer::addPrimeNumber(Node *newNode)
{
    Node *prevPrime = nullptr;
    Node *prev = nullptr;

    for (Node *iter = this->first_; iter != nullptr; iter = iter->getNext())
    {
        // found the place to insert
        if (iter->getData() >= newNode->getData())
        {
            insertToPrimes(prevPrime, newNode);
            insertToNumbers(prev, newNode);
            return;
        }

        // update the last prime
        if (iter->getIsPrime())
            prevPrime = iter;
        // update the last Node
        prev = iter;
    }

    insertToPrimes(prevPrime, newNode);
    insertToNumbers(prev, newNode);
}
void MagicalContainer::addCompositeNumber(Node *newNode)
{
    Node *prev = nullptr;
    for (Node *iter = this->first_; iter != nullptr; iter = iter->getNext())
    {
        // found the place to insert
        if (iter->getData() >= newNode->getData())
        {
            insertToNumbers(prev, newNode);
            return;
        }

        // update the last Node
        prev = iter;
    }
    insertToNumbers(prev, newNode);
}
void MagicalContainer::removeFromPrimes(Node *deletedNode)
{
    Node *prevPrime = deletedNode->getPrevPrime();
    Node *nextPrime = deletedNode->getNextPrime();
    // update the prev
    if (prevPrime != nullptr)
    {
        prevPrime->setNextPrime(nextPrime);
    }
    // update the next
    if (nextPrime != nullptr)
    {
        nextPrime->setPrevPrime(prevPrime);
    }
    // update the head
    if (this->firstPrime_ == deletedNode)
    {
        this->firstPrime_ = nextPrime;
    }
}
void MagicalContainer::removeFromNumbers(Node *deletedNode)
{
    Node *prev = deletedNode->getPrev();
    Node *next = deletedNode->getNext();
    // update the prev
    if (prev != nullptr)
    {
        prev->setNext(next);
    }
    // update the next
    if (next != nullptr)
    {
        next->setPrev(prev);
    }
    // update the head
    if (this->first_ == deletedNode)
    {
        this->first_ = next;
    }
    // update the teal
    if (this->last_ == deletedNode)
    {
        this->last_ = prev;
    }
}

void MagicalContainer::addElement(int number)
{
    // create new Node
    Node *newNode = new Node(number);
    if (newNode->getIsPrime())
        addPrimeNumber(newNode);
    else
        addCompositeNumber(newNode);
    this->size_++;
}

void MagicalContainer::removeElement(int number)
{
    if (this->size_ == 0)
    {
        throw runtime_error("Can't remove from an empty list");
    }

    for (Node *iter = this->first_; iter != nullptr; iter = iter->getNext())
    {
        if (iter->getData() == number)
        {
            // change the pointers
            if (iter->getIsPrime())
            {
                removeFromPrimes(iter);
            }

            // remove from the list
            removeFromNumbers(iter);
            // free the deleted Node
            delete iter;

            this->size_--;
            return;
        }
    }
    // didn't found the number
    throw runtime_error("Can't remove a non-exist element");
}

int MagicalContainer::size()
{
    return this->size_;
}

// getters
Node *MagicalContainer::getBegin() const
{
    return this->first_;
}
Node *MagicalContainer::getEnd() const
{
    return this->last_;
}
Node *MagicalContainer::getFirstPrime() const
{
    return this->firstPrime_;
}

void MagicalContainer::printMagicalContainer()
{
    cout << "elements: ";
    for (Node *iter = this->first_; iter != nullptr; iter = iter->getNext())
    {
        cout << iter->getData() << ",";
    }
    cout << "NULL" << endl;
}

void MagicalContainer::printPrimes()
{
    cout << "primes: ";
    for (Node *iter = this->first_; iter != nullptr; iter = iter->getNextPrime())
    {
        cout << iter->getData() << ", ";
    }
    cout << "NULL" << endl;
}

// 5 related nethods
MagicalContainer::~MagicalContainer()
{
    Node *prev = nullptr;
    bool first = true;
    for (Node *iter = this->first_; iter != nullptr; iter = iter->getNext())
    {
        if (!first)
            delete prev;
        else
            first = false;
        prev = iter;
    }
    delete prev;
}
MagicalContainer::MagicalContainer(const MagicalContainer &other)
    : first_(nullptr), last_(nullptr), firstPrime_(nullptr), size_(0)
{
    // Copy all the element
    for (Node *iter = other.first_; iter != nullptr; iter = iter->getNext())
    {
        this->addElement(iter->getData());
    }
}
MagicalContainer::MagicalContainer(MagicalContainer &&other) noexcept
    : first_(other.first_), last_(other.last_), firstPrime_(other.firstPrime_), size_(other.size_) {}
MagicalContainer &MagicalContainer::operator=(MagicalContainer other)
{
    // first, intilize the data members
    this->first_ = nullptr;
    this->firstPrime_ = nullptr;
    this->last_ = nullptr;
    this->size_ = 0;

    // Copy all the element
    for (Node *iter = other.first_; iter != nullptr; iter = iter->getNext())
    {
        this->addElement(iter->getData());
    }

    return *this;
}
MagicalContainer &MagicalContainer::operator=(MagicalContainer &&other) noexcept
{
    this->first_ = other.first_;
    this->firstPrime_ = other.firstPrime_;
    this->last_ = other.last_;
    this->size_ = other.size_;

    return *this;
}