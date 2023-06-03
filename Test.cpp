#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>

using namespace ariel;
TEST_SUITE("Test 1 - Basic Container Functions")
{
    TEST_CASE("1.1 - element addition")
    {
        MagicalContainer container;
        SUBCASE("1.1.1 - adding a single element")
        {
            container.addElement(1);
            CHECK(container.size() == 1);
        }

        SUBCASE("1.1.2 - adding multiple elements")
        {
            container.addElement(1);
            container.addElement(2);
            container.addElement(3);
            CHECK(container.size() == 3);
        }
    }
    TEST_CASE("1.2 - remove element")
    {
        MagicalContainer container;
        SUBCASE("1.2.1 - removing existing element")
        {
            container.addElement(1);
            container.addElement(2);
            container.addElement(3);
            CHECK_NOTHROW(container.removeElement(2));
            CHECK(container.size() == 2);
        }

        SUBCASE("1.2.2 - removing non-existant element")
        {
            container.addElement(1);
            container.addElement(2);
            container.addElement(3);
            CHECK_THROWS(container.removeElement(4));
        }
    }
}

TEST_SUITE("Test 2 - Ascending Iterator")
{

    TEST_CASE("2.1 - iterate over elements")
    {
        SUBCASE("2.1.1 - sorted after unsorted addition")
        {
            MagicalContainer container;
            container.addElement(3);
            container.addElement(1);
            container.addElement(4);
            container.addElement(2);
            container.addElement(7);
            container.addElement(5);
            container.addElement(9);
            container.addElement(6);
            container.addElement(8);

            MagicalContainer::AscendingIterator ascIter(container);
            auto it = ascIter.begin();
            auto end = ascIter.end();

            CHECK(*it==1);
            ++it;
            CHECK(*it== 2);
            ++it;
            CHECK(*it== 3);
            ++it;
            CHECK(*it== 4);
            ++it;
            CHECK(*it== 5);
            ++it;
            CHECK(*it== 6);
            ++it;
            CHECK(*it== 7);
            ++it;
            CHECK(*it== 8);
            ++it;
            CHECK(*it== 9);
            ++it;
            CHECK(it==end);
        }
        SUBCASE("2.1.2 - empty container with ascending iterator")
        {
            MagicalContainer emptyContainer;
            MagicalContainer::AscendingIterator ascIter(emptyContainer);
            auto it = ascIter.begin();
            auto end = ascIter.end();
            CHECK_EQ(it, end);
            CHECK_THROWS(++it);
        }
        SUBCASE("2.1.3 - sorted with positive & negative numbers")
        {
            MagicalContainer container;

            container.addElement(-3);
            container.addElement(1);
            container.addElement(4);
            container.addElement(2);
            container.addElement(7);
            container.addElement(-5);
            container.addElement(9);
            container.addElement(-6);
            container.addElement(8);

            MagicalContainer::AscendingIterator ascIter(container);
            auto it = ascIter.begin();
            auto end = ascIter.end();

            CHECK_EQ(*it, -6);
            ++it;
            CHECK_EQ(*it, -5);
            ++it;
            CHECK_EQ(*it, -3);
            ++it;
            CHECK_EQ(*it, 1);
            ++it;
            CHECK_EQ(*it, 2);
            ++it;
            CHECK_EQ(*it, 4);
            ++it;
            CHECK_EQ(*it, 6);
            ++it;
            CHECK_EQ(*it, 8);
            ++it;
            CHECK_EQ(*it, 9);
            ++it;
            CHECK_EQ(it, end);
        }
    }

    TEST_CASE("2.2 - Comparison")
    {
        MagicalContainer container;
        for (int i = 0; i < 5; i++)
        {
            container.addElement(i);
        }

        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();

        auto copyIt = it;
        CHECK(copyIt == it);
        CHECK_FALSE(copyIt != it);

        ++it;
        CHECK(it > ascIter.begin());
        CHECK(ascIter.begin() < it);

        // copy hasn't increased
        CHECK(copyIt == ascIter.begin());
        CHECK_FALSE(copyIt < ascIter.begin());
        CHECK_FALSE(ascIter.begin() > copyIt);

        // increase copy till end
        while (copyIt != ascIter.end())
        {
            ++copyIt;
        }
        CHECK(copyIt != it);
        CHECK(copyIt == ascIter.end());
        CHECK_FALSE(copyIt == it);

        CHECK(copyIt > it);
        CHECK(it < copyIt);
    }
}

