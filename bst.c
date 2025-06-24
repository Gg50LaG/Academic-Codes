#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *l, *r;
};

struct node *newnode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->l = temp->r = NULL;
    return temp;
}

struct node *minvalue(struct node *node) {
    struct node *p = node;
    while (p && p->l != NULL)
        p = p->l;
    return p;
}

struct node *insert(struct node *node, int key) {
    if (node == NULL)
        return newnode(key);
    if (key < node->key)
        node->l = insert(node->l, key);
    else if (key > node->key)
        node->r = insert(node->r, key);
    return node;
}

struct node *deleten(struct node *root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->l = deleten(root->l, key);
    else if (key > root->key)
        root->r = deleten(root->r, key);
    else {
        if (root->l == NULL) {
            struct node *temp = root->r;
            free(root);
            return temp;
        } else if (root->r == NULL) {
            struct node *temp = root->l;
            free(root);
            return temp;
        }
        struct node *temp = minvalue(root->r);
        root->key = temp->key;
        root->r = deleten(root->r, temp->key);
    }
    return root;
}

void inorder(struct node *root) {
    if (root == NULL)
        return;
    inorder(root->l);
    printf("%d\t", root->key);
    inorder(root->r);
}

void preorder(struct node *root) {
    if (root == NULL)
        return;
    printf("%d\t", root->key);
    preorder(root->l);
    preorder(root->r);
}

void postorder(struct node *root) {
    if (root == NULL)
        return;
    postorder(root->l);
    postorder(root->r);
    printf("%d\t", root->key);
}

int main() {
    int ele, ch = 1;
    struct node *root = NULL;
    printf("Traversal : Default INORDER");
    while (ch <= 5 && ch > 0) {
        printf("\n1-Insert 2-Delete 3-Inorder 4-Preorder 5-Postorder ");
        printf("\nEnter your choice : ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the element: ");
                scanf("%d", &ele);
                root = insert(root, ele);
                printf("\n");
                inorder(root);
                break;
            case 2:
                printf("\nEnter element to be deleted: ");
                scanf("%d", &ele);
                root = deleten(root, ele);
                printf("\n");
                inorder(root);
                break;
            case 3:
                inorder(root);
                printf("\n");
                break;
            case 4:
                preorder(root);
                printf("\n");
                break;
            case 5:
                postorder(root);
                printf("\n");
                break;
            default:
                printf("\nPROGRAM TERMINATED.");
                break;
        }
    }
}
