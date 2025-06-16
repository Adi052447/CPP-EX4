//adi.gamzu@gmail.com


#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace ariel {

/**
 * @brief A generic container class that supports multiple custom iteration orders.
 * 
 * @tparam T The type of elements stored in the container. Default is int.
 */
template <typename T = int>
class MyContainer {
private:
    vector<T> data; ///< Internal storage for elements.

public:
    // Forward declarations for iterator classes
    class Order;
    class AscendingOrder;
    class DescendingOrder;
    class SideCrossOrder;
    class ReverseOrder;
    class MiddleOutOrder;

    MyContainer() = default;
    MyContainer(const MyContainer& other) : data(other.data) {}
    ~MyContainer() = default;

    
        /**
         * @brief Copy assignment operator.
         * @param other The container to copy from.
         * @return Reference to this container.
         */
        MyContainer& operator=(const MyContainer& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    
        /**
         * @brief Get the number of elements in the container.
         * @return Number of elements currently stored.
         */
        size_t size() const {
        return data.size();
    }

    
        /**
         * @brief Add an element to the container.
         * @param item The element to add.
         */
        void add(const T& item) {
        data.push_back(item);
    }

    
        /**
         * @brief Remove all occurrences of a specific element.
         * @param item The element to remove.
         * @throws std::invalid_argument if the element does not exist in the container.
         */
        void remove(const T& item) {
        bool removed = false;
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == item) {
                data.erase(data.begin() + i);
                --i;
                removed = true;
            }
        }
        if (!removed) {
            throw std::invalid_argument("ERROR: Object does not exist\n");
        }
    }

    
        /**
         * @brief Print the container contents using stream output.
         * @param os The output stream.
         * @param container The container to print.
         * @return Reference to the output stream.
         */
        friend ostream& operator<<(ostream& os, const MyContainer<T>& container) {
        os << "{";
        for (size_t i = 0; i < container.size(); ++i) {
            os << container.data[i];
            if (i < container.size() - 1) os << ", ";
        }
        os << "}";
        return os;
    }

    // Iterator creators
    
        /**
         * @brief Begin iterator for default order (insertion order).
         * @return Iterator to the beginning.
         */
        Order begin_order() { return Order(this, 0); }
    
        /**
         * @brief End iterator for default order (insertion order).
         * @return Iterator past the last element.
         */
        Order end_order() { return Order(this, data.size()); }

    
        /**
         * @brief Begin iterator for ascending order.
         * @return Iterator to the smallest element.
         */
        AscendingOrder begin_ascending_order() { return AscendingOrder(this, 0); }
    
        /**
         * @brief End iterator for ascending order.
         * @return Iterator past the largest element.
         */
        AscendingOrder end_ascending_order() { return AscendingOrder(this, data.size()); }

    
        /**
         * @brief Begin iterator for descending order.
         * @return Iterator to the largest element.
         */
        DescendingOrder begin_descending_order() { return DescendingOrder(this, 0); }
    
        /**
         * @brief End iterator for descending order.
         * @return Iterator past the smallest element.
         */
        DescendingOrder end_descending_order() { return DescendingOrder(this, data.size()); }

    
        /**
         * @brief Begin iterator for reverse insertion order.
         * @return Iterator to the last inserted element.
         */
        ReverseOrder begin_reverse_order() { return ReverseOrder(this, 0); }
    
        /**
         * @brief End iterator for reverse insertion order.
         * @return Iterator past the first inserted element.
         */
        ReverseOrder end_reverse_order() { return ReverseOrder(this, data.size()); }

    
        /**
         * @brief Begin iterator for SideCross order (smallest-largest alternating).
         * @return Iterator to the start of the cross order.
         */
        SideCrossOrder begin_side_cross_order() { return SideCrossOrder(this, 0); }
    
        /**
         * @brief End iterator for SideCross order.
         * @return Iterator past the last element in the SideCross pattern.
         */
        SideCrossOrder end_side_cross_order() {
        return SideCrossOrder(this, (data.size() <= 1 ? data.size() : data.size() / 2));
    }

    
        /**
         * @brief Begin iterator for MiddleOut order (center to edges).
         * @return Iterator to the middle of the sequence.
         */
        MiddleOutOrder begin_middle_out_order() { return MiddleOutOrder(this, data.size() / 2); }
    
        /**
         * @brief End iterator for MiddleOut order.
         * @return Iterator past the last element.
         */
        MiddleOutOrder end_middle_out_order() { return MiddleOutOrder(this, data.size()); }

    /**
     * @brief Basic iterator: iterates in insertion order.
     */
    class Order {
    private:
        MyContainer* container;
        size_t index;

    public:
        Order(MyContainer* cont, size_t idx) : container(cont), index(idx) {
            if (!cont) throw std::invalid_argument("Container pointer cannot be null");
        }

        
        /**
         * @brief Dereference operator.
         * @return Reference to the current element.
         * @throws std::out_of_range if the iterator is out of bounds.
         */
        T& operator*() {
            if (index >= container->data.size())
                throw std::out_of_range("Iterator is at end position - cannot dereference");
            return container->data[index];
        }

        
        /**
         * @brief Pre-increment operator.
         * @return Reference to this iterator after advancing.
         * @throws std::out_of_range if incrementing past end.
         */
        Order& operator++() {
            if (index >= container->data.size())
                throw std::out_of_range("Cannot increment iterator past end");
            ++index;
            return *this;
        }

        
        /**
         * @brief Post-increment operator.
         * @return Copy of iterator before incrementing.
         */
        Order operator++(int) {
            Order temp = *this;
            ++(*this);
            return temp;
        }

        
        /**
         * @brief Equality comparison.
         * @param other Another Order iterator.
         * @return True if both point to the same container and index.
         */
        bool operator==(const Order& other) const {
            return container == other.container && index == other.index;
        }

        
        /**
         * @brief Inequality comparison.
         * @param other Another Order iterator.
         * @return True if not equal.
         */
        bool operator!=(const Order& other) const {
            return !(*this == other);
        }

        
        /**
         * @brief Assignment operator.
         * @param other Iterator to copy from.
         * @return Reference to this.
         */
        Order& operator=(const Order& other) {
            if (this != &other) {
                container = other.container;
                index = other.index;
            }
            return *this;
        }
    };

    /**
     * @brief Ascending iterator: elements sorted in increasing order.
     */
    class AscendingOrder {
    private:
        vector<T> sorted;
        size_t index;

    public:
        AscendingOrder(MyContainer* cont, size_t idx) : index(idx) {
            if (!cont) throw std::invalid_argument("Container pointer cannot be null");
            sorted = cont->data;
            sort(sorted.begin(), sorted.end());
        }

        
        /**
         * @brief Dereference operator.
         * @return Reference to the current element.
         * @throws std::out_of_range if the iterator is out of bounds.
         */
        T& operator*() {
            if (index >= sorted.size())
                throw std::out_of_range("Iterator is at end position - cannot dereference");
            return sorted[index];
        }

        
        /**
         * @brief Pre-increment operator.
         * @return Reference to this iterator after advancing.
         * @throws std::out_of_range if incrementing past end.
         */
        AscendingOrder& operator++() {
            if (index >= sorted.size())
                throw std::out_of_range("Cannot increment iterator past end");
            ++index;
            return *this;
        }

        
        /**
         * @brief Post-increment operator.
         * @return Copy of iterator before incrementing.
         */
        AscendingOrder operator++(int) {
            AscendingOrder temp = *this;
            ++(*this);
            return temp;
        }

        
        /**
         * @brief Equality check for AscendingOrder.
         */
        bool operator==(const AscendingOrder& other) const {
            return sorted == other.sorted && index == other.index;
        }

        
        /**
         * @brief Inequality check for AscendingOrder.
         */
        bool operator!=(const AscendingOrder& other) const {
            return !(*this == other);
        }

        
        /**
         * @brief Assignment operator for AscendingOrder.
         */
        AscendingOrder& operator=(const AscendingOrder& other) {
            if (this != &other) {
                sorted = other.sorted;
                index = other.index;
            }
            return *this;
        }
    };

    /**
     * @brief Descending iterator: elements sorted in decreasing order.
     */
    class DescendingOrder {
    private:
        vector<T> sorted;
        size_t index;

    public:
        DescendingOrder(MyContainer* cont, size_t idx) : index(idx) {
            if (!cont) throw std::invalid_argument("Container pointer cannot be null");
            sorted = cont->data;
            sort(sorted.begin(), sorted.end());
            reverse(sorted.begin(), sorted.end());
        }

        
        /**
         * @brief Dereference operator.
         * @return Reference to the current element.
         * @throws std::out_of_range if the iterator is out of bounds.
         */
        T& operator*() {
            if (index >= sorted.size())
                throw std::out_of_range("Iterator is at end position - cannot dereference");
            return sorted[index];
        }

        
        /**
         * @brief Pre-increment operator.
         * @return Reference to this iterator after advancing.
         * @throws std::out_of_range if incrementing past end.
         */
        DescendingOrder& operator++()  {
            if (index >= sorted.size())
                throw std::out_of_range("Cannot increment iterator past end");
            ++index;
            return *this;
        }

        
        /**
         * @brief Post-increment operator.
         * @return Copy of iterator before incrementing.
         */
        DescendingOrder operator++(int) {
            DescendingOrder temp = *this;
            ++(*this);
            return temp;
        }

                /**
         * @brief Equality operator for DescendingOrder.
         */
        bool operator==(const DescendingOrder& other) const {
            return sorted == other.sorted && index == other.index;
        }

                /**
         * @brief Inequality operator for DescendingOrder.
         */
        bool operator!=(const DescendingOrder& other) const {
            return !(*this == other);
        }

                /**
         * @brief Assignment operator for DescendingOrder.
         */
        DescendingOrder& operator=(const DescendingOrder& other) {
            if (this != &other) {
                sorted = other.sorted;
                index = other.index;
            }
            return *this;
        }
    };

    /**
     * @brief Reverse iterator: elements in reverse insertion order.
     */
    class ReverseOrder {
    private:
        vector<T> reversed;
        size_t index;

    public:
        ReverseOrder(MyContainer* cont, size_t idx) : index(idx) {
            if (!cont) throw std::invalid_argument("Container pointer cannot be null");
            reversed = cont->data;
            reverse(reversed.begin(), reversed.end());
        }

        
        /**
         * @brief Dereference operator.
         * @return Reference to the current element.
         * @throws std::out_of_range if the iterator is out of bounds.
         */
        T& operator*() {
            if (index >= reversed.size())
                throw std::out_of_range("Iterator is at end position - cannot dereference");
            return reversed[index];
        }

        
        /**
         * @brief Pre-increment operator.
         * @return Reference to this iterator after advancing.
         * @throws std::out_of_range if incrementing past end.
         */
        ReverseOrder& operator++() {
            if (index >= reversed.size())
                throw std::out_of_range("Cannot increment iterator past end");
            ++index;
            return *this;
        }

        
        /**
         * @brief Post-increment operator.
         * @return Copy of iterator before incrementing.
         */
        ReverseOrder operator++(int) {
            ReverseOrder temp = *this;
            ++(*this);
            return temp;
        }

                /**
         * @brief Equality operator for ReverseOrder.
         */
        bool operator==(const ReverseOrder& other) const {
            return reversed == other.reversed && index == other.index;
        }

                /**
         * @brief Inequality operator for ReverseOrder.
         */
        bool operator!=(const ReverseOrder& other) const {
            return !(*this == other);
        }

                /**
         * @brief Assignment operator for ReverseOrder.
         */
        ReverseOrder& operator=(const ReverseOrder& other) {
            if (this != &other) {
                reversed = other.reversed;
                index = other.index;
            }
            return *this;
        }
    };

    /**
     * @brief SideCross iterator: alternates between smallest and largest remaining elements.
     */
    class SideCrossOrder {
    private:
        vector<T> sorted;
        size_t left, right, index;
        bool left_turn;

    public:
        SideCrossOrder(MyContainer* cont, size_t idx) : index(idx) {
            if (!cont) throw std::invalid_argument("Container pointer cannot be null");
            sorted = cont->data;
            sort(sorted.begin(), sorted.end());
            left_turn = true;
            left = 0;
            right = sorted.size() > 0 ? sorted.size() - 1 : 0;
        }

        
        /**
         * @brief Dereference operator.
         * @return Reference to the current element.
         * @throws std::out_of_range if the iterator is out of bounds.
         */
        T& operator*() {
            if (sorted.empty() || index >= sorted.size() || left > right)
                throw std::out_of_range("Iterator out of range");
            index = left_turn ? left : right;
            return sorted[index];
        }

        
        /**
         * @brief Pre-increment operator.
         * @return Reference to this iterator after advancing.
         * @throws std::out_of_range if incrementing past end.
         */
       SideCrossOrder& operator++() {
            if (index >= sorted.size() || left > right)
                throw std::out_of_range("Cannot increment iterator past end");
            if (sorted.size() == 1) {
                ++index;
            } else if (left_turn) {
                index = left++;
                left_turn = false;
            } else {
                index = right--;
                left_turn = true;
            }
            return *this;
        }

        
        /**
         * @brief Post-increment operator.
         * @return Copy of iterator before incrementing.
         */
       SideCrossOrder operator++(int) {
            SideCrossOrder temp = *this;
            ++(*this);
            return temp;
        }

                /**
         * @brief Equality operator for SideCrossOrder.
         */
        bool operator==(const SideCrossOrder& other) const {
            return sorted == other.sorted && index == other.index;
        }

                /**
         * @brief Inequality operator for SideCrossOrder.
         */
        bool operator!=(const SideCrossOrder& other) const {
            return !(*this == other);
        }

                /**
         * @brief Assignment operator for SideCrossOrder.
         */
        SideCrossOrder& operator=(const SideCrossOrder& other) {
            if (this != &other) {
                sorted = other.sorted;
                index = other.index;
                left = other.left;
                right = other.right;
                left_turn = other.left_turn;
            }
            return *this;
        }
    };

    /**
     * @brief MiddleOut iterator: starts at middle, moves outward alternately left and right.
     */
    class MiddleOutOrder {
    private:
        vector<T> sequence;
        size_t index, offset;
        bool move_left;

    public:
        MiddleOutOrder(MyContainer* cont, size_t idx) : index(idx), offset(0), move_left(true) {
            if (!cont) throw std::invalid_argument("Container pointer cannot be null");
            sequence = cont->data;
        }

        
        /**
         * @brief Dereference operator.
         * @return Reference to the current element.
         * @throws std::out_of_range if the iterator is out of bounds.
         */
        T& operator*() {
            if (index >= sequence.size())
                throw std::out_of_range("Iterator is at end position - cannot dereference");
            return sequence[index];
        }

        
        /**
         * @brief Pre-increment operator.
         * @return Reference to this iterator after advancing.
         * @throws std::out_of_range if incrementing past end.
         */
        MiddleOutOrder&  operator++() {
            if (move_left) {
                if (index > offset) {
                    index -= ++offset;
                    move_left = false;
                } else {
                    index = sequence.size();
                }
            } else {
                if (index + offset < sequence.size()) {
                    index += ++offset;
                    move_left = true;
                } else {
                    index = sequence.size();
                }
            }
            return *this;
        }

        
        /**
         * @brief Post-increment operator.
         * @return Copy of iterator before incrementing.
         */
        MiddleOutOrder operator++(int) {
            MiddleOutOrder temp = *this;
            ++(*this);
            return temp;
        }

                /**
         * @brief Equality operator for MiddleOutOrder.
         */
        bool operator==(const MiddleOutOrder& other) const {
            return sequence == other.sequence && index == other.index;
        }

                /**
         * @brief Inequality operator for MiddleOutOrder.
         */
        bool operator!=(const MiddleOutOrder& other) const {
            return !(*this == other);
        }

                /**
         * @brief Assignment operator for MiddleOutOrder.
         */
        MiddleOutOrder& operator=(const MiddleOutOrder& other) {
            if (this != &other) {
                sequence = other.sequence;
                index = other.index;
                offset = other.offset;
                move_left = other.move_left;
            }
            return *this;
        }
    };
};

}  // namespace ariel
