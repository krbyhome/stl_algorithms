#include "../lib/STLalgo.h"

#include <gtest/gtest.h>
#include <list>

bool sorted(int lhs, int rhs) {
    return lhs < rhs;
}

bool is_even(int num) {
    return (num + 1) % 2;
}

bool same_parity(int lhs, int rhs) {
    return (lhs % 2) == (rhs % 2);
}

TEST(STLalgoTestSuit, IsSortedTest) {
std::vector<int> v = {1, 2, 3, 4, 5};
std::vector<int> unsorted = {5, 2, 3, 4, 5};

ASSERT_EQ(stl_algo::is_sorted(v.begin(), v.end(), sorted), true);
ASSERT_EQ(stl_algo::is_sorted(unsorted.begin(), unsorted.end(), sorted), false);
}

TEST(STLalgoTestSuit, AllOf) {
std::vector<int> even = {2, 4, 6, 8, 10};
ASSERT_EQ(stl_algo::all_of(even.begin(), even.end(), is_even), 1);
}

TEST(STLalgoTestSuit, AnyOf) {
std::vector<int> one_even = {1, 2, 5, 7, 9};
ASSERT_EQ(stl_algo::any_of(one_even.begin(), one_even.end(), is_even), 1);
}

TEST(STLalgoTestSuit, OneOf) {
std::vector<int> one_even = {1, 2, 5, 7, 9};

ASSERT_EQ(stl_algo::one_of(one_even.begin(), one_even.end(), is_even), 1);
}

TEST(STLalgoTestSuit, NoneOf) {
std::vector<int> no_even = {1, 3, 5, 7, 9};

ASSERT_EQ(none_of(no_even.begin(), no_even.end(), is_even), 1);
}

TEST(STLalgoTestSuit, IsPartitioned) {
std::vector<int> partitioned = {2, 4, 6, 7, 9, 11};
ASSERT_EQ(is_partitioned(partitioned.begin(), partitioned.end(), is_even), 1);
}

TEST(STLalgoTestSuit, FindNot) {
std::vector<int> fnot = {1, 1, 1, 2, 1};
ASSERT_EQ(*stl_algo::find_not(fnot.begin(), fnot.end(), 1), 2);
}

TEST(STLalgoTestSuit, FindBackward) {
std::vector<int> fback = {1, 1, 1, 2, 1, 2, 1};

ASSERT_EQ(*stl_algo::find_backward(fback.begin(), fback.end(), 2), 2);
}

TEST(STLalgoTestSuit, IsPalik) {
std::vector<int> palik = {1, 2, 3, 4, 5};

ASSERT_EQ(stl_algo::is_palindrome(palik.begin(), palik.end(), same_parity), 1);
}


TEST(STLalgoTestSuit, XRANGETEST) {

auto x = xrange(1, 10, 1);
std::vector<int> xv{x.begin(), x.end()};
std::vector<int> prototype = {1, 2, 3, 4, 5, 6, 7, 8, 9};

size_t n = 0;
for (auto i = xv.begin(); i < xv.end(); ++i, ++n) {
    ASSERT_EQ(*i, prototype[n]);
}

}

TEST(STLalgoTestSuit, ZIPTest) {
    std::list l = {1, 2, 3, 4, 5};
    std::vector p = {'a', 'b', 'c', 'd'};

    std::vector<std::pair<int, char>> v = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}};

    size_t n = 0;
    for(auto value : zip(l, p)) {
    ASSERT_EQ(value, v[n]);
    n++;
    }
}
