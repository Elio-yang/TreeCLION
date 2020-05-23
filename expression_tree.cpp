/*
    We build a tree like this :
                        +
                       / \
                      +   *
                     / \  | \
                    a   * d  e
                       /  \
                      b    c
        @pre_order traversal  :++a*bc*de
        root-->left_child-->right_child
        @in_order  traversal  :(a+(b*c))+(d*e)
        left_child-->root-->right_child
        @posy_order traversal :abc*+de*+
        left_child-->right_child-->root
    Programming to make a post_order expression to an expression tree
    and give the in_order and pre_order traversal.
 */

#include <cstdlib>
#include <iostream>

//Tree part
typedef struct ExpressionTree Tree;
typedef Tree *PtrTree;
typedef char ElementType;

//Stack part
typedef struct StackNode Stack;
typedef Stack *PtrStack;

//Definition
struct ExpressionTree {
    ElementType val;
    PtrTree left;
    PtrTree right;
};

struct StackNode {
    PtrTree data;
    PtrStack next;
};

//Method: Create Tree and give traversals
PtrTree CreatTree();

void inOrderTraversal(PtrTree T);

void postOrderTraversal(PtrTree T);

void preOrderTraversal(PtrTree T);

//Method:Create stack ,push,pop
PtrStack CreateStack();

void push(PtrTree T, PtrStack S);

PtrTree pop(PtrStack S);

extern void WriteLog(const char *szFile, int nLine, const char *szFunc, const char *szFmt, ...);

int main() {
    PtrTree T;
    T = CreatTree();

    std::cout << "postOrderTraversal is:";
    postOrderTraversal(T);
    std::cout << std::endl;

    std::cout << "inOrderTraversal is:";
    inOrderTraversal(T);
    std::cout << std::endl;

    std::cout << "postOrderTraversal is:";
    postOrderTraversal(T);
    std::cout << std::endl;

    return 0;
}

PtrTree CreatTree() {
    ElementType data;
    PtrTree T;
    PtrStack S = CreateStack();
    std::cout << "Enter postOrder expression:(# to end)";
    while (std::cin >> data) {
        if (data == '#') {
            break;
        }
        if ('a' <= data & data <= 'z') {
            T = (PtrTree) malloc(sizeof(Tree));
            if (T == nullptr) {
                WriteLog(__FILE__, __LINE__, __FUNCTION__, "ERROR:%s", "MALLOC FAILURE");
                exit(-1);
            }
            T->val = data;
            T->left = nullptr;
            T->right = nullptr;
            push(T, S);
        } else {
            T = (PtrTree) malloc(sizeof(Tree));
            if (T == nullptr) {
                WriteLog(__FILE__, __LINE__, __FUNCTION__, "ERROR:%s", "MALLOC FAILURE");
                exit(-1);
            }
            T->val = data;
            T->left = pop(S);
            T->right = pop(S);
            push(T, S);
        }
    }
    return pop(S);
}

void inOrderTraversal(PtrTree T) {
    if (T) {
        if (T->left) {
            std::cout << '(';
        }
        inOrderTraversal(T->left);
        std::cout << T->val;
        inOrderTraversal(T->right);
        if (T->right) {
            std::cout << ')';
        }
    }
}

void postOrderTraversal(PtrTree T) {
    if (T) {
        postOrderTraversal(T->left);
        postOrderTraversal(T->right);
        std::cout << T->val;
    }
}

void preOrderTraversal(PtrTree T) {
    if (T) {
        std::cout << T->val;
        preOrderTraversal(T->left);
        preOrderTraversal(T->right);
    }
}

PtrStack CreateStack() {
    auto P = (PtrStack) malloc(sizeof(Stack));
    if (P) {
        P->next = nullptr;
        return P;
    } else {
        WriteLog(__FILE__, __LINE__, __FUNCTION__, "ERROR:%s", "MALLOC FAILURE");
        exit(-1);
    }
}

void push(PtrTree T, PtrStack S) {
    auto tmp = (PtrStack) malloc(sizeof(Stack));
    if (tmp == nullptr) {
        WriteLog(__FILE__, __LINE__, __FUNCTION__, "ERROR:%s", "MALLOC FAILURE");
        exit(-1);
    }
    tmp->data = T;
    tmp->next = S->next;
    S->next = tmp;
}

PtrTree pop(PtrStack S) {
    auto tmp = (PtrStack) malloc(sizeof(Stack));
    if (tmp == nullptr) {
        WriteLog(__FILE__, __LINE__, __FUNCTION__, "ERROR:%S", "MALLOC FAILURE");
        exit(-1);
    }
    auto T = (PtrTree) malloc(sizeof(Tree));
    if (T == nullptr) {
        WriteLog(__FILE__, __LINE__, __FUNCTION__, "ERROR:%S", "MALLOC FAILURE");
        exit(-1);
    }
    tmp = S->next;
    S->next = S->next->next;

    T->val = tmp->data->val;
    T->left = tmp->data->left;
    T->right = tmp->data->right;
    free(tmp);
    return T;
}
