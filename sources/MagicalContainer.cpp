#include "MagicalContainer.hpp"

namespace ariel
{
    MagicalContainer::MagicalContainer()
    {
    }

    void MagicalContainer::addElement(int elem)
    {
    }

    void MagicalContainer::removeElement(int elem)
    {
    }

    MagicalContainer::~MagicalContainer()
    {
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        // TODO: insert return statement here
                    if (this != &other)
            {
                container = other.container;
                currentIndex = other.currentIndex;
            }
            return *this;
    }

}