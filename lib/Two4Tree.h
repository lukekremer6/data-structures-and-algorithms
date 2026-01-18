/*
 * Implements a 2-3-4 tree, also known as a 2-4 tree.
 *
 * A 2-3-4 tree is a self-balancing search tree.
 * It can find, insert, and delete elements in O(log n) time.
 * It's a B-tree of order 4.
*/

#ifndef TWO_4_TREE_H
#define TWO_4_TREE_H

#include "Node.h"
#include <string>
#include <sstream>
#include <array>

template <typename keytype, typename valuetype>
class Two4Tree {
    private:
        Node<keytype, valuetype>* root;
        keytype junk;
        Node<keytype, valuetype>* findNode(Node<keytype, valuetype>* curNode, keytype k);
        Element<keytype, valuetype> & findPredecessor(Node<keytype, valuetype>* curNode, keytype k);
        Element<keytype, valuetype> & goUpPredecessor(Node<keytype, valuetype>* curNode, keytype k);
        Element<keytype, valuetype> & findSuccessor(Node<keytype, valuetype>* curNode, keytype k);
        Element<keytype, valuetype> & goUpSuccessor(Node<keytype, valuetype>* curNode, keytype k);
        Node<keytype, valuetype>* findNextChild(Node<keytype, valuetype>* node, keytype k);
        void insertNonfull(Node<keytype, valuetype>* topNode, keytype k, valuetype v);
        void splitChild(Node<keytype, valuetype>* node, int childIndex);
        void removeUtility(Node<keytype, valuetype>* topNode, keytype k, keytype predecessorKey);
        void shrink();
        bool rotate(Node<keytype, valuetype>* node);
        void merge(Node<keytype, valuetype>* node);
        keytype selectUtility(Node<keytype, valuetype>* topNode, int pos);
        int rankUtility(Node<keytype, valuetype>* curNode, keytype k, int rank);
        std::string preorderStringUtility(Node<keytype, valuetype>* topNode) const;
        std::string inorderStringUtility(Node<keytype, valuetype>* topNode) const;
        std::string postorderStringUtility(Node<keytype, valuetype>* topNode) const;

    public:
        friend void swap(Two4Tree & tree1, Two4Tree & tree2) {
            using std::swap;
            swap(tree1.root, tree2.root);
        }
        Two4Tree();
        Two4Tree(keytype k[], valuetype V[], int s);
        ~Two4Tree();
        Two4Tree(const Two4Tree & oldTree);
        Two4Tree & operator=(Two4Tree oldTree);
        valuetype* search(keytype k);
        void insert(keytype k, valuetype v);
        int remove(keytype k);
        int rank(keytype k);
        keytype select(int pos);
        keytype successor(keytype k);
        keytype predecessor(keytype k);
        int size() const;
        void preorder() const;
        void inorder() const;
        void postorder() const;
        std::string preorderString() const;
        std::string inorderString() const;
        std::string postorderString() const;
        Node<keytype, valuetype>* getRoot() const;
};

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Two4Tree<keytype, valuetype>::findNode(Node<keytype, valuetype>* curNode, keytype k) {
    if (curNode->indexOf(k) != -1) {
        return curNode;
    }

    else if (curNode->getNumChildren() == 0) {
        return nullptr;
    }

    else {
        Node<keytype, valuetype>* nextChild = findNextChild(curNode, k);
        return findNode(nextChild, k);
    }
}

// When you first call this function, curNode should be the node containing k.
template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Two4Tree<keytype, valuetype>::findPredecessor(Node<keytype, valuetype>* curNode, keytype k) {
    if (curNode->getNumChildren() > 0) { // if curNode is an internal node
        if (curNode->indexOf(k) != -1) { // if k is in curNode
            return findPredecessor(curNode->getLeftChildOf(k), k);
        }

        else { // k is not in curNode
            return findPredecessor(curNode->getRightmostChild(), k);
        }
    }

    else { // curNode is a leaf node
        if (curNode->indexOf(k) != -1) { // if k is in curNode
            if (curNode->indexOf(k) > 0) { // There's an element in curNode smaller than k
                return curNode->getElement(curNode->indexOf(k) - 1); // return that element
            }

            else if (curNode->isLeftmostChild()) {
                return goUpPredecessor(curNode, k);
            }

            else {
                return curNode->getLeftParentElement();
            }
        }

        else { // k is not in curNode
            return curNode->getMaximumElement();
        }
    }
}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Two4Tree<keytype, valuetype>::goUpPredecessor(Node<keytype, valuetype>* curNode, keytype k) {
    if (curNode->getParent() != nullptr) {
        if (curNode->isLeftmostChild()) {
            return goUpPredecessor(curNode->getParent(), k);
        }
        else {
            return curNode->getLeftParentElement();
        }
    }

    else {
        std::cout << "Error: key " << k << " is smallest key in tree" << std::endl;
        Node<keytype, valuetype>* originalNode = findNode(root, k);
        return originalNode->getElement(originalNode->indexOf(k));
    }
}

