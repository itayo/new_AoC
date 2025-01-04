#include <gtest/gtest.h>
#include <AoC/LinkedList.h>

namespace AoC {


    TEST(LinkedListTest, PushFront) {
        LinkedList<int> list;
        list.push_front(1);
        list.push_front(2);
        list.push_front(3);

        EXPECT_EQ(list.size(), 3);
        EXPECT_EQ(list.ToString(), "3,2,1");
    }


    TEST(LinkedListTest, PushBack) {
        LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        EXPECT_EQ(list.size(), 3);
        EXPECT_EQ(list.ToString(), "1,2,3");
    }


    TEST(LinkedListTest, PopFront) {
        LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.pop_front();

        EXPECT_EQ(list.size(), 2);
        EXPECT_EQ(list.ToString(), "2,3");

        list.pop_front();
        EXPECT_EQ(list.size(), 1);
        EXPECT_EQ(list.ToString(), "3");

        list.pop_front();
        EXPECT_EQ(list.size(), 0);
        EXPECT_EQ(list.ToString(), "");
    }


    TEST(LinkedListTest, PopBack) {
        LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.pop_back();

        EXPECT_EQ(list.size(), 2);
        EXPECT_EQ(list.ToString(), "1,2");

        list.pop_back();
        EXPECT_EQ(list.size(), 1);
        EXPECT_EQ(list.ToString(), "1");

        list.pop_back();
        EXPECT_EQ(list.size(), 0);
        EXPECT_EQ(list.ToString(), "");
    }


    TEST(LinkedListTest, InsertAtPosition) {
        LinkedList<int> list;
        list.push_back(1);
        list.push_back(3);
        list.insert(1, 2);

        EXPECT_EQ(list.size(), 3);
        EXPECT_EQ(list.ToString(), "1,2,3");


        list.insert(0, 0);
        EXPECT_EQ(list.size(), 4);
        EXPECT_EQ(list.ToString(), "0,1,2,3");


        list.insert(4, 4);
        EXPECT_EQ(list.size(), 5);
        EXPECT_EQ(list.ToString(), "0,1,2,3,4");


        EXPECT_THROW(list.insert(6, 5), std::out_of_range);
    }


    TEST(LinkedListTest, Iterator) {
        LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        std::vector<int> values;
        for (auto &val: list) {
            values.push_back(val);
        }

        EXPECT_EQ(values.size(), 3);
        EXPECT_EQ(values[0], 1);
        EXPECT_EQ(values[1], 2);
        EXPECT_EQ(values[2], 3);
    }

    TEST(LinkedListTest, CopyConstructor) {
        LinkedList<int> list1;
        list1.push_back(1);
        list1.push_back(2);

        LinkedList<int> list2(list1);
        EXPECT_EQ(list2.size(), 2);
        EXPECT_EQ(list2.ToString(), "1,2");

        list1.push_back(3);
        EXPECT_EQ(list1.size(), 3);
        EXPECT_EQ(list1.ToString(), "1,2,3");
        EXPECT_EQ(list2.size(), 2);
        EXPECT_EQ(list2.ToString(), "1,2");
    }

    TEST(LinkedListTest, CopyAssignmentOperator) {
        LinkedList<int> list1;
        list1.push_back(1);
        list1.push_back(2);

        LinkedList<int> list2;
        list2.push_back(3);
        list2.push_back(4);

        list2 = list1;
        EXPECT_EQ(list2.size(), 2);
        EXPECT_EQ(list2.ToString(), "1,2");

        list1.push_back(3);
        EXPECT_EQ(list1.size(), 3);
        EXPECT_EQ(list1.ToString(), "1,2,3");
        EXPECT_EQ(list2.size(), 2);
        EXPECT_EQ(list2.ToString(), "1,2");
    }

    TEST(LinkedListTest, RemoveDuplicates) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(2);
        list.push_back(3);
        list.push_back(3);
        list.push_back(4);
        list.push_back(4);

        list.removeDuplicates();

        EXPECT_EQ(list.size(), 4);
        EXPECT_EQ(list.ToString(), "1,2,3,4");
    }

    TEST(LinkedListTest, Sort) {
        AoC::LinkedList<int> list;
        list.push_back(4);
        list.push_back(3);
        list.push_back(1);
        list.push_back(2);

        list.sort();

        EXPECT_EQ(list.ToString(), "1,2,3,4");
    }

    TEST(LinkedListTest, SortWithDuplicates) {
        AoC::LinkedList<int> list;
        list.push_back(4);
        list.push_back(2);
        list.push_back(2);
        list.push_back(1);
        list.push_back(3);

        list.sort();
        list.removeDuplicates();

        EXPECT_EQ(list.ToString(), "1,2,3,4");
    }

    TEST(LinkedListTest, Find) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);

        auto node = list.find(3);
        ASSERT_NE(node, nullptr);
        EXPECT_EQ(node->data, 3);

        node = list.find(5);
        EXPECT_EQ(node, nullptr);
    }

    TEST(LinkedListTest, Contains) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);

        EXPECT_TRUE(list.contains(3));
        EXPECT_FALSE(list.contains(5));
    }

    TEST(LinkedListTest, OperatorStream) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        std::ostringstream os;
        os << list;

        EXPECT_EQ(os.str(), "1,2,3");
    }

    TEST(LinkedListTest, ToVector) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        std::vector<int> vec = list.toVector();

        EXPECT_EQ(vec.size(), 3);
        EXPECT_EQ(vec[0], 1);
        EXPECT_EQ(vec[1], 2);
        EXPECT_EQ(vec[2], 3);
    }

    TEST(LinkedListTest, OperatorIndex) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[1], 2);
        EXPECT_EQ(list[2], 3);
    }

    TEST(LinkedListTest, RemoveAt) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.erase(1);

        EXPECT_EQ(list.size(), 2);
        EXPECT_EQ(list.ToString(), "1,3");
    }

    TEST(LinkedListTest, GetAt) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        EXPECT_EQ(list.getAt(0), 1);
        EXPECT_EQ(list.getAt(1), 2);
        EXPECT_EQ(list.getAt(2), 3);
    }

    TEST(LinkedListTest, Clear) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.clear();

        EXPECT_EQ(list.size(), 0);
        EXPECT_EQ(list.ToString(), "");
    }

    TEST(LinkedListTest, Reverse) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.reverse();

        EXPECT_EQ(list.ToString(), "3,2,1");
    }

    TEST(LinkedListTest, MakeUnique) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(2);
        list.push_back(3);
        list.push_back(3);
        list.push_back(4);

        list.unique();

        EXPECT_EQ(list.size(), 4);
        EXPECT_EQ(list.ToString(), "1,2,3,4");
    }

    TEST(LinkedListTest, MakeUniqueNoDuplicates) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);

        list.unique();

        EXPECT_EQ(list.size(), 4);
        EXPECT_EQ(list.ToString(), "1,2,3,4");
    }

    TEST(LinkedListTest, MakeUniqueAllDuplicates) {
        AoC::LinkedList<int> list;
        list.push_back(1);
        list.push_back(1);
        list.push_back(1);
        list.push_back(1);

        list.unique();

        EXPECT_EQ(list.size(), 1);
        EXPECT_EQ(list.ToString(), "1");
    }

    TEST(LinkedListTest, MakeUniqueEmptyList) {
        AoC::LinkedList<int> list;

        list.unique();

        EXPECT_EQ(list.size(), 0);
        EXPECT_EQ(list.ToString(), "");
    }

}
