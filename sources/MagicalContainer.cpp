#include "MagicalContainer.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace ariel
{
    bool isPrime(int number)
    {
        if (number < 2)
            return false;
        for (int i = 2; i <= std::sqrt(number); ++i)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    bool compareIntPtrs(const int *a, const int *b)
    {
        return *a < *b; // Compare the pointed values
    }

    void MagicalContainer::addElement(int elem)
    {
        // add as sorted
        auto it = std::lower_bound(elements.begin(), elements.end(), elem);
        elements.insert(it, elem);

        if (isPrime(elem)) // save primes in ptr container
        {
            int *elemPtr = new int(elem); // would get garbage value otherwise
            if (primes.empty())
                primes.push_back(elemPtr);
            else
            {
                auto prime_it = std::lower_bound(primes.begin(), primes.end(), elemPtr, compareIntPtrs);
                primes.insert(prime_it, elemPtr);
            }
        }
    }

    void MagicalContainer::removeElement(int elem)
    {
        auto it = std::find(elements.begin(), elements.end(), elem);
        if (it != elements.end())
        {
            elements.erase(it);
        }
        else
        {
            throw std::runtime_error("element doesn't exist");
        }
        // erase in primes
        auto p_it = std::find(primes.begin(), primes.end(), &elem);
        if (p_it != primes.end())
        {
            primes.erase(p_it);
        }
        // elements.erase(elem);
    }
    MagicalContainer::~MagicalContainer()
    {
        for (auto p : primes)
        {
            delete p;
        }
    }
    // -----------------------------Iterators----------------------------------------

    void MagicalContainer::BasicIterator::checkTypes(const BasicIterator &other) const
    {
        if (this->type != other.type)
        {
            throw std::runtime_error("operation on different types");
        }
    }

    // MagicalContainer::BasicIterator &MagicalContainer::BasicIterator::operator=(const BasicIterator &other)
    // {
    //     checkTypes(other);
    //     if (this != &other)
    //     {
    //         container = other.container;
    //         index = other.index;
    //     }
    //     return *this;
    // }

    void MagicalContainer::BasicIterator::checkContainers(const BasicIterator &other) const
    {
        if (this->container != other.container)
        {
            throw std::runtime_error("operation on different containers");
        }
    }

    bool MagicalContainer::BasicIterator::operator==(const BasicIterator &other) const
    {
        checkTypes(other);
        checkContainers(other);
        return index == other.index;
        ;
    }

    bool MagicalContainer::BasicIterator::operator!=(const BasicIterator &other) const
    {
        return !(*this == other);
    }
    bool MagicalContainer::BasicIterator::operator>(const BasicIterator &other) const
    {
        checkTypes(other);
        checkContainers(other);
        return index > other.index;
        ;
    }
    bool MagicalContainer::BasicIterator::operator<(const BasicIterator &other) const
    {
        checkTypes(other);
        checkContainers(other);
        return index < other.index;
    }

    // -----------------------------Ascending----------------------------------------
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        checkContainers(other);
        if (this != &other)
        {
            // container = other.container;
            index = other.index;
        }
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (index == container->size())
        {
            throw std::runtime_error("reached the end");
        }
        ++index;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        return container->elements.at(index);
    }
    // ----------------------------- SideCross----------------------------------------
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        checkContainers(other);
        if (this != &other)
        {
            // container = other.container;
            index = other.index;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (index == container->size())
        {
            throw std::runtime_error("reached the end");
        }
        ++index;
        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        auto pos = (index % 2 == 0) ? (index / 2) : container->elements.size() - (index / 2) - 1;
        return container->elements.at(pos);
    }

    // ----------------------------- Prime----------------------------------------
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        checkContainers(other);
        if (this != &other)
        {
            // container = other.container;
            index = other.index;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (index == container->primes.size())
        {
            throw std::runtime_error("reached the end");
        }
        ++index;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        auto ptr = container->primes.at(index);
        int value = *ptr; // derefrence the pointer
        return value;
    }
}