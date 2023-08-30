#pragma once

#include <cinttypes>
#include <iterator>


namespace stl_algo {
    template<typename iter, typename predicate>
    bool all_of(iter iter_left, iter iter_right, predicate pred) {
        while (iter_left != iter_right) {
            if (!pred(*iter_left)) {
                return false;
            }
            ++iter_left;
        }

        return true;
    }

    template<typename iter, typename predicate>
    bool any_of(iter iter_left, iter iter_right, predicate pred) {
        while (iter_left != iter_right) {
            if (pred(*iter_left)) {
                return true;
            }
            ++iter_left;
        }

        return false;
    }

    template<typename iter, typename predicate>
    bool none_of(iter iter_left, iter iter_right, predicate pred) {
        while (iter_left != iter_right) {
            if (pred(*iter_left)) {
                return false;
            }
            ++iter_left;
        }

        return true;
    }

    template<typename iter, typename predicate>
    bool one_of(iter iter_left, iter iter_right, predicate pred) {
        bool one_fits;
        one_fits = false;
        while (iter_left != iter_right) {
            if (pred(*iter_left)) {
                if (one_fits) {
                    return false;
                } else {
                    one_fits = true;
                }
            }
            ++iter_left;
        }

        if (one_fits) {
            return true;
        } else {
            return false;
        }
    }

    template<typename iter, typename predicate>
    bool is_sorted(iter iter_left, iter iter_right, predicate pred) {
        --iter_right;
        while (iter_left != iter_right) {
            if (!pred(*iter_left, *(iter_left + 1))) {
                return false;
            }
            ++iter_left;
        }

        return true;
    }

    template<typename iter, typename predicate>
    bool is_partitioned(iter iter_left, iter iter_right, predicate pred) {
        while (iter_left != iter_right) {
            if (!pred(*iter_left)) {
                break;
            }
            ++iter_left;
        }

        while (iter_left != iter_right) {
            if (pred(*iter_left)) {
                return false;
            }
            ++iter_left;
        }

        return true;
    }

    template<typename iter, typename type>
    iter find_not(iter iter_left, iter iter_right, const type &value) {
        while (iter_left != iter_right) {
            if (*iter_left != value) {
                return iter_left;
            }
            ++iter_left;
        }

        return iter_right;
    }

    template<typename iter, typename type>
    iter find_backward(iter iter_left, iter iter_right, const type &value) {
        iter end = iter_right;
        --iter_right;
        while (iter_right >= iter_left) {
            if (*iter_right == value) {
                return iter_right;
            }
            --iter_right;
        }

        return end;
    }

    template<typename iter, typename predicate>
    bool is_palindrome(iter iter_left, iter iter_right, predicate pred) {
        --iter_right;
        while (iter_left < iter_right) {
            if (!pred(*iter_left, *iter_right)) {
                return false;
            }
            ++iter_left;
            --iter_right;
        }

        return true;
    }
};

template<typename T>
class xrange {
    private:
        T first_;
        T last_;
        T step_;
    public:
        class iterator_xrange;

        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using const_reference = const T&;
        using iterator = iterator_xrange;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;

        xrange(T first, T last) : first_(first), last_(last), step_(1) {};

        xrange(T first, T last, T step) : first_(first), last_(last), step_(step) {};

        xrange(T last) : first_(0), last_(last), step_(1) {};

        class iterator_xrange {
        public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using const_reference = const T&;
            using iterator = iterator_xrange;
            using difference_type = std::ptrdiff_t;
            using size_type = size_t;
            using iterator_category = std::input_iterator_tag;

            explicit iterator_xrange(T value, T step) {
                value_ = value;
                step_ = step;
            }

            iterator_xrange& operator++() {
                value_ += step_;

                return *this;
            }

            bool operator!=(const iterator_xrange& rhs) {
                return value_ < rhs.value_;
            }

            value_type operator*() {
                return value_;
            }

            iterator& operator->() {
                return *this;
            }

        private:
            T value_;
            T step_;
        };

        iterator begin() {
            return iterator(first_, step_);
        }

        iterator end() {
            return iterator(last_, step_);
        }
};

template<typename container1, typename container2>
class zip {
    private:
        container1& container1_link;
        container2& container2_link;

    public:
        class iterator_zip;
        using value_type_container1 = typename container1::value_type;
        using value_type_container2 = typename container2::value_type;
        using value_type = std::pair<value_type_container1, value_type_container2>;
        using reference = value_type&;
        using pointer = value_type*;
        using const_reference = const value_type&;
        using iterator = iterator_zip;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;

        zip(container1& first_container, container2& second_container) :
        container1_link(first_container), container2_link(second_container) {};

        class iterator_zip{
            public:
            using value_type_container1 = typename container1::value_type;
            using value_type_container2 = typename container2::value_type;
            using value_type = std::pair<value_type_container1, value_type_container2>;
            using reference = value_type&;
            using pointer = value_type*;
            using iterator = iterator_zip;
            using difference_type = std::ptrdiff_t;
            using size_type = size_t;
            using iterator_category = std::input_iterator_tag;
            using container1_iterator = typename container1::iterator;
            using container2_iterator = typename container2::iterator;

            iterator_zip(container1_iterator iterator1, container2_iterator iterator2) :
            iter1(iterator1), iter2(iterator2) {};

            iterator& operator++() {
                ++iter1;
                ++iter2;

                return *this;
            }

            bool operator!=(const iterator& rhs) {
                return (iter1 != rhs.iter1) && (iter2 != rhs.iter2);
            }

            value_type operator*() {
                return std::make_pair(*iter1, *iter2);
            }

            iterator& operator->() {
                return *this;
            }

            private:
                container1_iterator iter1;
                container2_iterator iter2;
        };

        iterator begin() {
            return iterator_zip(container1_link.begin(), container2_link.begin());
        }

        iterator end() {
            return iterator_zip(container1_link.end(), container2_link.end());
        }
};