TEST_SUITE("Test 3 - Side-Cross Iterator")
{
    TEST_CASE("2.1 - iterate over elements")
    {
        SUBCASE("3.1.1 - basic cross iteration")
        {
            MagicalContainer container;
            for (int i = 1; i < 10; i++)
            {
                container.addElement(i);
            }
            MagicalContainer::SideCrossIterator crossIter(container);
            auto it = crossIter.begin();
            auto end = crossIter.end();

            CHECK_EQ(*it, 1);
            ++it;
            CHECK_EQ(*it, 9);
            ++it;
            CHECK_EQ(*it, 2);
            ++it;
            CHECK_EQ(*it, 8);
            ++it;
            CHECK_EQ(*it, 3);
            ++it;
            CHECK_EQ(*it, 7);
            ++it;
            CHECK_EQ(*it, 4);
            ++it;
            CHECK_EQ(*it, 6);
            ++it;
            CHECK_EQ(*it, 5);
            ++it;
            CHECK_EQ(it, end);
        }
        SUBCASE("3.1.2 - empty container with side-cross iterator")
        {
            MagicalContainer emptyContainer;
            MagicalContainer::SideCrossIterator crossIter(emptyContainer);
            auto it = crossIter.begin();
            auto end = crossIter.end();
            CHECK_EQ(it, end);
            CHECK_THROWS(++it);
        }
        SUBCASE("3.1.3 - negative/positive side-cross")
        {
            MagicalContainer container;
            for (int i = -4; i <= 4; i++)
            {
                container.addElement(i);
            }
            MagicalContainer::SideCrossIterator crossIter(container);
            auto it = crossIter.begin();
            auto end = crossIter.end();

            CHECK_EQ(*it, -4);
            ++it;
            CHECK_EQ(*it, 4);
            ++it;
            CHECK_EQ(*it, -3);
            ++it;
            CHECK_EQ(*it, 3);
            ++it;
            CHECK_EQ(*it, -2);
            ++it;
            CHECK_EQ(*it, 2);
            ++it;
            CHECK_EQ(*it, -1);
            ++it;
            CHECK_EQ(*it, 1);
            ++it;
            CHECK_EQ(*it, 0);
            CHECK_EQ(it, end);
        }
    }

    TEST_CASE("3.2 - Comparison")
    {
        SUBCASE("3.2.1 - same behaviour as all other iterators")
        {
            MagicalContainer container;
            for (int i = 0; i < 5; i++)
            {
                container.addElement(i);
            }

            MagicalContainer::SideCrossIterator crossIter(container);
            auto it = crossIter.begin();
            auto end = crossIter.end();

            auto copyIt = it;
            CHECK(copyIt == it);
            CHECK_FALSE(copyIt != it);

            ++it;
            CHECK(it > crossIter.begin());
            CHECK(crossIter.begin() < it);

            // copy hasn't increased
            CHECK(copyIt == crossIter.begin());
            CHECK_FALSE(copyIt < crossIter.begin());
            CHECK_FALSE(crossIter.begin() > copyIt);

            // increase copy till end
            while (copyIt != crossIter.end())
            {
                ++copyIt;
            }
            CHECK(copyIt != it);
            CHECK(copyIt == crossIter.end());
            CHECK_FALSE(copyIt == it);
            CHECK(copyIt > it);
            CHECK(it < copyIt);
        }
    }
}

TEST_SUITE("Test 4 - Prime Iterator")
{
    TEST_CASE("4.1 - iterate over elements")
    {
        SUBCASE("4.1.1 - basic prime iteration")
        {
            MagicalContainer container;
            for (int i = 1; i < 10; i++)
            {
                container.addElement(i);
            }
            MagicalContainer::PrimeIterator primeIter(container);
            auto it = primeIter.begin();
            auto end = primeIter.end();

            CHECK_EQ(*it, 2);
            ++it;
            CHECK_EQ(*it, 3);
            ++it;
            CHECK_EQ(*it, 5);
            ++it;
            CHECK_EQ(*it, 7);
            ++it;
            CHECK_EQ(*it, 9);
            ++it;
            CHECK_EQ(it, end);
        }
        SUBCASE("4.1.2 - empty container with prime iterator")
        {
            MagicalContainer emptyContainer;
            MagicalContainer::PrimeIterator primeIter(emptyContainer);
            auto it = primeIter.begin();
            auto end = primeIter.end();
            CHECK_EQ(it, end);
            CHECK_THROWS(++it);
        }
        SUBCASE("4.1.3 - no primes")
        {
            MagicalContainer noPrimeContainer;
            noPrimeContainer.addElement(4);
            noPrimeContainer.addElement(6);
            noPrimeContainer.addElement(8);
            MagicalContainer::PrimeIterator primeIter(noPrimeContainer);
            auto it = primeIter.begin();
            auto end = primeIter.end();

            CHECK(it == end);
        }
    }

    TEST_CASE("4.2 - Comparison")
    {
        MagicalContainer container;
        for (int i = 0; i <= 5; i++)
        {
            container.addElement(i);
        }

        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();

        auto copyIt = it;
        CHECK(copyIt == it);
        CHECK_FALSE(copyIt != it);

        ++it;
        CHECK(it > primeIter.begin());
        CHECK(primeIter.begin() < it);

        // copy hasn't increased
        CHECK(copyIt == primeIter.begin());
        CHECK_FALSE(copyIt < primeIter.begin());
        CHECK_FALSE(primeIter.begin() > copyIt);

        // increase copy till end
        while (copyIt != primeIter.end())
        {
            ++copyIt;
        }
        CHECK(copyIt != it);
        CHECK(copyIt == primeIter.end());
        CHECK_FALSE(copyIt == it);

        CHECK(copyIt > it);
        CHECK(it < copyIt);
    }
}
