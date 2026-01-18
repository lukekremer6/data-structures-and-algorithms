#include "Node.h"
#include "Element.h"
#include <gtest/gtest.h>
#include <string>


namespace {
    TEST(NodeTest, defaultConstructor) {
        Node<char, int> n;

        EXPECT_EQ(n.getNumElements(), 0);
        EXPECT_EQ(n.getNumChildren(), 0);
        EXPECT_THROW(n.getElement(0), std::string);
        EXPECT_THROW(n.getElement(2), std::string);
        EXPECT_EQ(n.getChild(0), nullptr);
        EXPECT_EQ(n.getChild(3), nullptr);
        EXPECT_EQ(n.getParent(), nullptr);

        Node<std::string, int> n2;

        EXPECT_EQ(n2.getNumElements(), 0);
        EXPECT_EQ(n2.getNumChildren(), 0);
        EXPECT_THROW(n2.getElement(1), std::string);
        EXPECT_EQ(n2.getChild(2), nullptr);
        EXPECT_EQ(n2.getParent(), nullptr);
    }

    TEST(NodeTest, insertionConstructor) {
        std::string x = "hello";
        char y = '$';
        Node<std::string, char> n(x, y);

        EXPECT_EQ(n.getNumElements(), 1);
        EXPECT_EQ(n.getNumChildren(), 0);
        EXPECT_EQ(n.getElement(0).key, x);
        EXPECT_EQ(n.getElement(0).value, y);
        EXPECT_THROW(n.getElement(1), std::string);
        EXPECT_EQ(n.getChild(0), nullptr);
        EXPECT_EQ(n.getParent(), nullptr);

        char x2 = 'A';
        int y2 = 33;
        Node<char, int> n2(x2, y2);

        EXPECT_EQ(n2.getNumElements(), 1);
        EXPECT_EQ(n2.getNumChildren(), 0);
        EXPECT_EQ(n2.getElement(0).key, x2);
        EXPECT_EQ(n2.getElement(0).value, y2);
        EXPECT_THROW(n2.getElement(1), std::string);
        EXPECT_EQ(n2.getChild(0), nullptr);
        EXPECT_EQ(n2.getParent(), nullptr);
    }

    TEST(NodeTest, copyConstructor) {
        char x = 'M';
        int y = 10;

        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        char x3[3] = {'X', 'Y', 'Z'};
        int y3[3] = {10, 20, 30};

        Node<char, int> n1;
        Node<char, int>* n2 = new Node<char, int>;
        Node<char, int>* n3 = new Node<char, int>;

        n1.insert(x, y);

        for (int i = 0; i < 3; ++i) {
            n2->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n3->insert(x3[i], y3[i]);
        }

        n1.insert(n2);
        n1.insert(n3);
        
        Node<char, int> n4(n1);

        EXPECT_EQ(n1.getParent(), n4.getParent());
        EXPECT_EQ(n1.getNumChildren(), n4.getNumChildren());

        EXPECT_EQ(n1.getElement(0).key, n4.getElement(0).key);
        EXPECT_EQ(n1.getChild(0)->getElement(1).key, n4.getChild(0)->getElement(1).key);
        EXPECT_EQ(n1.getChild(1)->getElement(2).key, n4.getChild(1)->getElement(2).key);


        EXPECT_NE(n1.getChild(0), n4.getChild(0));
        n1.remove(n3);
        
        EXPECT_NO_THROW(n4.getChild(1));
    }

    TEST(NodeTest, copyAssignmentOperator) {
        char x = 'M';
        int y = 10;

        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        char x3[3] = {'X', 'Y', 'Z'};
        int y3[3] = {10, 20, 30};

        Node<char, int> n1;
        Node<char, int>* n2 = new Node<char, int>;
        Node<char, int>* n3 = new Node<char, int>;

        n1.insert(x, y);

        for (int i = 0; i < 3; ++i) {
            n2->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n3->insert(x3[i], y3[i]);
        }

        n1.insert(n2);
        n1.insert(n3);

        Node<char, int> n4 = n1;
        EXPECT_EQ(n1.getParent(), n4.getParent());
        EXPECT_EQ(n1.getNumChildren(), n4.getNumChildren());
        
        EXPECT_EQ(n1.getElement(0).key, n4.getElement(0).key);
        EXPECT_EQ(n1.getChild(0)->getElement(1).key, n4.getChild(0)->getElement(1).key);
        EXPECT_EQ(n1.getChild(1)->getElement(2).key, n4.getChild(1)->getElement(2).key);

        EXPECT_NE(n1.getChild(0), n4.getChild(0));
        n1.remove(n3);
        EXPECT_NO_THROW(n4.getChild(1));
    }

