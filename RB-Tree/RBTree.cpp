#include "RBTree.h"
#include <iostream>
#include <queue>
/**
 * There are several cases of red-black tree insertion to handle.
 *
 * N is the root node, i,e, first node of red-black tree
 * N's parent(P) is black
 * N's parent(P) and Uncle(U) are red
 * N is added to right of left child of grandparent, or N is added to left of
 * right child of grandparent(P is red and U is black)
 * N is added to left of left child of grandparent, or N is added to right of
 * right child of grandparent(P is red and U is black)
 *
 */
void RBTree::insert(int data) {
    if (m_pRoot == NULL) {
        m_pRoot = new TreeNode(data);
        m_pRoot->m_eColor = BLACK;
        return;
    }
    TreeNode* n = findAndInsert(data, m_pRoot);
    if (n == NULL) // 出现了重复的键
        return;
    insert_case1(n);
}
/**
 * 不允许出现相同的键
 */
TreeNode* RBTree::findAndInsert(int data, TreeNode* root) {
    if (data < root->m_idata && root->m_pLeft == NULL) {
        TreeNode *n = new TreeNode(data);
        n->m_pParent = root;
        root->m_pLeft = n;
        return n;
    } else if (data > root->m_idata && root->m_pRight == NULL) {
        TreeNode *n = new TreeNode(data);
        n->m_pParent = root;
        root->m_pRight = n;
        return n;
    }
    if(data < root->m_idata)
        return findAndInsert(data, root->m_pLeft);
    else if (data > root->m_idata)
        return findAndInsert(data, root->m_pRight);
    return NULL;
}
void RBTree::insert_case1(TreeNode* n) {
    if (n->m_pParent == NULL)
        n->m_eColor = BLACK;
    else
        insert_case2(n);
}
void RBTree::insert_case2(TreeNode* n) {
    if(n->m_pParent->m_eColor == BLACK)
        return;
    else
        insert_case3(n);
}
/**
 * Both parent P and the uncle U are red, the
 */
void RBTree::insert_case3(TreeNode* n) {
    TreeNode* u = n->uncle();
    TreeNode *g;
    if((u != NULL) && (u->m_eColor == RED)) {
        n->m_pParent->m_eColor = BLACK;
        u->m_eColor = BLACK;
        g = n->grandParent();
        if (g != m_pRoot) {
            g->m_eColor = RED;
            insert_case1(g);
        }
    } else {
        insert_case4(n);
    }
}
void RBTree::insert_case4(TreeNode* n) {
    TreeNode *g = n->grandParent();
    if( (n == n->m_pParent->m_pRight) && (n->m_pParent == g->m_pLeft)) {
        rotate_left(n->m_pParent);
    } else if ((n == n->m_pParent->m_pLeft) && (n->m_pParent == g->m_pRight)) {
        rotate_right(n->m_pParent);
    }
    insert_case5(n);
}
void RBTree::insert_case5(TreeNode* n) {
    TreeNode *g = n->grandParent();
    if(n == n->m_pParent->m_pLeft)
        rotate_right(g);
    else
        rotate_left(g);
}
/**
 * @ parm p is for parent node.
 * In this function, Just swap the data, and modify the pointer. And the
 * pointer to N node will always pointer the newer point.
 */
void RBTree::rotate_right(TreeNode* p) {
    TreeNode* n = p->m_pLeft;
    if(n == NULL) return;
    TreeNode* p1 = n->m_pLeft;
    TreeNode* p2 = n->m_pRight;
    TreeNode* p3 = p->m_pRight;
    p->m_pRight = n;
    TreeNode::swap(p, n); // swap key stored in TreeNode
    p->m_pLeft = p1;
    if (p1 != NULL) p1->m_pParent = p;
    n->m_pLeft = p2;
    if (p2 != NULL) p2->m_pParent = n;
    n->m_pRight = p3;
    if (p3 != NULL) p3->m_pParent = n;
}
void RBTree::rotate_left(TreeNode* p /*p for parent */) {
    TreeNode* p1 = p->m_pLeft;
    TreeNode* n = p->m_pRight;
    if(n == NULL)
        return;
    TreeNode* p2 = n->m_pLeft;
    TreeNode* p3 = n->m_pRight;
    p->m_pLeft = n;
    TreeNode::swap(n, p);
    p->m_pRight = p3;
    if (p3 != NULL) p3->m_pParent = p;
    n->m_pRight = p2;
    if (p2 != NULL) p2->m_pParent = n;
    n->m_pLeft = p1;
    if (p1 != NULL) p1->m_pParent = n;
}
void RBTree::travelLevelOrder() {
    using namespace std;
    if (m_pRoot == NULL) {
        return;
    }
    queue<TreeNode*> q;
    q.push(m_pRoot);
    TreeNode::visit(m_pRoot);
    while(!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        if(n->m_pLeft != NULL) {
            q.push(n->m_pLeft);
        }
        TreeNode::visit(n->m_pLeft);
        if(n->m_pRight != NULL) {
            q.push(n->m_pRight);
        }
        TreeNode::visit(n->m_pRight);
    }
    return;
}
/**
 * In a regular binary search tree when deleting a node with two non-leaf
 * children, we find either 
 *  the maximum element in  its left subtree(which is the in-order predecessor) 
 * or
 *  the minimum element in its right subtree(which is the in order successor)
 *  and move its value into the node being deleted.
 *
 */
