//adi.gamzu@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "MyContainer.hpp"
#include "doctest.h"
#include <sstream>
#include <string>

using namespace ariel;

/* ════════════════════════════════
   1. בדיקות ליבה – בנאים, השמה וגודל
   ════════════════════════════════ */
TEST_CASE("Core behaviour: ctor / copy / size / <<") {

    SUBCASE("Default-constructed container is empty") {
        MyContainer<int> box;
        CHECK(box.size() == 0);
    }

    SUBCASE("Copy-constructor duplicates size & data") {
        MyContainer<int> src;
        src.add(2);
        src.add(4);
        src.add(6);

        MyContainer<int> dup(src);
        CHECK(dup.size() == 3);
        CHECK(src.size() == dup.size());
    }

    SUBCASE("Copy-assignment overwrites previous content") {
        MyContainer<int> a, b;
        a.add(1); a.add(2);
        b.add(9); b.add(8); b.add(7);

        b = a;
        CHECK(b.size() == 2);
    }

    SUBCASE("Streaming operator formats correctly") {
        MyContainer<int> nums;
        std::ostringstream oss;

        oss << nums;
        CHECK(oss.str() == "{}");

        nums.add(10); nums.add(20); nums.add(30);
        std::ostringstream oss2;
        oss2 << nums;
        CHECK(oss2.str() == "{10, 20, 30}");
    }
}

/* ════════════════════════════════
   2. הוספה והסרה
   ════════════════════════════════ */
TEST_CASE("Insertion & removal") {

    SUBCASE("Push back a single element") {
        MyContainer<int> c;
        c.add(5);
        CHECK(c.size() == 1);
    }

    SUBCASE("Adding duplicates does *not* merge") {
        MyContainer<int> c;
        c.add(7); c.add(7); c.add(7);
        CHECK(c.size() == 3);
    }

    SUBCASE("Removing value deletes all its instances") {
        MyContainer<int> c;
        for(int i=0;i<3;++i) c.add(9);
        c.add(1);
        c.remove(9);
        CHECK(c.size() == 1);
        CHECK_THROWS_AS(c.remove(9), std::invalid_argument);
    }

    SUBCASE("Removing from empty container throws") {
        MyContainer<std::string> s;
        CHECK_THROWS_AS(s.remove("ghost"), std::invalid_argument);
    }
}

/* ════════════════════════════════
   3. Order iterator – insertion sequence
   ════════════════════════════════ */
TEST_CASE("Iterator: Order (insertion)") {

    SUBCASE("Empty container begin==end") {
        MyContainer<int> c;
        CHECK(c.begin_order() == c.end_order());
    }

    SUBCASE("Traversal matches push sequence") {
        MyContainer<int> c;
        c.add(5); c.add(3); c.add(8);

        std::vector<int> got;
        for(auto it=c.begin_order(); it!=c.end_order(); ++it) got.push_back(*it);

        CHECK(got == std::vector<int>{5,3,8});
    }

    SUBCASE("Operator overloading sanity") {
        MyContainer<int> c; c.add(1); c.add(2);
        auto a = c.begin_order(), b = c.begin_order();
        CHECK(a == b);
        CHECK(*a == 1);
        ++a;
        CHECK(*a == 2);
        CHECK(a != b);
    }

    SUBCASE("Out-of-range protections") {
        MyContainer<int> x; x.add(9);
        auto it = x.end_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
        auto b = x.begin_order(); ++b;
        CHECK_THROWS_AS(++b, std::out_of_range);
    }
}

/* ════════════════════════════════
   4. Iterators that sort (ascending / descending)
   ════════════════════════════════ */
TEST_CASE("Iterators: Ascending & Descending") {

    SUBCASE("Ascending – typical list") {
        MyContainer<int> c; c.add(4); c.add(1); c.add(3);
        std::vector<int> v;
        for(auto i=c.begin_ascending_order(); i!=c.end_ascending_order(); ++i) v.push_back(*i);
        CHECK(v == std::vector<int>{1,3,4});
    }

    SUBCASE("Descending – duplicates kept") {
        MyContainer<int> c; c.add(2); c.add(2); c.add(1);
        std::vector<int> v;
        for(auto i=c.begin_descending_order(); i!=c.end_descending_order(); ++i) v.push_back(*i);
        CHECK(v == std::vector<int>{2,2,1});
    }

    SUBCASE("Null-ptr ctor throws") {
        CHECK_THROWS_AS(MyContainer<int>::AscendingOrder(nullptr,0), std::invalid_argument);
        CHECK_THROWS_AS(MyContainer<int>::DescendingOrder(nullptr,0), std::invalid_argument);
    }
}

/* ════════════════════════════════
   5. Reverse iterator
   ════════════════════════════════ */
TEST_CASE("Iterator: Reverse") {

    SUBCASE("Reverse mirrors insertion") {
        MyContainer<char> c; c.add('a'); c.add('b'); c.add('c');
        std::string s;
        for(auto it=c.begin_reverse_order(); it!=c.end_reverse_order(); ++it) s+=*it;
        CHECK(s == "cba");
    }

    SUBCASE("Single element works") {
        MyContainer<int> c; c.add(42);
        auto beg = c.begin_reverse_order();
        CHECK(*beg == 42);
        ++beg;
        CHECK(beg == c.end_reverse_order());
    }
}