    TEST(NodeTest, insertKeyValue) {
        std::string x[3] = {"hello", "apple", "tree"};
        char y[3] = {'$', 'z', '*'};
        Node<std::string, char> n;
        for (int i = 0; i < 3; ++i) {
            n.insert(x[i], y[i]);
        }

        EXPECT_EQ(n.getNumElements(), 3);
        EXPECT_EQ(n.getNumChildren(), 0);
        EXPECT_EQ(n.getElement(0).key, x[1]);
        EXPECT_EQ(n.getElement(0).value, y[1]);
        EXPECT_EQ(n.getElement(1).key, x[0]);
        EXPECT_EQ(n.getElement(1).value, y[0]);
        EXPECT_EQ(n.getElement(2).key, x[2]);
        EXPECT_EQ(n.getElement(2).value, y[2]);
        EXPECT_THROW(n.getElement(3), std::string);
        EXPECT_EQ(n.getChild(0), nullptr);
        EXPECT_EQ(n.getParent(), nullptr);
    }

    TEST(NodeTest, indexOfKey) {
        Node<char, int> n;
        char x[3] = {'A', 'B', 'C'};
        int y[3] = {10, 20, 30};

        EXPECT_EQ(n.indexOf(x[0]), -1);
        EXPECT_EQ(n.indexOf(x[1]), -1);
        EXPECT_EQ(n.indexOf(x[2]), -1);

        for (int i = 0; i < 3; ++i) {
            n.insert(x[i], y[i]);
        }
        
        EXPECT_EQ(n.indexOf(x[0]), 0);
        EXPECT_EQ(n.indexOf(x[1]), 1);
        EXPECT_EQ(n.indexOf(x[2]), 2);
    }

    TEST(NodeTest, removeKey) {
        Node<char, int> n;
        char x[3] = {'A', 'B', 'C'};
        int y[3] = {10, 20, 30};

        EXPECT_THROW(n.remove(x[0]), std::string);
        try {
            n.remove(x[0]);
        }
        catch(std::string e) {
            EXPECT_EQ(e, "NRE2");
        }

        n.insert(x[0], y[0]);

        for (int i = 1; i < 3; ++i) {
            n.insert(x[i], y[i]);
        }

        EXPECT_THROW(n.remove('D'), std::string);
        try {
            n.remove('D');
        }
        catch(std::string e) {
            EXPECT_EQ(e, "NRE3");
        }

        n.remove(x[0]);
        EXPECT_EQ(n.getElement(0).key, x[1]);
        EXPECT_THROW(n.remove(x[0]), std::string);
        try {
            n.remove(x[0]);
        }
        catch(std::string e) {
            EXPECT_EQ(e, "NRE3");
        }

        n.insert(x[0], y[0]);
        n.remove(x[1]);
        EXPECT_EQ(n.getElement(1).key, x[2]);

        n.insert(x[1], y[1]);
        n.remove(x[2]);
        EXPECT_THROW(n.getElement(2), std::string);
        try {
            n.getElement(2);
        }
        catch(std::string e) {
            EXPECT_EQ(e, "NGE1");
        }
    }

