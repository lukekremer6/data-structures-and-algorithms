#include "Two4Tree.h"
#include <gtest/gtest.h>
#include <random>
#include <time.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>

namespace {
    TEST(Two4TreeTest, defaultConstructor) {
        Two4Tree<char, int> t1;
        EXPECT_NE(t1.getRoot(), nullptr);
        EXPECT_EQ(t1.size(), 0);
        Two4Tree<double, long double> t2;
        Two4Tree<long long int, float> t3;
        Two4Tree<short, std::string> t4;
        Two4Tree<std::string, wchar_t> t5;
    }

    TEST(Two4TreeTest, insertionConstructor) {
        int inputSize = 10;

        char x2[inputSize] = {'F', 'C', 'J', 'A', 'E', 'D', 'B', 'I', 'G', 'H'};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        Two4Tree<char, int> t(x2, y2, inputSize);

        std::string inorder = t.inorderString();
        std::string expectedInorder = "A B C D E F G H I J";

        std::string preorder = t.preorderString();
        std::string expectedPreorder = "C F I A B D E G H J";

        std::string postorder = t.postorderString();
        std::string expectedPostorder = "A B D E G H J C F I";

        EXPECT_EQ(inorder, expectedInorder);
        EXPECT_EQ(preorder, expectedPreorder);
        EXPECT_EQ(postorder, expectedPostorder);
    }

    void foo(Two4Tree<int, int> t) {
        for (int i = 0; t.size() > 0; ++i) {
            t.remove(i);
        }
    }

    TEST(Two4TreeTest, copyConstructor) {
        Two4Tree<int, int> t1;

        int inputSize = 10000;

        int x[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x[i] = i;
        }

        for (int i = 0; i < inputSize; ++i) {
            t1.insert(x[i], x[i]);
        }

        Two4Tree<int, int> t2(t1);
        EXPECT_NE(t1.getRoot(), t2.getRoot());

        std::ostringstream expectedInorder;

        for (int i = 0; i < inputSize; ++i) {
            expectedInorder << x[i] << ' ';
        }

        std::string expectedInorderString = expectedInorder.str();
        expectedInorderString.pop_back();

        EXPECT_EQ(t1.inorderString(), t2.inorderString());
        EXPECT_EQ(t1.preorderString(), t2.preorderString());
        EXPECT_EQ(t1.postorderString(), t2.postorderString());

        for (int i = 0; i < inputSize; ++i) {
            t1.remove(x[i]);
        }

        EXPECT_EQ(t2.inorderString(), expectedInorderString);
        EXPECT_EQ(t1.inorderString(), (std::string) "");

        foo(t2);
        EXPECT_EQ(t2.inorderString(), expectedInorderString);
    }

    TEST(Two4TreeTest, copyAssignmentOperator) {
        Two4Tree<int, int> t1;

        int inputSize = 10000;

        int x[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x[i] = i;
        }

        for (int i = 0; i < inputSize; ++i) {
            t1.insert(x[i], x[i]);
        }

        Two4Tree<int, int> t2 = t1;
        EXPECT_NE(t1.getRoot(), t2.getRoot());

        std::ostringstream expectedInorder;

        for (int i = 0; i < inputSize; ++i) {
            expectedInorder << x[i] << ' ';
        }

        std::string expectedInorderString = expectedInorder.str();
        expectedInorderString.pop_back();

        EXPECT_EQ(t1.inorderString(), t2.inorderString());
        EXPECT_EQ(t1.preorderString(), t2.preorderString());
        EXPECT_EQ(t1.postorderString(), t2.postorderString());

        for (int i = 0; i < inputSize; ++i) {
            t1.remove(x[i]);
        }

        EXPECT_EQ(t2.inorderString(), expectedInorderString);
    }

