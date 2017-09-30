
#ifndef RBTREE_H_
#define RBTREE_H_
#include <iostream>
#include <assert.h>

#define ASSERT(state) do { \
\
} while(0)

enum Color {
    RED, BLACK
};

struct TreeNode {
public:
    TreeNode() {
        m_eColor = RED;
        m_pLeft = NULL;
        m_pRight = NULL;
        m_pRight = NULL;
        m_pParent = NULL;
    }
    TreeNode(int data) {
        m_idata = data;
        m_eColor = RED;
        m_pLeft = NULL;
        m_pParent = NULL;
        m_pRight = NULL;
        m_pRight = NULL;
    }
    int m_idata;
    Color m_eColor;
    TreeNode *m_pLeft;
    TreeNode *m_pRight;
    TreeNode *m_pParent;
    TreeNode* grandParent() {
        if (m_pParent != NULL)
            return m_pParent->m_pParent;
        else
            return NULL;
    }
    TreeNode *uncle() {
        TreeNode* g = grandParent();
        if (g == NULL) {
            return NULL;
        }
        if (m_pParent == g->m_pLeft)
            return g->m_pRight;
        else
            return g->m_pLeft;
    }
    static TreeNode* sibling(TreeNode* n, TreeNode* p) {
        if(p == NULL) return NULL;
        if(p->m_pLeft == n) return p->m_pRight;
        else if (p->m_pRight == n) return p->m_pLeft;
    }
    // 当节点为黑色或是叶子节点时返回true
    static bool isBlack(TreeNode *n) {
        if (n == NULL) return true;
        return n->m_eColor == BLACK;
    }
    // 在红黑树中, 叶子节点指的是为最底层的为NULL的点, 并不是两个子节点都为NULL的点
    static bool isLeaf(TreeNode *n) {
        return n == NULL;
    }
    static void swap(TreeNode* n1, TreeNode* n2) {
        int data = n1->m_idata;
        n1->m_idata = n2->m_idata;
        n2->m_idata = data;
    }
    static void visit(TreeNode* n) { // 访问这个节点
        using std::cout;
        if(n == NULL) {
            cout << "NULL, ";
        } else {
            if(n->m_eColor == RED)
                cout << "\33[31m";  // For red
            else
                cout << "\33[38m";

            cout << n->m_idata << ", ";

            cout << "\33[0m";   // clear last color
        }
    }
};

/**
 * In addition to the requirements imposed on a binary search tree the following
 * must be satisfied by a red-black tree;
 * 1. Each node is either red or black.
 * 2. The root is black. This rule is sometimes omitted. Since the root can
 * always be changed from red to black.
 * 3. All leaves (NIL) are black.
 * 4. If a node is red, then both its children are black.
 * 5. Every path from a given node to any of its descendant NIL nodes
 * contains the same number of black nodes. Some definitions: the number
 * of black nodes from root to a node is the node's black depth; the uniform
 * number of black nodes in all paths from root to the leaves is called
 * the black-height of the right-black tree.
 */
class RBTree {
public:
    RBTree() {
        m_pRoot = NULL;
    }
    RBTree(int data) {
        m_pRoot = new TreeNode;
        m_pRoot->m_idata = data;
        m_pRoot->m_eColor = BLACK;
    }
    void insert(int data);
    void deleteItem(int data);
    TreeNode* findNode(int data);
    TreeNode* findNodeHelper(int data, TreeNode* root);
    void treeClear(TreeNode* root) {
        if (root == NULL)
            return;
        treeClear(root->m_pLeft);
        treeClear(root->m_pRight);
        root = NULL;
        delete root;
    }
    void travelInOrder() {
        inOrder(m_pRoot);
    }
    void travelLevelOrder();
    ~RBTree() {
        treeClear(m_pRoot);
    }
private:
    TreeNode* m_pRoot;
    TreeNode* findAndInsert(int data, TreeNode* root);
    void deleteOneChild(TreeNode* beDel);
    TreeNode* findRightMinSwap(TreeNode* beDel);
    TreeNode* findLeftMaxSwap(TreeNode* beDel);
    void safeDelete(TreeNode* p, TreeNode* n) {
// ASSERT
        if(n->m_pParent != p) exit(1);
        if (n->m_pRight != NULL || n->m_pRight != NULL) {
            return;
        }
        if(p->m_pLeft == n) {
            p->m_pLeft = NULL;
        } else {
            p->m_pRight = NULL;
        }
        delete n; // 不能使用treeClear函数
    }
    void inOrder(TreeNode* root) {
        if(root == NULL) return;
        inOrder(root->m_pLeft);
        TreeNode::visit(root);
        inOrder(root->m_pRight);
    }
    void backOrder(TreeNode* root) {
        if(root == NULL) return;
        inOrder(root->m_pLeft);
        inOrder(root->m_pRight);
        TreeNode::visit(root);
    }
    void frontOrder(TreeNode* root) {
        if(root == NULL) return;
        TreeNode::visit(root);
        inOrder(root->m_pLeft);
        inOrder(root->m_pRight);
    }
    void rotate_left(TreeNode* root);
    void rotate_right(TreeNode* root);
    void insert_case1(TreeNode* n);
    void insert_case2(TreeNode* n);
    void insert_case3(TreeNode* n);
    void insert_case4(TreeNode* n);
    void insert_case5(TreeNode* n);
    void delete_case1(TreeNode* n, TreeNode* p);
    void delete_case2(TreeNode* n, TreeNode* p);
    void delete_case3(TreeNode* n, TreeNode* p);
    void delete_case4(TreeNode* n, TreeNode* p);
    void delete_case5(TreeNode* n, TreeNode* p);
    void delete_case6(TreeNode* n, TreeNode* p);
};
#endif