    TEST(NodeTest, insertChild) {
        char x = 'M';
        int y = 10;

        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        char x3[3] = {'X', 'Y', 'Z'};
        int y3[3] = {10, 20, 30};

        Node<char, int> n(x, y);
        Node<char, int>* n2 = new Node<char, int>;
        Node<char, int>* n3 = new Node<char, int>;
        Node<char, int> n4(x, y);
        Node<char, int>* n5 = new Node<char, int>;
        Node<char, int>* n6 = new Node<char, int>;

        for (int i = 0; i < 3; ++i) {
            n2->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n3->insert(x3[i], y3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n5->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n6->insert(x3[i], y3[i]);
        }

        n.insert(n2);
        n.insert(n3);

        EXPECT_EQ(n.getChild(0), n2);
        EXPECT_EQ(n.getChild(1), n3);
        EXPECT_EQ(n.getNumChildren(), 2);
        EXPECT_EQ(n.getChild(0)->getElement(0).key, 'A');
        EXPECT_EQ(n.getChild(1)->getElement(2).key, 'Z');
        EXPECT_EQ(n.getChild(0)->getNumChildren(), 0);

        n4.insert(n6);
        n4.insert(n5);

        EXPECT_EQ(n4.getChild(0), n5);
        EXPECT_EQ(n4.getChild(1), n6);
        EXPECT_EQ(n4.getNumChildren(), 2);
        EXPECT_EQ(n4.getChild(0)->getElement(0).key, 'A');
        EXPECT_EQ(n4.getChild(1)->getElement(2).key, 'Z');
        EXPECT_EQ(n4.getChild(0)->getNumChildren(), 0);
    }

    TEST(NodeTest, indexOfChild) {
        char x = 'M';
        int y = 10;

        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        char x3[3] = {'X', 'Y', 'Z'};
        int y3[3] = {10, 20, 30};

        Node<char, int>* n1 = new Node<char, int>;
        Node<char, int>* n2 = new Node<char, int>;
        Node<char, int>* n3 = new Node<char, int>;
        Node<char, int>* n4 = new Node<char, int>;
        Node<char, int>* n5 = new Node<char, int>;
        Node<char, int>* n6 = new Node<char, int>;

        n1->insert(x, y);
        n4->insert(x, y);

        for (int i = 0; i < 3; ++i) {
            n2->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n3->insert(x3[i], y3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n5->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n6->insert(x3[i], y3[i]);
        }

        n1->insert(n2);
        n1->insert(n3);

        n4->insert(n6);
        n4->insert(n5);

        EXPECT_EQ(n1->indexOf(n2), 0);
        EXPECT_EQ(n1->indexOf(n3), 1);
        EXPECT_EQ(n1->indexOf(n4), -1);

        EXPECT_EQ(n4->indexOf(n5), 0);
        EXPECT_EQ(n4->indexOf(n6), 1);
        EXPECT_EQ(n4->indexOf(n1), -1);
    }

    TEST(NodeTest, removeChild) {
        char x = 'M';
        int y = 10;

        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        char x3[3] = {'X', 'Y', 'Z'};
        int y3[3] = {10, 20, 30};

        Node<char, int>* n1 = new Node<char, int>;
        Node<char, int>* n2 = new Node<char, int>;
        Node<char, int>* n3 = new Node<char, int>;
        Node<char, int>* n4 = new Node<char, int>;
        Node<char, int>* n5 = new Node<char, int>;
        Node<char, int>* n6 = new Node<char, int>;

        n1->insert(x, y);
        n4->insert(x, y);

        for (int i = 0; i < 3; ++i) {
            n2->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n3->insert(x3[i], y3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n5->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n6->insert(x3[i], y3[i]);
        }

        EXPECT_THROW(n1->remove(n2), std::string);
    
        n1->insert(n2);
        n1->insert(n3);

        EXPECT_EQ(n1->getChild(0), n2);
        EXPECT_EQ(n1->getChild(1), n3);
        EXPECT_EQ(n1->getChild(0)->getElement(0).key, n2->getElement(0).key);
        EXPECT_EQ(n1->getChild(1)->getElement(0).key, n3->getElement(0).key);

        n4->insert(n6);
        n4->insert(n5);

        EXPECT_THROW(n1->remove(n4), std::string);

        n1->remove(n2);

        EXPECT_EQ(n1->getChild(0), n3);
        EXPECT_EQ(n1->getChild(0)->getElement(0).key, n3->getElement(0).key);
        EXPECT_THROW(n1->remove(n2), std::string);
    }

    TEST(NodeTest, getChildVariations) {
        char x = 'M';
        int y = 10;

        char x2[3] = {'A', 'B', 'C'};
        int y2[3] = {10, 20, 30};

        char x3[3] = {'X', 'Y', 'Z'};
        int y3[3] = {10, 20, 30};

        Node<char, int>* n1 = new Node<char, int>;
        Node<char, int>* n2 = new Node<char, int>;
        Node<char, int>* n3 = new Node<char, int>;

        n1->insert(x, y);

        for (int i = 0; i < 3; ++i) {
            n2->insert(x2[i], y2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            n3->insert(x3[i], y3[i]);
        }

        n1->insert(n2);
        n1->insert(n3);
        
        n2->setParent(n1);
        n3->setParent(n1);

        EXPECT_EQ(n1->getLeftmostChild(), n2);
        EXPECT_EQ(n1->getRightmostChild(), n3);

        EXPECT_TRUE(n2->isLeftmostChild());
        EXPECT_TRUE(n3->isRightmostChild());

        EXPECT_EQ(n1->getLeftChildOf('M'), n2);
        EXPECT_EQ(n1->getRightChildOf('M'), n3);

        EXPECT_EQ(n2->getRightParentElement().key, 'M');
        EXPECT_EQ(n3->getLeftParentElement().key, 'M');
    }
}
