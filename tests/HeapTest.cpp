#include "Heap.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

namespace {
    class HeapTest : public ::testing::Test {
        protected:
            int k1[10] = {5, 3, 2, 6, 8, 9, 0, 1, 4, 7};
            int k1Ordered[10] = {0, 1, 2, 3, 7, 9, 5, 6, 4, 8};
            int k1Inserted[10] = {0, 1, 2, 4, 7, 9, 3, 6, 5, 8};
            int size1 = 10;
            std::ostringstream expectedStringStream;

            void SetUp() override {
            }
    };

    TEST_F(HeapTest, defaultConstructor) {
        Heap<int> h1;
        Heap<double> h2;
        Heap<long long int> h3;
        Heap<std::string> h4;
        Heap<char> h5;
        Heap<wchar_t> h6;
        Heap<short> h7;
        Heap<bool> h8;
    }

    TEST_F(HeapTest, insertionConstructor) {
        Heap<int> h1(k1, size1);

        for (int i = 0; i < size1; ++i) {
            expectedStringStream << k1Ordered[i] << ' ';
        }
        std::string expectedString = expectedStringStream.str();
        expectedString.pop_back();

        EXPECT_EQ(h1.stringKey(), expectedString);
    }

    TEST_F(HeapTest, peekKey) {
        Heap<int> h1(k1, size1);
        EXPECT_EQ(h1.peekKey(), k1Ordered[0]);
    }

    TEST_F(HeapTest, extractMin1) {
        Heap<int> h1(k1, size1);
        for (int i = 0; i < 10; ++i) {
            EXPECT_EQ(h1.extractMin(), i);
        }
    }

    TEST_F(HeapTest, extractMin2) {
        int inputSize = 10000;

        Heap<int> h1;
        for (int i = 0; i < inputSize; ++i) {
            h1.insert(i);
        }

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(h1.extractMin(), i);
        }
    }

    TEST_F(HeapTest, extractMin3) {
        int inputSize = 26;

        Heap<char> h1;
        for (int i = 0; i < inputSize; ++i) {
            h1.insert('A' + i);
        }

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(h1.extractMin(), 'A' + i);
        }
    }

    TEST_F(HeapTest, insert) {
        Heap<int> h1;
        int mins[] = {5, 3, 2, 2, 2, 2, 0, 0, 0, 0};
        for (int i = 0; i < 10; ++i) {
            h1.insert(k1[i]);
            EXPECT_EQ(h1.peekKey(), mins[i]);
        }

        for (int i = 0; i < size1; ++i) {
            expectedStringStream << k1Inserted[i] << ' ';
        }
        std::string expectedString = expectedStringStream.str();
        expectedString.pop_back();

        EXPECT_EQ(h1.stringKey(), expectedString);
    }

    TEST_F(HeapTest, printKey) {
        Heap<int> h1(k1, size1);
        h1.printKey();

        for (int i = 0; i < size1; ++i) {
            std::cout << k1Ordered[i] << ' ';
        }
        std::cout << std::endl;

        // Should print the same thing twice
    }
}