void RBTree::deleteItem(int data) {
    TreeNode *beDel = findNode(data); // record the data to be deleted.
    if(beDel == NULL) return;
    if(beDel->m_pRight) {
        beDel = findRightMinSwap(beDel);
        deleteOneChild(beDel);
        return;
    } else if(beDel->m_pLeft) {
        beDel = findLeftMaxSwap(beDel);
        deleteOneChild(beDel);
        return;
    } else {
        deleteOneChild(beDel);
    }
}
/**
 * Precondition: beDel has at most one non-leaf child
 * 要删除的节点最多只含有一个非叶节点
 */
void RBTree::deleteOneChild(TreeNode* beDel) {
    TreeNode* child = TreeNode::isLeaf(beDel->m_pRight)?
                      beDel->m_pLeft : beDel->m_pRight;
    TreeNode* p = beDel->m_pParent;
    if(p == NULL) { // 此时只剩下了一个节点, 因此可以直接删除
        delete beDel;
        this->m_pRoot = NULL;
        return;
    }

    if(p->m_pLeft == beDel) p->m_pLeft = child;
    else if (p->m_pRight == beDel) p->m_pRight = child;
    if(child != NULL) child->m_pParent = p;
    if (TreeNode::isBlack(beDel)) {
        if( !TreeNode::isBlack(child) ) {   // Child is red
            child->m_eColor = BLACK;        // 将其涂黑
        } else
            delete_case1(child, p);
    }
    delete beDel;
}
void RBTree::delete_case1(TreeNode* n, TreeNode* p) {
    if (p != NULL) {
        delete_case2(n, p);
    }
}
void RBTree::delete_case2(TreeNode* n, TreeNode* p) {
    TreeNode* s = TreeNode::sibling(n, p);
    assert(s != NULL); // 如果s此时为空, 那么s所在的一边黑色是不足的, 这样的情况不应该存在

    if (s->m_eColor == RED) {
        if (n == p->m_pLeft) {
            rotate_left(p);
        } else {
            rotate_right(p);
        }
        delete_case3(n, s);     // n成为了s指针对象的子节点
    } else {
        delete_case3(n, p);
    }
}
void RBTree::delete_case3(TreeNode* n, TreeNode* p) {
    TreeNode* s = TreeNode::sibling(n, p);
    if( (p->m_eColor == BLACK) &&
            (s != NULL) &&
            (s->m_eColor == BLACK) &&
            TreeNode::isBlack(s->m_pLeft) &&
            TreeNode::isBlack(s->m_pRight) ) {
        s->m_eColor = RED;
        delete_case1(p, p->m_pParent);
    } else
        delete_case4(n, p);
}
void RBTree::delete_case4(TreeNode* n, TreeNode* p) {
    TreeNode * s = TreeNode::sibling(n, p);
    if ((p->m_eColor == RED) &&
            (s->m_eColor == BLACK) &&
            TreeNode::isBlack(s->m_pLeft) &&
            TreeNode::isBlack(s->m_pRight) ) {
        s->m_eColor = RED;
        p->m_eColor = BLACK;
    } else
        delete_case5(n, p);
}
void RBTree::delete_case5(TreeNode* n, TreeNode* p) {
    TreeNode* s = TreeNode::sibling(n, p);
    if (TreeNode::isBlack(s)) {
        if ((n == p->m_pLeft)
                && ! TreeNode::isBlack(s->m_pLeft)
                && TreeNode::isBlack(s->m_pRight)
           ) {
            rotate_right(s);
        } else if (( n == p->m_pRight)
                   && TreeNode::isBlack(s->m_pLeft)
                   && ! TreeNode::isBlack(s->m_pRight)
                  ) {
            rotate_left(s);
        }
    }
    delete_case6(n, p);
}
void RBTree::delete_case6(TreeNode* n, TreeNode* p) {
    TreeNode* s = TreeNode::sibling(n, p);
    if(n == p->m_pLeft) {
        s->m_pRight->m_eColor = BLACK;
        rotate_left(p);
    } else {
        s->m_pLeft->m_eColor = BLACK;
        rotate_right(p);
    }
}
/**
 * 寻找右子树的最小值节点, 将beDel数据与其交换数据, 并返回找到的节点的地址
 * 如果右子树是叶子节点, 可以直接进行返回
 */
TreeNode* RBTree::findRightMinSwap(TreeNode* beDel) {
    TreeNode* rMin = beDel->m_pRight;
    if(TreeNode::isLeaf(rMin)) return beDel;

    while(rMin->m_pLeft)
        rMin = rMin->m_pLeft;
    TreeNode::swap(beDel, rMin);
    return rMin;
}
TreeNode* RBTree::findLeftMaxSwap(TreeNode* beDel) {
    TreeNode* lMax = beDel->m_pLeft;
    if(TreeNode::isLeaf(lMax)) return beDel;
    while(lMax->m_pRight) {
        lMax = lMax->m_pRight;
    }
    TreeNode::swap(beDel, lMax);
    return lMax;
}
TreeNode* RBTree::findNode(int data) {
    return findNodeHelper(data, m_pRoot);
}
TreeNode* RBTree::findNodeHelper(int data, TreeNode* root) {
    if(root == NULL)
        return NULL;
    if(root->m_idata == data) {
        return root;
    } else if (root->m_idata > data) {
        return findNodeHelper(data, root->m_pLeft);
    } else if (root->m_idata < data) {
        return findNodeHelper(data, root->m_pRight);
    }
}
