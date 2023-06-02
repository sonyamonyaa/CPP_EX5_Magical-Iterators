#include <vector>
#include <cstddef>

namespace ariel
{
    // TODO: add check if same container
    /**
     * Create a user-defined container class named "MagicalContainer" that can store integers representing mystical elements.
     * Implement necessary methods for adding elements,
     * removing elements,
     * retrieving the size of the container.
     * You can use a dynamic array or any other suitable data structure for internal storage.
     */
    class MagicalContainer
    {
    private:
        std::vector<int> elements;

    public:
        MagicalContainer();
        void addElement(int elem); // adds as a sorted
        void removeElement(int elem);
        size_t size() { return elements.size(); };
        ~MagicalContainer();

        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };
    /**
     * Each iterator should support the following operations:
     * Default constructor
     * Copy constructor
     * Destructor
     * Assignment operator
     * Equality comparison (operator==)
     * Inequality comparison (operator!=)
     * GT, LT comparison (operator>, operatorn<) all comparison operators only valid for iterators of the same type of order and should compair the location of the iterator in the container and not the element inside. Example bellow. Using operators on iterators of differant type or differant containers should throw an examtion.
     * Dereference operator (operator*)
     * Pre-increment operator (operator++)
     * begin(type): Returns the appropriate iterator (ascending, cross, or prime) pointing to the first element of the container based on the specified type.
     * end(type): Returns the appropriate iterator (ascending, cross, or prime) pointing one position past the last element of the container based on the specified type.
     */
    class MagicalContainer::AscendingIterator
    {
    private:
        MagicalContainer &container;
        size_t currentIndex;

    public:
        AscendingIterator(MagicalContainer &container, size_t currentIndex = 0)
            : container(container), currentIndex(currentIndex) {}

        AscendingIterator begin() { return AscendingIterator(container, 0); };
        AscendingIterator end() { return AscendingIterator(container, container.size()); };

        // Overload the dereference operator
        int operator*() const
        {
            return container.elements[currentIndex];
        }

        // Overload the prefix increment operator
        AscendingIterator &operator++()
        {
            ++currentIndex;
            return *this;
        }

        // Overload the equality operator
        bool operator==(const AscendingIterator &other) const
        {
            return currentIndex == other.currentIndex;
        }

        // Overload the inequality operator
        bool operator!=(const AscendingIterator &other) const
        {
            return !(*this == other);
        }

        bool operator<(const AscendingIterator &other) const
        {
            return false;
        }

        bool operator>(const AscendingIterator &other) const
        {
            return false;
        }
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        MagicalContainer &container;
        size_t currentIndex;

    public:
        SideCrossIterator(MagicalContainer &container, size_t currentIndex = 0)
            : container(container), currentIndex(currentIndex) {}

        SideCrossIterator begin() { return SideCrossIterator(container, 0); };
        SideCrossIterator end() { return SideCrossIterator(container, container.size()); };
        // Overload the dereference operator
        int operator*() const
        {
            return container.elements[currentIndex];
        }
        // Overload the prefix increment operator
        SideCrossIterator &operator++()
        {
            ++currentIndex;
            return *this;
        }

        // Overload the equality operator
        bool operator==(const SideCrossIterator &other) const
        {
            return currentIndex == other.currentIndex;
        }

        // Overload the inequality operator
        bool operator!=(const SideCrossIterator &other) const
        {
            return !(*this == other);
        }
    };

    class MagicalContainer::PrimeIterator
    {
    private:
        MagicalContainer &container;
        size_t currentIndex;

    public:
        PrimeIterator(MagicalContainer &container, size_t currentIndex = 0)
            : container(container), currentIndex(currentIndex) {}
        
        PrimeIterator begin() { return PrimeIterator(container, 0); };
        PrimeIterator end() { return PrimeIterator(container, container.size()); };
        
        int operator*() const
        {
            return container.elements[currentIndex];
        }
        // Overload the prefix increment operator
        PrimeIterator &operator++()
        {
            ++currentIndex;
            return *this;
        }

        // Overload the equality operator
        bool operator==(const PrimeIterator &other) const
        {
            return currentIndex == other.currentIndex;
        }

        // Overload the inequality operator
        bool operator!=(const PrimeIterator &other) const
        {
            return !(*this == other);
        }
    };

}