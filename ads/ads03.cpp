// Code guidance from https://www.way2techin.com/2017/01/for-given-expression-eg-bc-def.html

#include <string>
#include <iostream>
using namespace std;
class node;
class ExpressionTree;
const int MAX = 50;

class Stack
{
    int top;
    node *info[MAX];

public:
    Stack()
    {
        top = -1;
    }
    void push(node *cnode)
    {
        top = top + 1;
        info[top] = cnode;
    }
    node *Top()
    {
        return info[top];
    }
    node *pop()
    {
        if (!empty())
        {
            return info[top--];
        }
        return NULL;
    }
    bool empty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }
    bool isFull()
    {
        if (top == MAX - 1)
            return true;
        else
            return false;
    }
};

class node
{
    node *left, *right;
    char data;

public:
    node()
    {
        left = right = NULL;
    }
    node(char ch)
    {
        left = right = NULL;
        data = ch;
    }
    friend class ExpressionTree;
};

class ExpressionTree
{
    node *root;

public:
    ExpressionTree()
    {
        root = NULL;
    }
    void create(string str);
    void in_order_with_recursion(node *rnode);
    void pre_order_with_recurion(node *rnode);
    void post_order_with_recursion(node *rnode);
    void in_order_without_recursion();
    void pre_order_without_recursion();
    void post_order_without_recursion();
    void postorder()
    {
        post_order_with_recursion(root);
    }
    void inorder()
    {
        in_order_with_recursion(root);
    }
    void preorder()
    {
        pre_order_with_recurion(root);
    }
    int priority(char ch);
};
int ExpressionTree::priority(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 0;
        break;
    case '*':
    case '/':
        return 1;
        break;
    case '^':
        return 2;
        break;
    }
    return -1;
}
void ExpressionTree::post_order_without_recursion()
{
    Stack s1;
    node *ptr = root;
    int arr[MAX], i = -1, flag;
LOOP:
    while (ptr != NULL)
    {
        s1.push(ptr);
        arr[++i] = 0;
        if (ptr->right != NULL)
        {
            s1.push(ptr->right);
            arr[++i] = 1;
        }
        ptr = ptr->left;
    }

    ptr = s1.pop();
    flag = arr[i--];
    while (flag == 0 && i >= 0)
    {
        cout << " " << ptr->data;
        ptr = s1.pop();
        flag = arr[i--];
    }
    if (flag == 1 && i >= 0)
    {
        goto LOOP;
    }
    cout << " " << ptr->data;
}

void ExpressionTree::pre_order_without_recursion()
{
    Stack s1;
    node *ptr = root;
    while (ptr != NULL)
    {
        cout << " " << ptr->data;
        if (ptr->right != NULL)
            s1.push(ptr->right);
        if (ptr->left != NULL)
            ptr = ptr->left;
        else
            ptr = s1.pop();
    }
}
void ExpressionTree::in_order_without_recursion()
{
    node *ptr = root;
    Stack s1;
X:
    while (ptr != NULL)
    {
        s1.push(ptr);
        ptr = ptr->left;
    }
    ptr = s1.pop();

    while (ptr != NULL)
    {
        cout << " " << ptr->data;
        if (ptr->right != NULL)
        {
            ptr = ptr->right;
            goto X;
        }
        ptr = s1.pop();
    }
}
void ExpressionTree::in_order_with_recursion(node *rnode)
{
    if (rnode)
    {
        in_order_with_recursion(rnode->left);
        cout << " " << rnode->data;
        in_order_with_recursion(rnode->right);
    }
}
void ExpressionTree::pre_order_with_recurion(node *rnode)
{
    if (rnode)
    {
        cout << " " << rnode->data;
        pre_order_with_recurion(rnode->left);
        pre_order_with_recurion(rnode->right);
    }
}
void ExpressionTree::post_order_with_recursion(node *rnode)
{
    if (rnode)
    {
        post_order_with_recursion(rnode->left);
        post_order_with_recursion(rnode->right);
        cout << " " << rnode->data;
    }
}
void ExpressionTree::create(string str)
{
    Stack s1, s2;
    int i = 0;
    char ch;
    while (str[i] != '\0')
    {

        ch = str[i];
        if (isalpha(ch))
        {
            node *temp = new node(ch);
            s1.push(temp);
        }
        else
        {
            if (s2.empty())
            {
                node *temp = new node(ch);
                s2.push(temp);
            }
            else if (priority(ch) > priority(s2.Top()->data))
            {
                node *temp = new node(ch);
                s2.push(temp);
            }
            else
            {
                while (!s2.empty() && priority(ch) <= priority(s2.Top()->data))
                {
                    node *op = s2.pop();
                    node *rchild = s1.pop();
                    node *lchild = s1.pop();

                    op->right = rchild;
                    op->left = lchild;

                    s1.push(op);
                }
                s2.push(new node(ch));
            }
        }

        i++;
    }
    while (!s2.empty())
    {
        node *op = s2.pop();
        node *rchild = s1.pop();
        node *lchild = s1.pop();

        op->right = rchild;
        op->left = lchild;
        s1.push(op);
    }
    root = s1.pop();
}

int main()
{
    cout << "" << endl;
    ExpressionTree t1;
    string exp = "a-b*c-d/e+f";
    cout << "\n-------------------------------\n| Given Equation: " << exp << " |";

    t1.create(exp);
    cout << "\n---------------------------------------------------------------\n\nInorder Traversal Recursive: \t\t";
    t1.inorder();
    cout << "\n\nInorder Non-Recursive: \t\t\t";
    t1.in_order_without_recursion();
    cout << "\n---------------------------------------------------------------\n\nPreorder Traversal Recursive: \t\t";
    t1.preorder();
    cout << "\n\nPreorder traversal Non-Recursive: \t";
    t1.pre_order_without_recursion();
    cout << "\n---------------------------------------------------------------\n\nPostorder Traversal recursive: \t\t";
    t1.postorder();
    cout << "\n\nPostorder Non-Recursive: \t\t";
    t1.post_order_without_recursion();
    cout << "\n---------------------------------------------------------------\n"
         << endl;
    return 0;
}