#include "MagicalContainer.hpp"

using namespace ariel;

// constructor with container
MagicalContainer::Iterator::Iterator(const MagicalContainer &container, int type, Node *iter)
    : container_(container), type_(type), it_(iter) {}

// Dereference operator (operator*)
int MagicalContainer::Iterator::operator*() const
{
    if (this->it_ == nullptr)
    {
        throw runtime_error("Can't use dereference operator for nullptr operator");
    }
    return this->it_->getData();
}
// Equality comparison(operator==)
bool MagicalContainer::Iterator::operator==(const Iterator &otherIt) const
{
    if (this->type_ != otherIt.type_)
        throw runtime_error("Can't compare different iterators");

    if (&this->container_ != &otherIt.container_)
        throw runtime_error("Can't compare iterators from different containers");

    if (this->it_ == otherIt.it_)
        return true;

    return false;
}
// Inequality comparison(operator!=)
bool MagicalContainer::Iterator::operator!=(const Iterator &otherIt) const
{
    return !(*this == otherIt);
}
//  GT, LT comparison (operator>, operatorn<)
bool MagicalContainer::Iterator::operator>(const Iterator &otherIt) const
{
    if (this->type_ != otherIt.type_)
        throw runtime_error("Can't compare different iterators");

    if (&this->container_ != &otherIt.container_)
        throw runtime_error("Can't compare iterators from different containers");

    if (this->it_ == nullptr && otherIt.it_ == nullptr)
        return false;

    if (this->it_->getData() > otherIt.it_->getData())
        return true;

    return false;
}
bool MagicalContainer::Iterator::operator<(const Iterator &otherIt) const
{

    if (this->it_ == nullptr && otherIt.it_ == nullptr)
        return false;

    return !(*this > otherIt || *this == otherIt);
}

// getters
Node *MagicalContainer::Iterator::getIt() const
{
    return this->it_;
}
const MagicalContainer &MagicalContainer::Iterator::getContainer() const
{
    return this->container_;
}
int MagicalContainer::Iterator::getType() const
{
    return this->type_;
}

// setters
void MagicalContainer::Iterator::setIt(Node *iter)
{
    this->it_ = iter;
}

// 5 related nethods
MagicalContainer::Iterator::Iterator(const Iterator &other)
    : container_(other.container_), type_(other.type_), it_(other.it_) {}
MagicalContainer::Iterator::Iterator(Iterator &&other) noexcept
    : container_(other.container_), type_(other.type_), it_(other.it_){}
    
MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(const Iterator &other)
{
    if (this->type_ != other.type_)
        throw runtime_error("Can't assign different iterators");
    if (&this->container_ != &other.container_)
        throw runtime_error("Can't assign iterators from different containers");

    this->it_ = other.it_;
    return *this;
}
MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(Iterator &&other) noexcept
{
    if (this->type_ != other.type_)
        return *this;
    if (&this->container_ != &other.container_)
        return *this;

    this->it_ = other.it_;
    return *this;
}