/* ════════════════════════════════
   6. Side-cross iterator
   ════════════════════════════════ */
TEST_CASE("Iterator: SideCross pattern") {

    SUBCASE("Odd count") {
        MyContainer<int> c; for(int v: {5,1,4,2,3}) c.add(v);
        std::vector<int> actual;
        for(auto it=c.begin_side_cross_order(); it!=c.end_side_cross_order(); ++it) actual.push_back(*it);
        // Expected pattern: 1 5 2 4 3
        CHECK(actual == std::vector<int>{1,5,2,4,3});
    }

   SUBCASE("Even count") {
    MyContainer<int> c;
    for (int v : {4, 1, 3, 2}) c.add(v);

    std::vector<int> got;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        got.push_back(*it);
    }

    CHECK(got == std::vector<int>{1, 4, 2, 3});
}

}

/* ════════════════════════════════
   7. Middle-out iterator
   ════════════════════════════════ */
TEST_CASE("Iterator: Middle-Out") {

    SUBCASE("Classic example (odd)") {
        MyContainer<int> c; for(int v: {7,15,6,1,2}) c.add(v);
        std::vector<int> out;
        for(auto it=c.begin_middle_out_order(); it!=c.end_middle_out_order(); ++it) out.push_back(*it);
        CHECK(out == std::vector<int>{6,15,1,7,2});
    }

    SUBCASE("Even number of items") {
    MyContainer<int> c;
    for(int v: {1,2,3,4}) c.add(v);

    std::vector<int> out;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        out.push_back(*it);
    }

    CHECK(out.front() == 3);
    CHECK(out.size() == 4);
}

}

/* ════════════════════════════════
   8. Containers of different types
   ════════════════════════════════ */
TEST_CASE("Generic-type support (string / double / char)") {

    SUBCASE("String ascending") {
    MyContainer<std::string> s;
    for (const auto& w : {"zoo", "ant", "cat"}) {
        s.add(w);
    }

    std::vector<std::string> asc;
    for (auto it = s.begin_ascending_order(); it != s.end_ascending_order(); ++it) {
        asc.push_back(*it);
    }

    CHECK(asc == std::vector<std::string>{"ant", "cat", "zoo"});
}


    SUBCASE("Double descending precision") {
        MyContainer<double> d; d.add(2.71); d.add(3.14); d.add(1.41);
        auto first = *d.begin_descending_order();
        CHECK(first == doctest::Approx(3.14));
    }

    SUBCASE("Char container duplicates") {
    MyContainer<char> letters;
    letters.add('b');
    letters.add('a');
    letters.add('b');

    std::vector<char> asc;
    for (auto it = letters.begin_ascending_order(); it != letters.end_ascending_order(); ++it) {
        asc.push_back(*it);
    }

    CHECK(asc == std::vector<char>{'a', 'b', 'b'});
}

}

/* ════════════════════════════════
   9. Iterator copy / assignment / post-increment  
   ════════════════════════════════ */
TEST_CASE("Iterator semantics (copy, assign, ++)") {

    MyContainer<int> c; for(int i:{1,2,3}) c.add(i);

    SUBCASE("Copy-ctor keeps equality") {
        auto it1 = c.begin_order();
        auto it2(it1);
        CHECK(it1 == it2);
        CHECK(*it2 == 1);
    }

    SUBCASE("Assignment operator works for AscendingOrder") {
        auto a = c.begin_ascending_order();
        auto b = c.end_ascending_order();
        b = a;
        CHECK(a == b);
    }

    SUBCASE("Post-increment returns previous value") {
        auto it = c.begin_descending_order();   // order: 3 2 1
        auto old = it++;
        CHECK(*old == 3);  // before increment
        CHECK(*it  == 2);  // after  increment
    }

    SUBCASE("Self-assignment tolerated") {
        auto it = c.begin_reverse_order();
        it = it;
        CHECK(*it == 3);
    }
}

/* ════════════════════════════════
   10. Boundary & error scenarios  
   ════════════════════════════════ */
TEST_CASE("Boundary & error scenarios") {

    SUBCASE("End iterators dereference throw") {
        MyContainer<int> c; c.add(9);
        CHECK_THROWS_AS(*c.end_order(), std::out_of_range);
    }

    SUBCASE("Null-pointer ctor throws (sample)") {
        CHECK_THROWS_AS(MyContainer<int>::ReverseOrder(nullptr,0), std::invalid_argument);
    }

    SUBCASE("Large container still sorted") {
    MyContainer<int> many;
    for (int i = 0; i < 120; ++i) {
        many.add(i % 12);
    }

    many.remove(5);

    std::vector<int> asc;
    for (auto it = many.begin_ascending_order(); it != many.end_ascending_order(); ++it) {
        asc.push_back(*it);
    }

    CHECK(std::is_sorted(asc.begin(), asc.end()));
    CHECK(asc.size() == 110);
}

}
