#include "CDA.h"
#include <string>
#include <gtest/gtest.h>

namespace {
    class CDATest : public ::testing::Test {
        protected:
            CDA<int> c1;

            void SetUp() override {
            }
    };

    TEST_F(CDATest, defaultConstructor) {
        CDA<int> h1;
        CDA<int> h10;
        CDA<double> h2;
        CDA<double> h20;
        CDA<long long int> h3;
        CDA<long long int> h30;
        CDA<std::string> h4;
        CDA<std::string> h40;
        CDA<char> h5;
        CDA<char> h50;
        CDA<wchar_t> h6;
        CDA<wchar_t> h60;
        CDA<short> h7;
        CDA<short> h70;
        CDA<bool> h8;
        CDA<bool> h80;

        swap(h1, h10);
        swap(h2, h20);
        swap(h3, h30);
        swap(h4, h40);
        swap(h5, h50);
        swap(h6, h60);
        swap(h7, h70);
        swap(h8, h80);
    }

    TEST_F(CDATest, copyConstructor) {
        for (int i = 0; i < 5; ++i) {
            c1.AddEnd(i);
        }

        CDA<int> cCopy(c1);
        cCopy.DelEnd();
        cCopy.DelFront();
        EXPECT_EQ(cCopy.Length(), 3);
        EXPECT_EQ(c1.Length(), 5);
    }
}
