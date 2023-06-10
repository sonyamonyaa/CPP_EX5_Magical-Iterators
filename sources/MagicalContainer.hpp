#include <vector>
#include <cstddef>

namespace ariel
{
    enum class iterTypes : char
    {
        ascend = 'a',
        cross = 'c',
        prime = 'p'
    };

    class MagicalContainer
    {
    private:
        std::vector<int> elements;
        std::vector<int *> primes; // holds the pointers for prime nums in the sorted container (=elements)
        class BasicIterator;

    public:
        void addElement(int elem); // adds as a sorted
        void removeElement(int elem);
        size_t size() { return elements.size(); };

        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;

        MagicalContainer() = default;
        ~MagicalContainer();
        MagicalContainer(const MagicalContainer &) = default;
        MagicalContainer &operator=(const MagicalContainer &) = default;
        MagicalContainer(MagicalContainer &&) noexcept = default;
        MagicalContainer &operator=(MagicalContainer &&) noexcept = default;
    };

    class MagicalContainer::BasicIterator
    {
    protected:
        MagicalContainer *container;
        size_t index;
        void checkContainers(const BasicIterator &other) const;
    private:
        iterTypes type;
        void checkTypes(const BasicIterator &other) const;

    public:
        BasicIterator(MagicalContainer &container, size_t index = 0, iterTypes type = iterTypes::ascend)
            : container(&container), index(index), type(type) {}
        BasicIterator(const BasicIterator &other) : container(other.container), index(other.index) {}
        ~BasicIterator() = default;
        BasicIterator(BasicIterator &&other) noexcept = default;
        BasicIterator &operator=(BasicIterator &&other) noexcept = default;
        // BasicIterator &operator=(const BasicIterator &other);

        bool operator==(const BasicIterator &other) const;
        bool operator!=(const BasicIterator &other) const;
        bool operator>(const BasicIterator &other) const;
        bool operator<(const BasicIterator &other) const;
    };

    class MagicalContainer::AscendingIterator : public MagicalContainer::BasicIterator
    {
    public:
        AscendingIterator(MagicalContainer &container, size_t index = 0)
            : BasicIterator(container, index, iterTypes::ascend) {}

        AscendingIterator(const AscendingIterator &other) : BasicIterator(other) {}
        ~AscendingIterator() {}
        AscendingIterator &operator=(const AscendingIterator &other);
        AscendingIterator begin() { return AscendingIterator(*container, 0); }
        AscendingIterator end() { return AscendingIterator(*container, container->size()); }

        AscendingIterator &operator++();
        int operator*() const;

        AscendingIterator(AscendingIterator &&) noexcept = default;
        AscendingIterator &operator=(AscendingIterator &&) noexcept = default;
    };

    class MagicalContainer::SideCrossIterator : public MagicalContainer::BasicIterator
    {
    public:
        SideCrossIterator(MagicalContainer &container, size_t index = 0)
            : BasicIterator(container, index, iterTypes::cross) {}

        SideCrossIterator(const SideCrossIterator &other) : BasicIterator(other) {}
        ~SideCrossIterator() {}
        SideCrossIterator &operator=(const SideCrossIterator &other);
        SideCrossIterator begin() { return SideCrossIterator(*container, 0); }
        SideCrossIterator end() { return SideCrossIterator(*container, container->size()); }

        SideCrossIterator &operator++();
        int operator*() const;

        SideCrossIterator(SideCrossIterator &&) noexcept = default;
        SideCrossIterator &operator=(SideCrossIterator &&) noexcept = default;
    };

    class MagicalContainer::PrimeIterator : public MagicalContainer::BasicIterator
    {
    public:
        PrimeIterator(MagicalContainer &container, size_t index = 0)
            : BasicIterator(container, index, iterTypes::prime) {}
        PrimeIterator(const PrimeIterator &other) : BasicIterator(other) {}
        ~PrimeIterator() {}
        PrimeIterator &operator=(const PrimeIterator &other);
        PrimeIterator begin() { return PrimeIterator(*container, 0); }
        PrimeIterator end() { return PrimeIterator(*container, container->primes.size()); }

        PrimeIterator &operator++();
        int operator*() const;

        PrimeIterator(PrimeIterator &&) noexcept = default;
        PrimeIterator &operator=(PrimeIterator &&) noexcept = default;
    };
}  // namespace ariel