// When you first call this function, curNode should be the node containing k.
template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Two4Tree<keytype, valuetype>::findSuccessor(Node<keytype, valuetype>* curNode, keytype k) {
    if (curNode->getNumChildren() > 0) { // if curNode is an internal node
        if (curNode->indexOf(k) != -1) { // if k is in curNode
            return findSuccessor(curNode->getRightChildOf(k), k);
        }

        else { // k is not in curNode
            return findSuccessor(curNode->getLeftmostChild(), k);
        }
    }

    else { // curNode is a leaf node
        if (curNode->indexOf(k) != -1) { // if k is in curNode
            if (curNode->indexOf(k) < curNode->getNumElements() - 1) { // There's an element in curNode greater than k
                return curNode->getElement(curNode->indexOf(k) + 1); // return that element
            }

            else if (curNode->isRightmostChild()) {
                return goUpSuccessor(curNode, k);
            }

            else {
                return curNode->getRightParentElement();
            }
        }

        else { // k is not in curNode
            return curNode->getMinimumElement();
        }
    }
}

template <typename keytype, typename valuetype>
Element<keytype, valuetype> & Two4Tree<keytype, valuetype>::goUpSuccessor(Node<keytype, valuetype>* curNode, keytype k) {
    if (curNode->getParent() != nullptr) {
        if (curNode->isRightmostChild()) {
            return goUpSuccessor(curNode->getParent(), k);
        }
        else {
            return curNode->getRightParentElement();
        }
    }

    else {
        std::cout << "Error: key " << k << " is largest key in tree" << std::endl;
        Node<keytype, valuetype>* originalNode = findNode(root, k);
        return originalNode->getElement(originalNode->indexOf(k));
    }
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Two4Tree<keytype, valuetype>::findNextChild(Node<keytype, valuetype>* node, keytype k) {
    for (int i = 0; i < node->getNumElements(); ++i) {
        if (k < node->getElement(i).key) {
            return node->getChild(i);
        }
    }

    return node->getChild(node->getNumElements());
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::insertNonfull(Node<keytype, valuetype>* topNode, keytype k, valuetype v) {
    if (topNode->getNumChildren() == 0) {
        topNode->insert(k, v);
        topNode->updateSizeRecursive();
    }

    else {
        Node<keytype, valuetype>* nextChild = findNextChild(topNode, k);
        if (nextChild->getNumElements() == 3) {
            splitChild(topNode, topNode->indexOf(nextChild));
            insertNonfull(topNode, k, v);
        }

        else {
            insertNonfull(nextChild, k, v);
        }
    }
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::splitChild(Node<keytype, valuetype>* node, int childIndex) {
    if (node->getChild(childIndex) == nullptr) {
        throw (std::string) "TSC1";
    }

    else if (node->getChild(childIndex)->getNumElements() != 3) {
        throw (std::string) "TSC2";
    }
    
    else {
        Node<keytype, valuetype>* leftChild = node->getChild(childIndex);
        Node<keytype, valuetype>* rightChild = new Node<keytype, valuetype>;

        node->insert(leftChild->getElement(1));
        rightChild->insert(leftChild->getElement(2));

        leftChild->remove(leftChild->getElement(1));
        leftChild->remove(leftChild->getElement(1));

        if (leftChild->getNumChildren() == 4) {
            Node<keytype, valuetype>* child2Copy = new Node<keytype, valuetype>;
            Node<keytype, valuetype>* child3Copy = new Node<keytype, valuetype>;

            *child2Copy = *(leftChild->getChild(2));
            *child3Copy = *(leftChild->getChild(3));

            rightChild->insert(child2Copy);
            rightChild->insert(child3Copy);

            child2Copy->setParent(rightChild);
            child3Copy->setParent(rightChild);

            leftChild->remove(leftChild->getChild(2));
            leftChild->remove(leftChild->getChild(2));
        }

        node->insert(rightChild);
        rightChild->setParent(node);

        leftChild->updateSize();
        rightChild->updateSize();
    }
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::removeUtility(Node<keytype, valuetype>* topNode, keytype k, keytype predecessorKey) {
    if (topNode->getNumChildren() == 0) {
        topNode->remove(k);
        topNode->updateSizeRecursive();
    }

    else if (topNode->getNumElements() == 1 &&
             topNode->getChild(0)->getNumElements() == 1 &&
             topNode->getChild(1)->getNumElements() == 1) {
        shrink();
        removeUtility(topNode, k, predecessorKey);
    }

    else {
        Node<keytype, valuetype>* nextChild;

        if (topNode->indexOf(predecessorKey) != -1) {
            nextChild = topNode->getLeftChildOf(predecessorKey);
        }

        else {
            nextChild = findNextChild(topNode, k);
        }

        if (nextChild->getNumElements() == 1) {
            if (!rotate(nextChild)) {
                merge(nextChild);
            }
        }

        removeUtility(nextChild, k, predecessorKey);
    }
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::shrink() {
    root->insert(root->getChild(0)->getElement(0));
    root->insert(root->getChild(1)->getElement(0));

    if (root->getChild(0)->getNumChildren() > 0) {
        Node<keytype, valuetype>* child0Copy = new Node<keytype, valuetype>;
        Node<keytype, valuetype>* child1Copy = new Node<keytype, valuetype>;
        Node<keytype, valuetype>* child2Copy = new Node<keytype, valuetype>;
        Node<keytype, valuetype>* child3Copy = new Node<keytype, valuetype>;

        *child0Copy = *(root->getChild(0)->getChild(0));
        *child1Copy = *(root->getChild(0)->getChild(1));
        *child2Copy = *(root->getChild(1)->getChild(0));
        *child3Copy = *(root->getChild(1)->getChild(1));

        root->remove(root->getChild(0));
        root->remove(root->getChild(0));

        root->insert(child0Copy);
        root->insert(child1Copy);
        root->insert(child2Copy);
        root->insert(child3Copy);

        child0Copy->setParent(root);
        child1Copy->setParent(root);
        child2Copy->setParent(root);
        child3Copy->setParent(root);
    }

    else {
        root->remove(root->getChild(0));
        root->remove(root->getChild(0));
    }

    root->updateSize();
}

template <typename keytype, typename valuetype>
bool Two4Tree<keytype, valuetype>::rotate(Node<keytype, valuetype>* node) {
    if (node->getLeftSibling() != nullptr && node->getLeftSibling()->getNumElements() > 1) {
        node->insert(node->getLeftParentElement());
        node->getLeftParentElement() = node->getLeftSibling()->getMaximumElement();
        node->getLeftSibling()->remove(node->getLeftSibling()->getMaximumElement());
        
        if (node->getLeftSibling()->getNumChildren() > 0) {
            Node<keytype, valuetype>* childCopy = new Node<keytype, valuetype>;
            *childCopy = *(node->getLeftSibling()->getRightmostChild());

            node->insert(childCopy);
            childCopy->setParent(node);

            node->getLeftSibling()->remove(node->getLeftSibling()->getRightmostChild());
        }

        node->getLeftSibling()->updateSize();

        return true;
    }

    else if (node->getRightSibling() != nullptr && node->getRightSibling()->getNumElements() > 1) {
        node->insert(node->getRightParentElement());
        node->getRightParentElement() = node->getRightSibling()->getMinimumElement();
        node->getRightSibling()->remove(node->getRightSibling()->getMinimumElement());

        if (node->getRightSibling()->getNumChildren() > 0) {
            Node<keytype, valuetype>* childCopy = new Node<keytype, valuetype>;
            *childCopy = *(node->getRightSibling()->getLeftmostChild());

            node->insert(childCopy);
            childCopy->setParent(node);

            node->getRightSibling()->remove(node->getRightSibling()->getLeftmostChild());
        }

        node->getRightSibling()->updateSize();

        return true;
    }

    else {
        return false;
    }
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::merge(Node<keytype, valuetype>* node) {
    if (node->getLeftSibling() != nullptr) {
        node->insert(node->getLeftSibling()->getElement(0));
        node->insert(node->getLeftParentElement());

        if (node->getLeftSibling()->getNumChildren() > 0) {
            Node<keytype, valuetype>* child0Copy = new Node<keytype, valuetype>;
            Node<keytype, valuetype>* child1Copy = new Node<keytype, valuetype>;

            *child0Copy = *(node->getLeftSibling()->getChild(0));
            *child1Copy = *(node->getLeftSibling()->getChild(1));

            node->insert(child0Copy);
            node->insert(child1Copy);

            child0Copy->setParent(node);
            child1Copy->setParent(node);
        }

        node->getParent()->remove(node->getLeftParentElement());
        node->getParent()->remove(node->getLeftSibling());
    }

    else if (node->getRightSibling() != nullptr) {
        node->insert(node->getRightSibling()->getElement(0));
        node->insert(node->getRightParentElement());

        if (node->getRightSibling()->getNumChildren() > 0) {
            Node<keytype, valuetype>* child0Copy = new Node<keytype, valuetype>;
            Node<keytype, valuetype>* child1Copy = new Node<keytype, valuetype>;

            *child0Copy = *(node->getRightSibling()->getChild(0));
            *child1Copy = *(node->getRightSibling()->getChild(1));

            node->insert(child0Copy);
            node->insert(child1Copy);

            child0Copy->setParent(node);
            child1Copy->setParent(node);
        }

        node->getParent()->remove(node->getRightParentElement());
        node->getParent()->remove(node->getRightSibling());
    }

    else {
        throw (std::string) "TM1";
    }
}

template <typename keytype, typename valuetype>
Two4Tree<keytype, valuetype>::Two4Tree() {
    root = new Node<keytype, valuetype>;
}

template <typename keytype, typename valuetype>
Two4Tree<keytype, valuetype>::Two4Tree(keytype k[], valuetype v[], int s) {
    root = new Node<keytype, valuetype>;
    for (int i = 0; i < s; ++i) {
        this->insert(k[i], v[i]);
    }
}

template <typename keytype, typename valuetype>
Two4Tree<keytype, valuetype>::Two4Tree::~Two4Tree() {
    delete root;
}

template <typename keytype, typename valuetype>
Two4Tree<keytype, valuetype>::Two4Tree(const Two4Tree<keytype, valuetype> & oldTree) {
    root = new Node<keytype, valuetype>;
    *root = *(oldTree.getRoot());
}

template <typename keytype, typename valuetype>
Two4Tree<keytype, valuetype> & Two4Tree<keytype, valuetype>::operator=(Two4Tree<keytype, valuetype> oldTree) {
    swap(*this, oldTree);
    return *this;
}

template <typename keytype, typename valuetype>
valuetype* Two4Tree<keytype, valuetype>::search(keytype k) {
    Node<keytype, valuetype>* node = findNode(root, k);

    if (node == nullptr) {
        return nullptr;
    }
    
    else {
        valuetype* v = &(node->getElement(node->indexOf(k)).value);
        return v;
    }
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::insert(keytype k, valuetype v) {
    if (root->getNumElements() == 3) {
        Node<keytype, valuetype>* newRoot = new Node<keytype, valuetype>;
        newRoot->insert(root);
        root->setParent(newRoot);
        root = newRoot;
        splitChild(root, 0);
    }

    insertNonfull(root, k, v);
}

template <typename keytype, typename valuetype>
int Two4Tree<keytype, valuetype>::remove(keytype k) {
    Node<keytype, valuetype>* nodeToDelete = findNode(root, k);
    if (nodeToDelete == nullptr) {
        return 0;
    }

    else {
        if (nodeToDelete->getNumChildren() > 0) {
            Element<keytype, valuetype> & predecessor = findPredecessor(nodeToDelete, k);
            keytype predecessorKey = predecessor.key;
            std::swap(nodeToDelete->getElement(nodeToDelete->indexOf(k)), predecessor);
            removeUtility(root, k, predecessorKey);
        }

        else {
            removeUtility(root, k, k);
        }

        return 1;
    }
}

template <typename keytype, typename valuetype>
int Two4Tree<keytype, valuetype>::rankUtility(Node<keytype, valuetype>* curNode, keytype k, int rank) {
    if (curNode->getNumChildren() == 0 && curNode->indexOf(k) == -1) {
        return 0;
    }

    else if (curNode->getNumChildren() == 0 && curNode->indexOf(k) != -1) {
        return rank + curNode->indexOf(k);
    }

    else if (curNode->getNumChildren() > 0 && curNode->indexOf(k) == -1) {
        Node<keytype, valuetype>* nextChild = findNextChild(curNode, k);
        for (int i = 0; i < curNode->indexOf(nextChild); ++i) {
            rank += curNode->getChild(i)->getSize() + 1;
        }

        return rankUtility(nextChild, k, rank);
    }

    else { // curNode->getNumChildren() > 0 && curNode->indexOf(k) != -1
        for (int i = 0; i <= curNode->indexOf(k); ++i) {
            rank += curNode->getChild(i)->getSize();
            if (i > 0) {
                ++rank;
            }
        }

        return rank;
    }
}

template <typename keytype, typename valuetype>
int Two4Tree<keytype, valuetype>::rank(keytype k) {
    int rank = 1;
    return rankUtility(root, k, rank);
}

template <typename keytype, typename valuetype>
keytype Two4Tree<keytype, valuetype>::selectUtility(Node<keytype, valuetype>* topNode, int pos) {
    if (pos > topNode->getSize() || pos < 1) {
        std::cout << "Error: pos " << pos << " is out of range" << std::endl;
        return junk;
    }

    else if (topNode->getNumChildren() == 0) {
        return topNode->getElement(pos - 1).key;
    }

    else {
        int comparisonValue = 0;
        int childSize = 0;

        for (int i = 0; i < topNode->getNumElements(); ++i) {
            childSize = topNode->getChild(i)->getSize();
            comparisonValue += childSize;

            if (pos <= comparisonValue) {
                return selectUtility(topNode->getChild(i), pos - comparisonValue + childSize);
            }

            else if (pos == ++comparisonValue) {
                return topNode->getElement(i).key;
            }

            else if (i == topNode->getNumElements() - 1) {
                childSize = topNode->getChild(i + 1)->getSize();
                comparisonValue += childSize;
                return selectUtility(topNode->getChild(i + 1), pos - comparisonValue + childSize);
            }
        }

        throw (std::string) "TSU1";
    }
}

template <typename keytype, typename valuetype>
keytype Two4Tree<keytype, valuetype>::select(int pos) {
    return selectUtility(root, pos);
}

template <typename keytype, typename valuetype>
keytype Two4Tree<keytype, valuetype>::successor(keytype k) {
    return findSuccessor(findNode(root, k), k).key;
}

template <typename keytype, typename valuetype>
keytype Two4Tree<keytype, valuetype>::predecessor(keytype k) {
    return findPredecessor(findNode(root, k), k).key;
}

template <typename keytype, typename valuetype>
int Two4Tree<keytype, valuetype>::size() const {
    return root->getSize();
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::preorder() const {
    std::cout << this->preorderString() << std::endl;
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::inorder() const {
    std::cout << this->inorderString() << std::endl;
}

template <typename keytype, typename valuetype>
void Two4Tree<keytype, valuetype>::postorder() const {
    std::cout << this->postorderString() << std::endl;
}

template <typename keytype, typename valuetype>
std::string Two4Tree<keytype, valuetype>::preorderString() const {
    std::string preorder = preorderStringUtility(root);

    if (!preorder.empty()) {
        preorder.pop_back(); // Removes final space
    }

    return preorder;
}

template <typename keytype, typename valuetype>
std::string Two4Tree<keytype, valuetype>::inorderString() const {
    std::string inorder = inorderStringUtility(root);

    if (!inorder.empty()) {
        inorder.pop_back(); // Removes final space
    }

    return inorder;
}

template <typename keytype, typename valuetype>
std::string Two4Tree<keytype, valuetype>::postorderString() const {
    std::string postorder = postorderStringUtility(root);

    if (!postorder.empty()) {
        postorder.pop_back(); // Removes final space
    }

    return postorder;
}

template <typename keytype, typename valuetype>
std::string Two4Tree<keytype, valuetype>::preorderStringUtility(Node<keytype, valuetype>* topNode) const {
    std::ostringstream preorder;

    for (int i = 0; i < topNode->getNumElements(); ++i) {
        preorder << topNode->getElement(i).key << ' ';
    }

    for (int i = 0; i < topNode->getNumChildren(); ++i) {
        preorder << preorderStringUtility(topNode->getChild(i));
    }

    return preorder.str();
}

template <typename keytype, typename valuetype>
std::string Two4Tree<keytype, valuetype>::inorderStringUtility(Node<keytype, valuetype>* topNode) const {
    std::ostringstream inorder;

    for (int i = 0; i < topNode->getNumElements(); ++i) {
        if (topNode->getNumChildren() > 0) {
            inorder << inorderStringUtility(topNode->getChild(i));
        }

        inorder << topNode->getElement(i).key << ' ';

        if (i == topNode->getNumElements() - 1 && topNode->getNumChildren() > 0) {
            inorder << inorderStringUtility(topNode->getChild(i + 1));
        }
    }

    return inorder.str();
}

template <typename keytype, typename valuetype>
std::string Two4Tree<keytype, valuetype>::postorderStringUtility(Node<keytype, valuetype>* topNode) const {
    std::ostringstream postorder;

    for (int i = 0; i < topNode->getNumChildren(); ++i) {
        postorder << postorderStringUtility(topNode->getChild(i));
    }

    for (int i = 0; i < topNode->getNumElements(); ++i) {
        postorder << topNode->getElement(i).key << ' ';
    }

    return postorder.str();
}

template <typename keytype, typename valuetype>
Node<keytype, valuetype>* Two4Tree<keytype, valuetype>::getRoot() const {
    return root;
}

#endif
