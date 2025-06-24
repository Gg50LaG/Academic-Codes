#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head;

struct node *create(int);
void insert_at_begin(int);
void insert_at_end(int);
void insert_at_position(int, int);
void delete_at_begin();
void delete_at_end();
void delete_at_position(int);
void addAfter(int, int);
void delAfter(int);
void print_list();
int size_of_list();
int getData();
int getPosition();

int main() {
    int afi, afd, choice = 0;
    int data, position;
    while (choice != 10) {
        printf("\n1.Insert in begining 2.Insert at last \n3.Insert at Location 4.Insert After a node");
        printf("\n5.Delete at beginning 6.Delete at end \n7.Delete at Location 8. Delete after a given node");
        printf("\n9.Display 10.Exit");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Inserting a node at beginning");
                data = getData();
                insert_at_begin(data);
                print_list();
                break;
            case 2:
                printf("Inserting a node at end");
                data = getData();
                insert_at_end(data);
                print_list();
                break;
            case 3:
                printf("Inserting a node at the given position");
                data = getData();
                position = getPosition();
                insert_at_position(position, data);
                print_list();
                break;
            case 4:
                printf("Insert a node after a given node(1st node)");
                printf("\nEnter the 1st node ");
                scanf("%d", &afi);
                data = getData();
                addAfter(data, afi);
                print_list();
                break;
            case 5:
                printf("Deleting a node from beginning");
                delete_at_begin();
                print_list();
                break;
            case 6:
                printf("\nDeleting a node from end");
                delete_at_end();
                print_list();
                break;
            case 7:
                printf("\nDelete a node from given position");
                position = getPosition();
                delete_at_position(position);
                print_list();
                break;
            case 8:
                printf("Delete a node after a given node(1st node)");
                printf("\nEnter the 1st node ");
                scanf("%d", &afd);
                delAfter(afd);
                print_list();
                break;
            case 9:
                print_list();
                break;
            case 10:
                printf("\nProgram was terminated\n\n");
                return 0;
            default:
                printf("\nInvalid Choice\n");
        }
    }
    return 0;
}

struct node *create(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("\nMemory can't be allocated.\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void addAfter(int data, int afi) {
    struct node *new_node = create(data);
    struct node *p;
    new_node->data = data;
    if (new_node != NULL) {
        if (head == NULL) {
            head = new_node;
            new_node->next = head;
            return;
        } else {
            p = head->next;
            while (p->data != afi && p->next != head)
                p = p->next;
            new_node->next = p->next;
            p->next = new_node;
        }
    }
    return;
}

void delAfter(int afd) {
    struct node *p = head;
    struct node *temp;
    if (head == NULL) {
        printf("\nEMPTY LIST");
        return;
    } else {
        p = head;
        while (p->next != head) {
            if (p->next->data != afd) {
                temp = p->next;
                p->next = p->next->next;
                free(temp);
                break;
            } else
                p = p->next;
        }
    }
}

void insert_at_begin(int data) {
    struct node *new_node = create(data);
    if (new_node != NULL) {
        struct node *last = head;
        if (head == NULL) {
            head = new_node;
            new_node->next = head;
            return;
        }
        while (last->next != head) {
            last = last->next;
        }
        last->next = new_node;
        new_node->next = head;
        head = new_node;
    }
}

void insert_at_end(int data) {
    struct node *new_node = create(data);
    if (new_node != NULL) {
        if (head == NULL) {
            head = new_node;
            new_node->next = head;
            return;
        }
        struct node *last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = new_node;
        new_node->next = head;
    }
}

void insert_at_position(int position, int data) {
    if (position <= 0) {
        printf("\nInvalid Position");
    } else if (head == NULL && position > 1) {
        printf("\nInvalid Position");
    } else if (head != NULL && position > size_of_list()) {
        printf("\nInvalid Position");
    } else if (position == 1) {
        insert_at_begin(data);
    } else {
        struct node *new_node = create(data);
        if (new_node != NULL) {
            struct node *temp = head, *prev = NULL;
            int i = 1;
            while (++i <= position) {
                prev = temp;
                temp = temp->next;
            }
            prev->next = new_node;
            new_node->next = temp;
        }
    }
}

void delete_at_begin() {
    if (head == NULL) {
        printf("\nEMPTY LIST");
        return;
    }
    struct node *last = head;
    struct node *temp = head;
    if (last->next == head) {
        free(last);
        head = NULL;
        return;
    }
    while (last->next != head)
        last = last->next;
    head = head->next;
    last->next = head;
    free(temp);
    temp = NULL;
}

void delete_at_end() {
    if (head == NULL) {
        printf("\nEMPTY LIST");
        return;
    }
    struct node *prev = head;
    struct node *temp = head->next;
    if (prev->next == head) {
        free(prev);
        head = NULL;
        return;
    }
    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = head;
    free(temp);
    temp = NULL;
}

void delete_at_position(int position) {
    if (position <= 0)
        printf("\nInvalid Position");
    else if (position > size_of_list())
        printf("\n Invalid position \n");
    else if (position == 1)
        delete_at_begin();
    else if (position == size_of_list())
        delete_at_end();
    else {
        struct node *temp = head;
        struct node *prev = NULL;
        int i = 1;
        while (i < position) {
            prev = temp;
            temp = temp->next;
            i += 1;
        }
        prev->next = temp->next;
        free(temp);
        temp = NULL;
    }
}

void print_list() {
    struct node *temp = head;
    if (head == NULL) {
        printf("\nEMPTY LIST");
        return;
    }
    printf("\nELEMENTS IN LIST\n");
    do {
        printf("%d\t", temp->data);
        temp = temp->next;
    } while (temp != head);
}

int size_of_list() {
    if (head == NULL)
        return 0;
    struct node *temp = head;
    int count = 1;
    while (temp->next != head) {
        count += 1;
        temp = temp->next;
    }
    return count;
}

int getData() {
    int data;
    printf("\nEnter Data: ");
    scanf("%d", &data);
    return data;
}

int getPosition() {
    int pos;
    printf("\nEnter Position: ");
    scanf("%d", &pos);
    return pos;
}
