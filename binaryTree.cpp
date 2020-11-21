#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>


int dep;

struct Tree {
    struct Node* root;
};

struct Node {
    int n;
    struct Node* left;
    struct Node* right;
};

void printLevel(struct Node* root, int level, int depth)
{
    if (depth < level)
    {
        if (root->left != NULL)
            printLevel(root->left, level, depth + 1);
        if (root->right != NULL)
            printLevel(root->right, level, depth + 1);
    }
    else
    {
        if (root->n != 0)
            printf("%d", root->n); else
            printf(" ");
        int pr = pow(2, dep - level + 1) - 1;
        for (int j = 0; j < pr; j++)
            printf(" ");
    }
}

void makeTree(struct Node* root, int depth)
{
    if (depth < dep)
    {
        if (root->left != NULL)
            makeTree(root->left, depth + 1); else
        {
            root->left = (struct Node*)malloc(sizeof(struct Node));
            root->left->n = 0;
            root->left->left = NULL;
            root->left->right = NULL;
            makeTree(root->left, depth + 1);
        }
        if (root->right != NULL)
            makeTree(root->right, depth + 1); else
        {
            root->right = (struct Node*)malloc(sizeof(struct Node));
            root->right->n = 0;
            root->right->left = NULL;
            root->right->right = NULL;
            makeTree(root->right, depth + 1);
        }
    }
}

void printTree(struct Tree tree)
{

    int i = 0;
    while (i <= dep)
    {
        int pr = pow(2, dep - i);
        for (int j = 0; j < pr; j++)
            printf(" ");
        printLevel(tree.root, i, 0);
        printf("\n");
        i++;
    }
}

int getDepth(struct Node* root, int depth)
{
    int ld;
    int rd;
    if (root->left != NULL)
        ld = getDepth(root->left, depth + 1); else
        ld = depth;
    if (root->right != NULL)
        rd = getDepth(root->right, depth + 1); else
        rd = depth;
    if (ld >= rd) return ld;
    return rd;
}

void add(struct Node* root, int n) 
{
    while (1)
    {
        if (n < root->n) 
            if (root->left != NULL)
            root = root->left; else
            break;
        if (n >= root->n) 
            if (root->right != NULL)
            root = root->right; else
            break;
    }
    if (n < root->n)
    {
        root->left = (struct Node*)malloc(sizeof(struct Node));
        root->left->n = n;
        root->left->left = NULL;
        root->left->right = NULL;
    } else
    {
        root->right = (struct Node*)malloc(sizeof(struct Node));
        root->right->n = n;
        root->right->left = NULL;
        root->right->right = NULL;
    }
}

void find(struct Node* root, int n)
{
    int was = 0;
    if (root->n == n)
    {
        printf("root\n");
        was = 1;
    }
    
    char res[100] = {};
    int k = 0;
    while (1)
    {
        

        if (n < root->n)
            if (root->left != NULL)
            {
                root = root->left;
                res[k] = 'l';
                k++;
                if (root->n == n)
                {
                    printf("%s\n", res);
                    was = 1;
                }
            }
            else
                break;

        

        if (n >= root->n)
            if (root->right != NULL)
            {
                root = root->right;
                res[k] = 'r';
                k++;
                if (root->n == n)
                {
                    printf("%s\n", res);
                    was = 1;
                }
            }
            else
                break;

    }

    if (was == 0)
        printf("No such element!\n");
    
}

void del(struct Tree* tree, int n)
{
    struct Node* root = tree->root;
    struct Node* current = NULL;
    char s = 'n';
    while (1)
    {
        if (n < root->n)
            if (root->left != NULL)
            {
                current = root;
                s = 'l';
                root = root->left;
            }
            else
                break;
        if (n > root->n)
            if (root->right != NULL)
            {
                current = root;
                s = 'r';
                root = root->right;
            }
            else
                break;
        if (n == root->n) break;
    }

    if (n == root->n)
    {
        if (((root->left == NULL) || (root->left->n == 0)) && ((root->right == NULL) || (root->right->n == 0)))
        {
            if (s == 'n')
            {
                root->n = 0;
            }
            if (s == 'l')
            {
                free(current->left);
                current->left = NULL;
            }
            if (s == 'r')
            {
                free(current->right);
                current->right = NULL;
            }
        } else
            if ((((root->left == NULL) || (root->left->n == 0)) && (root->right->n != 0)) ||
                ((root->left->n != 0) && ((root->right == NULL) || (root->right->n == 0))))
            {
                if ((root->left->n != 0) && ((root->right == NULL) || (root->right->n == 0)))
                {
                    if (s == 'n') tree->root = root->left;
                    if (s == 'l') current->left = root->left;
                    if (s == 'r') current->right = root->left;
                    free(root);
                }

                else
                {
                    if (s == 'n') tree->root = root->right;
                    if (s == 'l') current->left = root->right;
                    if (s == 'r') current->right = root->right;
                    free(root);
                }
            }
            else
            {
                struct Node* current1 = root;
                struct Node* root1 = root;
                char s1 = 'r';
                root1 = root1->right;
                while ((root1->left != NULL) && (root1->left->n != 0))
                {
                    s1 = 'l';
                    current1 = root1;
                    root1 = root1->left;
                }

                root->n = root1->n;
                
                    if (s1 == 'l')
                    {
                        current1->left = current1->left->right;
                        free(root1);
                    }

                    if (s1 == 'r')
                    {
                        current1->right = current1->right->right;
                        free(root1);
                    }
                
            }
    }
}

void obhod1(struct Node* root)
{
    printf("%d ", root->n);
    if ((root->left != NULL) && (root->left->n != 0)) obhod1(root->left);
    if ((root->right != NULL) && (root->right->n != 0)) obhod1(root->right); 
}

void obhod2(struct Node* root)
{
    if ((root->left != NULL) && (root->left->n != 0)) obhod1(root->left);
    if ((root->right != NULL) && (root->right->n != 0)) obhod1(root->right);
    printf("%d ", root->n);
}

void obhod3(struct Node* root)
{
    if ((root->left != NULL) && (root->left->n != 0)) obhod1(root->left);
    printf("%d ", root->n);
    if ((root->right != NULL) && (root->right->n != 0)) obhod1(root->right);
}

int main()
{

    struct Tree tree;
    tree.root = (struct Node*)malloc(sizeof(struct Node));
    tree.root->left = NULL;
    tree.root->right = NULL;
    tree.root->n = 0;
    while (1)
    {
        int ch;
        while (getchar() == 0);
        printf("(1) add (2) find (3) delete (4) print (5) 1 (6) 2 (7) 3   ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
            int k = 0;
            while (scanf("%d", &k))
            {
                if (tree.root->n != 0)
                    add(tree.root, k); else
                    tree.root->n = k;
                getchar();
            }
        } break;
        case 2:
        {
            int k = 0;
            while (scanf("%d", &k))
            {
                find(tree.root, k);
                getchar();
            }
        } break;
        case 3:
        {
            int k = 0;
            while (scanf("%d", &k))
            {
                del(&tree, k);
                getchar();
            }
        } break;
        case 4:
        {
            dep = getDepth(tree.root, 0);
            makeTree(tree.root, 0);
            printTree(tree);
        } break;

        case 5:
        {
            obhod1(tree.root);
            printf("\n");
        } break;

        case 6:
        {
            obhod2(tree.root);
            printf("\n");
        } break;

        case 7:
        {
            obhod3(tree.root);
            printf("\n");
        } break;
        }
    }
}