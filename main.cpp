//adi.gamzu@gmail.com
#include <iostream>
#include <string>
#include "MyContainer.hpp"
using namespace ariel;

int main() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "INT CONTAINER DEMONSTRATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    MyContainer<int> intBox;
    intBox.add(7);
    intBox.add(15);
    intBox.add(6);
    intBox.add(1);
    intBox.add(2);

    std::cout << "Total elements in intBox: " << intBox.size() << std::endl;
    std::cout << intBox << std::endl;

    std::cout << "SEQUENCE (Ascending):\n";
    for (auto it = intBox.begin_ascending_order(); it != intBox.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "SEQUENCE (Descending):\n";
    for (auto it = intBox.begin_descending_order(); it != intBox.end_descending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "SEQUENCE (Side-Cross):\n";
    for (auto it = intBox.begin_side_cross_order(); it != intBox.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "SEQUENCE (Reverse):\n";
    for (auto it = intBox.begin_reverse_order(); it != intBox.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "SEQUENCE (Insertion Order):\n";
    for (auto it = intBox.begin_order(); it != intBox.end_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "SEQUENCE (From Center Outward):\n";
    for (auto it = intBox.begin_middle_out_order(); it != intBox.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    intBox.add(2);
    intBox.add(2);

    std::cout << "Total elements in intBox after adding: " << intBox.size() << std::endl;
    std::cout << intBox << std::endl;

    intBox.remove(2);

    std::cout << "After removing all 2s: " << intBox.size() << std::endl;
    std::cout << intBox << std::endl;

    try {
        intBox.remove(2);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "STRING CONTAINER EXAMPLE" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    MyContainer<std::string> wordsBox;
    wordsBox.add("apple");
    wordsBox.add("zebra");
    wordsBox.add("banana");
    wordsBox.add("cherry");
    wordsBox.add("date");

    std::cout << "Total elements in wordsBox: " << wordsBox.size() << std::endl;
    std::cout << wordsBox << std::endl;

    std::cout << "ASCENDING STRINGS:\n";
    for (auto it = wordsBox.begin_ascending_order(); it != wordsBox.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "DESCENDING STRINGS:\n";
    for (auto it = wordsBox.begin_descending_order(); it != wordsBox.end_descending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "CROSS STRINGS:\n";
    for (auto it = wordsBox.begin_side_cross_order(); it != wordsBox.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "REVERSE STRINGS:\n";
    for (auto it = wordsBox.begin_reverse_order(); it != wordsBox.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "ORIGINAL ORDER STRINGS:\n";
    for (auto it = wordsBox.begin_order(); it != wordsBox.end_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "FROM CENTER OUTWARD STRINGS:\n";
    for (auto it = wordsBox.begin_middle_out_order(); it != wordsBox.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    wordsBox.add("apple");
    wordsBox.add("apple");

    std::cout << "Total after duplicates: " << wordsBox.size() << std::endl;
    std::cout << wordsBox << std::endl;

    wordsBox.remove("apple");

    std::cout << "Size after removing 'apple': " << wordsBox.size() << std::endl;
    std::cout << wordsBox << std::endl;

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "DOUBLE CONTAINER TEST" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    MyContainer<double> floatBox;
    floatBox.add(3.14);
    floatBox.add(2.71);
    floatBox.add(1.41);
    floatBox.add(9.81);
    floatBox.add(6.28);

    std::cout << "Elements in floatBox: " << floatBox.size() << std::endl;
    std::cout << floatBox << std::endl;

    std::cout << "ASCENDING DOUBLES:\n";
    for (auto it = floatBox.begin_ascending_order(); it != floatBox.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "DESCENDING DOUBLES:\n";
    for (auto it = floatBox.begin_descending_order(); it != floatBox.end_descending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "CROSS DOUBLES:\n";
    for (auto it = floatBox.begin_side_cross_order(); it != floatBox.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "REVERSE DOUBLES:\n";
    for (auto it = floatBox.begin_reverse_order(); it != floatBox.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "INSERTION ORDER DOUBLES:\n";
    for (auto it = floatBox.begin_order(); it != floatBox.end_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "CENTER OUT DOUBLES:\n";
    for (auto it = floatBox.begin_middle_out_order(); it != floatBox.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    floatBox.add(3.14);
    floatBox.add(3.14);

    std::cout << "Size with duplicates: " << floatBox.size() << std::endl;
    std::cout << floatBox << std::endl;

    floatBox.remove(3.14);

    std::cout << "After removal of 3.14: " << floatBox.size() << std::endl;
    std::cout << floatBox << std::endl;

    try {
        floatBox.remove(99.99);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}