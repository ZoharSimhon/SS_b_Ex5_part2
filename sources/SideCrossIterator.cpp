#include "MagicalContainer.hpp"
using namespace ariel;

// Default constructor
// MagicalContainer::SideCrossIterator::SideCrossIterator()
// {
// }

// constructor with container
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container)
    : Iterator(container, SideCross, container.first_), lastIt_(container.last_), counter_(0) {}

// constructor with container & iterator
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container, Node *iter)
    : Iterator(container, SideCross, iter), lastIt_(container.last_), counter_(container.size_) {}

// Copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator const &otherSCI)
    : Iterator(otherSCI.getContainer(), SideCross, otherSCI.getIt()),
      lastIt_(otherSCI.lastIt_), counter_(otherSCI.counter_) {}

// Assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator otherSCI)
{
    if (this->getType() != otherSCI.getType())
        throw runtime_error("Can't assign different iterators");

    if (this != &otherSCI)
    {
        if (&this->getContainer() != &otherSCI.getContainer())
            throw runtime_error("Can't assign iterators from different containers");

        this->setIt(otherSCI.getIt());
        this->counter_ = otherSCI.counter_;
        this->lastIt_ = otherSCI.lastIt_;
    }
    return *this;
}

// Move assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&otherSCI) noexcept
{
    if (&this->getContainer() == &otherSCI.getContainer())
        this->setIt(otherSCI.getIt());

    return *this;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &otherIt) const
{
    if (this->getType() != otherIt.getType())
        throw runtime_error("Can't compare different iterators");

    if (&this->getContainer() != &otherIt.getContainer())
        throw runtime_error("Can't compare iterators from different containers");

    if (this->counter_ > otherIt.counter_)
        return true;

    return false;
}

// Dereference operator (operator*)
int MagicalContainer::SideCrossIterator::operator*() const
{
    if (this->getIt() == nullptr)
    {
        throw runtime_error("Can't use dereference operator for nullptr operator");
    }
    if (this->counter_ % 2 == 0)
        return this->getIt()->getData();
    else
        return this->lastIt_->getData();
}

// Pre-increment operator (operator++)
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (this->getIt() == nullptr)
        throw runtime_error("out of range");

    // check if we have gone through all the elements
    if (this->counter_ == this->getContainer().size_ - 1)
    {
        this->setIt(nullptr);
        this->lastIt_ = nullptr;
        return *this;
    }

    // moving forward
    if (this->counter_ % 2 == 0)
        this->setIt(this->getIt()->getNext());
    // moving backword
    else
        this->lastIt_ = this->lastIt_->getPrev();
    // increament the counter by 1
    this->counter_++;
    return *this;
}

// begin(type): Returns the appropriate iterator pointing to the first element of the container
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
{
    return SideCrossIterator(this->getContainer());
}

// end(type): Returns the appropriate iterator pointing to the last element of the container.
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
{
    return SideCrossIterator(this->getContainer(), nullptr);
}