    TEST(Two4TreeTest, insert1) {
        Two4Tree<char, int> t;
        
        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x2[i], y2[i]);
        }
        EXPECT_EQ(t.size(), 3);

        std::string inorder = t.inorderString();
        std::string expectedInorder = "A B C";

        std::string preorder = t.preorderString();
        std::string expectedPreorder = "A B C";

        std::string postorder = t.postorderString();
        std::string expectedPostorder = "A B C";

        EXPECT_EQ(inorder, expectedInorder);
        EXPECT_EQ(preorder, expectedPreorder);
        EXPECT_EQ(postorder, expectedPostorder);
    }

    TEST(Two4TreeTest, insert2) {
        Two4Tree<char, int> t;
        
        int inputSize = 4;

        char x2[inputSize] = {'A', 'B', 'C', 'D'};
        int y2[inputSize] = {10, 20, 30, 40};

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x2[i], y2[i]);
        }
        EXPECT_EQ(t.size(), inputSize);

        std::string inorder = t.inorderString();
        std::string expectedInorder = "A B C D";

        std::string preorder = t.preorderString();
        std::string expectedPreorder = "B A C D";

        std::string postorder = t.postorderString();
        std::string expectedPostorder = "A C D B";

        EXPECT_EQ(inorder, expectedInorder);
        EXPECT_EQ(preorder, expectedPreorder);
        EXPECT_EQ(postorder, expectedPostorder);
    }

    TEST(Two4TreeTest, insert3) {
        Two4Tree<char, int> t;
        
        int inputSize = 4;

        char x2[inputSize] = {'C', 'A', 'D', 'B'};
        int y2[inputSize] = {10, 20, 30, 40};

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x2[i], y2[i]);
        }
        EXPECT_EQ(t.size(), inputSize);

        std::string inorder = t.inorderString();
        std::string expectedInorder = "A B C D";

        std::string preorder = t.preorderString();
        std::string expectedPreorder = "C A B D";

        std::string postorder = t.postorderString();
        std::string expectedPostorder = "A B D C";

        EXPECT_EQ(inorder, expectedInorder);
        EXPECT_EQ(preorder, expectedPreorder);
        EXPECT_EQ(postorder, expectedPostorder);
    }

    TEST(Two4TreeTest, insert4) {
        Two4Tree<char, int> t;

        int inputSize = 10;

        char x2[inputSize] = {'F', 'C', 'J', 'A', 'E', 'D', 'B', 'I', 'G', 'H'};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x2[i], y2[i]);
        }
        EXPECT_EQ(t.size(), inputSize);

        std::string inorder = t.inorderString();
        std::string expectedInorder = "A B C D E F G H I J";

        std::string preorder = t.preorderString();
        std::string expectedPreorder = "C F I A B D E G H J";

        std::string postorder = t.postorderString();
        std::string expectedPostorder = "A B D E G H J C F I";

        EXPECT_EQ(inorder, expectedInorder);
        EXPECT_EQ(preorder, expectedPreorder);
        EXPECT_EQ(postorder, expectedPostorder);
    }

    TEST(Two4TreeTest, insert5) {
        Two4Tree<int, int> t;

        srand(time(0));
        
        int inputSize = 1000;

        std::vector<int> x;
        std::vector<int> y;

        for (int i = 0; i < inputSize; ++i) {
            x.push_back(rand());
            y.push_back(i);
        }

        std::vector<int> z = x;

        for (int i = 0; i < inputSize; ++i) {
            t.insert(x.at(i), y.at(i));
        }

        std::sort(x.begin(), x.end());

        std::ostringstream expectedInorder;

        for (int i = 0; i < inputSize; ++i) {
            expectedInorder << x.at(i) << ' ';
        }

        std::string expectedInorderString = expectedInorder.str();
        expectedInorderString.pop_back();


        EXPECT_EQ(t.inorderString(), expectedInorderString);
    }

    TEST(Two4TreeTest, insert6) {
        Two4Tree<std::string, int> t;
        
        int inputSize = 10;

        std::string x2[inputSize] = {"farm", "cat", "jug", "ant", "epic", "dog", "bog", "idiot", "garbanzo beans", "heat"};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x2[i], y2[i]);
        }
        EXPECT_EQ(t.size(), inputSize);

        std::string inorder = t.inorderString();
        std::string expectedInorder = "ant bog cat dog epic farm garbanzo beans heat idiot jug";

        std::string preorder = t.preorderString();
        std::string expectedPreorder = "cat farm idiot ant bog dog epic garbanzo beans heat jug";

        std::string postorder = t.postorderString();
        std::string expectedPostorder = "ant bog dog epic garbanzo beans heat jug cat farm idiot";

        EXPECT_EQ(inorder, expectedInorder);
        EXPECT_EQ(preorder, expectedPreorder);
        EXPECT_EQ(postorder, expectedPostorder);
    }

    TEST(Two4TreeTest, insert7) {
        Two4Tree<int, int> t;

        int inputSize = 10000;

        int x[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x[i] = i;
        }

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x[i], x[i]);
        }
        EXPECT_EQ(t.size(), inputSize);

        std::ostringstream expectedInorder;

        for (int i = 0; i < inputSize; ++i) {
            expectedInorder << x[i] << ' ';
        }

        std::string expectedInorderString = expectedInorder.str();
        expectedInorderString.pop_back();

        EXPECT_EQ(t.inorderString(), expectedInorderString);
    }

    TEST(Two4TreeTest, insert8) {
// A few 0s are mixed into the 1s section. No 1s are mixed into the 0s section.
        Two4Tree<int, int> t;

        int inputSize = 100000;

        std::vector<int> x;
        std::vector<int> y;

        for (int i = 0; i < inputSize / 2; ++i) {
            x.push_back(0);
            x.push_back(1);
            y.push_back(2 * i);
            y.push_back(2 * i + 1);
        }

        std::random_shuffle(x.begin(), x.end());

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), i);
            t.insert(x.at(i), y.at(i));
        }
        EXPECT_EQ(t.size(), inputSize);

        std::string inorder = t.inorderString();
        std::ostringstream expectedInorder;
        for (int i = 0; i < inputSize / 2; ++i) {
            expectedInorder << 0 << ' ';
        }
        for (int i = 0; i < inputSize / 2; ++i) {
            expectedInorder << 1 << ' ';
        }
        std::string expectedInorderString = expectedInorder.str();
        expectedInorderString.pop_back();

        EXPECT_EQ(inorder, expectedInorderString);
    }

    TEST(Two4TreeTest, predecessor) {
        int inputSize = 10;

        char x2[inputSize] = {'F', 'C', 'J', 'A', 'E', 'D', 'B', 'I', 'G', 'H'};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        Two4Tree<char, int> t(x2, y2, inputSize);

        for (int i = 0; i < inputSize - 1; ++i) {
            EXPECT_EQ(t.predecessor('B' + i), 'A' + i);
        }
    }

    void parentTest(Node<int, int>* topNode) {
        if (topNode->getParent() != nullptr) {
            EXPECT_EQ(topNode->getParent()->getChild(topNode->getParent()->indexOf(topNode)), topNode);
        }

        for (int i = 0; i < topNode->getNumChildren(); ++i) {
            parentTest(topNode->getChild(i));
        }
    }

    TEST(Two4TreeTest, predecessor2) {
        Two4Tree<int, int> t;

        int inputSize = 10000;

        int x[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x[i] = i;
        }

        for (int i = 0; i < inputSize; ++i) {
// std::cout << "i = " << i << std::endl;
            t.insert(x[i], x[i]);
            // parentTest(t.getRoot());
        }

        for (int i = 0; i < inputSize - 1; ++i) {
// std::cout << "i2 = " << i << std::endl;
            EXPECT_EQ(t.predecessor(i + 1), i);
        }
    }

    TEST(Two4TreeTest, successor) {
        int inputSize = 10;

        char x2[inputSize] = {'F', 'C', 'J', 'A', 'E', 'D', 'B', 'I', 'G', 'H'};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        Two4Tree<char, int> t(x2, y2, inputSize);

        for (int i = 0; i < inputSize - 1; ++i) {
            EXPECT_EQ(t.successor('A' + i), 'B' + i);
        }
    }

    TEST(Two4TreeTest, successor2) {
        Two4Tree<int, int> t;

        int inputSize = 10000;

        int x[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x[i] = i;
        }

        for (int i = 0; i < inputSize; ++i) {
            t.insert(x[i], x[i]);
        }
        for (int i = 0; i < inputSize - 1; ++i) {
            EXPECT_EQ(t.successor(i), i + 1);
        }
    }

    TEST(Two4TreeTest, rotate) {
        int inputSize = 4;

        int x2[inputSize] = {1, 2, 3, 0};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        EXPECT_EQ(t.remove(3), 1);
        EXPECT_EQ(t.size(), inputSize - 1);
        // t.remove(3);
        // int x = 5;
        // std::cout << x << std::endl;
    }

    TEST(Two4TreeTest, rotate2) {
        int inputSize = 11;

        int x2[inputSize] = {3, 4, 5, 6, 7, 8, 9, 10, 2, 1, 0};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        EXPECT_EQ(t.remove(7), 1);
        EXPECT_EQ(t.size(), inputSize - 1);
    }

    TEST(Two4TreeTest, rotate3) {
        int inputSize = 10;

        int x2[inputSize];
        int y2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        EXPECT_EQ(t.remove(0), 1);
        EXPECT_EQ(t.size(), inputSize - 1);
        // t.remove(0);
        // int x = 5;
        // std::cout << x << std::endl;
    }

    TEST(Two4TreeTest, shrink) {
        int inputSize = 9;

        int x2[inputSize];
        int y2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        EXPECT_EQ(t.remove(0), 1);
        EXPECT_EQ(t.size(), inputSize - 1);
    }

    TEST(Two4TreeTest, merge) {
        int inputSize = 13;

        int x2[inputSize];
        int y2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        EXPECT_EQ(t.remove(8), 1);
        EXPECT_EQ(t.size(), inputSize - 1);
        // t.remove(8);
        // int x = 5;
        // std::cout << x << std::endl;
    }

    TEST(Two4TreeTest, remove) {
        int inputSize = 10;

        char x2[inputSize] = {'F', 'C', 'J', 'A', 'E', 'D', 'B', 'I', 'G', 'H'};
        int y2[inputSize];
        for (int i = 0; i < inputSize; ++i) {
            y2[i] = i * 10;
        }

        Two4Tree<char, int> t(x2, y2, inputSize);

        EXPECT_EQ(t.remove('Z'), 0);
        EXPECT_EQ(t.remove(x2[0]), 1);
        EXPECT_EQ(t.size(), inputSize - 1);

        // t.remove('F');
        // int x = 5;
        // std::cout << x << std::endl;
    }

    // smallest key removal
    TEST(Two4TreeTest, remove2) {
        int inputSize = 10000;

        int x2[inputSize];
        int y2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), inputSize - i);
            EXPECT_EQ(t.remove(i), 1);
        }
        EXPECT_EQ(t.size(), 0);

        EXPECT_EQ(t.getRoot()->getNumChildren(), 0);
        EXPECT_EQ(t.getRoot()->getNumElements(), 0);
        
    }

    // root removal
    TEST(Two4TreeTest, remove3) {
        int inputSize = 10000;

        int x2[inputSize];
        int y2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), inputSize - i);
            EXPECT_EQ(t.remove(t.getRoot()->getElement(0).key), 1);
        }
        EXPECT_EQ(t.size(), 0);

        EXPECT_EQ(t.getRoot()->getNumChildren(), 0);
        EXPECT_EQ(t.getRoot()->getNumElements(), 0);
    }

    // random removal
    TEST(Two4TreeTest, remove4) {
        int inputSize = 10000;

        std::vector<int> x;

        for (int i = 0; i < inputSize; ++i) {
            x.push_back(i);
        }

        Two4Tree<int, int> t;
        for (int i = 0; i < inputSize; ++i) {
            t.insert(x.at(i), x.at(i));
        }

        std::random_shuffle(x.begin(), x.end());

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.size(), inputSize - i);
            EXPECT_EQ(t.remove(x.at(i)), 1);
        }
        EXPECT_EQ(t.size(), 0);

        EXPECT_EQ(t.getRoot()->getNumChildren(), 0);
        EXPECT_EQ(t.getRoot()->getNumElements(), 0);
    }

    TEST(Two4TreeTest, search) {
        int inputSize = 10000;

        int x2[inputSize];
        int y2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
            y2[i] = i * 10;
        }

        Two4Tree<int, int> t(x2, y2, inputSize);

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(*t.search(x2[i]), y2[i]);
        }
        EXPECT_EQ(t.search(-1), nullptr);
    }

    TEST(Two4TreeTest, select) {
        int inputSize = 10000;

        int x2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
        }

        Two4Tree<int, int> t(x2, x2, inputSize);

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.select(i + 1), x2[i]);
        }
    }

    TEST(Two4TreeTest, rank) {
        int inputSize = 10000;

        int x2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
        }

        Two4Tree<int, int> t(x2, x2, inputSize);

        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.rank(x2[i]), i + 1);
        }
        EXPECT_EQ(t.rank(-1), 0);
    }

    TEST(Two4TreeTest, selectRankSanity) {
        int inputSize = 10000;

        int x2[inputSize];

        for (int i = 0; i < inputSize; ++i) {
            x2[i] = i;
        }

        Two4Tree<int, int> t(x2, x2, inputSize);

        for (int i = 1; i <= inputSize; ++i) {
            EXPECT_EQ(t.rank(t.select(i)), i);
        }
        for (int i = 0; i < inputSize; ++i) {
            EXPECT_EQ(t.select(t.rank(x2[i])), i);
        }
    }
}