#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Creating Node and singly linked list
struct node{
    int coeff;
    int degree;
    struct node* next;
};

typedef struct node Node;

typedef struct{
    Node* head;
    Node* tail;
} singly_linked_list;

void init(singly_linked_list *list){
    list->head = NULL;
    list->tail = NULL;
}

void insert_list(singly_linked_list *list,int coeff,int degree){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->coeff = coeff;
    temp->degree = degree;
    temp->next = NULL;
    if (list->head == NULL){
        list->head = temp;
        list->tail = temp;
    }else{
        list->tail->next = temp;
        list->tail = temp;
    }
}

void print_list(singly_linked_list *list){
    Node *curr = list->head;
    while(curr != NULL){
        printf("%dx^%d",curr->coeff,curr->degree);
        if (curr->next != NULL) {
            printf(" + ");
        }
    curr = curr->next;
    }
    printf("\n");
}

singly_linked_list add(singly_linked_list *l1,singly_linked_list *l2){
    singly_linked_list res;
    init(&res);

    Node *h1 = l1->head,*h2 = l2->head;

    while (h1 != NULL || h2 != NULL) {
        if (h1->degree == h2->degree) {
            insert_list(&res,h1->coeff+h2->coeff,h1->degree);
            h1 = h1->next;
            h2 = h2->next;
        } else if (h1->degree < h2->degree) {
            insert_list(&res,h2->coeff,h2->degree);
            h2 = h2->next;
        } else if (h1->degree > h2->degree) {
            insert_list(&res,h1->coeff,h1->degree);
            h1 = h1->next;
        }
        if (h1 == NULL){
            insert_list(&res,h2->coeff,h2->degree);
            h2 = h2->next;
        }else if (h2 == NULL){
            insert_list(&res,h1->coeff,h1->degree);
            h1 = h1->next;
        }
    }

    return res;
}

singly_linked_list expression_to_linkedList(char *exp){
    singly_linked_list list;
    init(&list);

    char*coeff = (char*)malloc(50);
    char*deg = (char*)malloc(50);
    int c = 0,d=0,coefficient,degree;
    char num = 'c';
    for (int i = 0;; i++) {
        if (exp[i] == 'x') {
            coefficient = stoi(coeff);
            num = 'd';
        } else if (exp[i] == '+' || exp[i] == '\0'){
            degree = stoi(deg);
            num = 'c';
            insert_list(&list,coefficient,degree);
            if (exp[i] == '\0')
                break;
            
        } else if(exp[i] >= 0 && exp[i] <= 9) {
            if (num == 'c'){
                coeff[c++]+=exp[i];
            } else {
                deg[d++]+=exp[i];
            }
        }
    }
    return list;
}

/*

Polynomial 1: 8x^6 + 4x^4 + 3x^3 + 2x^2 + 1x^1
Polynomial 2: 5x^6 + 3x^5 + 2x^4 + 7x^2 + 6x^0
Resultant Polynomial: 13x^6 + 3x^5 + 6x^4 + 3x^3 + 9x^2 + 1x^1 + 6x^0

*/

int main() {
    singly_linked_list poly1,poly2,result;
    init(&poly1);
    init(&poly2);

    int n;
    printf("Enter the number of terms you want to put in poly 1 >>> ");
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        int c,d;
        printf("%d.) [coefficient]x^[degree] >>> ",i+1);
        scanf("%d %d",&c,&d);
        insert_list(&poly1,c,d);
    }
    printf("Enter the number of terms you want to put in poly 2 >>> ");
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        int c,d;
        printf("%d.) [coefficient]x^[degree] >>> ",i+1);
        scanf("%d %d",&c,&d);
        insert_list(&poly2,c,d);
    }
    
    
    // Creating Polynomial 1;
    // Polynomial 1: 8x^6 + 4x^4 + 3x^3 + 2x^2 + 1x^1
    // insert_list(&poly1,8,6);
    // insert_list(&poly1,4,4);
    // insert_list(&poly1,3,3);
    // insert_list(&poly1,2,2);
    // insert_list(&poly1,1,1);
    
    // Creating Polynomial 2
    // Polynomial 2: 5x^6 + 3x^5 + 2x^4 + 7x^2 + 6x^0
    // insert_list(&poly2,5,6);
    // insert_list(&poly2,3,5);
    // insert_list(&poly2,2,4);
    // insert_list(&poly2,7,2);
    // insert_list(&poly2,6,0);
    /*
5
8 6
4 4
3 3
2 2
1 1
5
5 6
3 5
2 4
7 2
6 0

    */

    printf("Polynomial 1 : ");
    print_list(&poly1);
    printf("Polynomial 2 : ");
    print_list(&poly2);
    
    // add em
    // Resultant Polynomial: 13x^6 + 3x^5 + 6x^4 + 3x^3 + 9x^2 + 1x^1 + 6x^0
    result = add(&poly1,&poly2);

    
    printf("-------------------------------------\n");
    printf("Resultant Polynomial : ");
    print_list(&result);
    
    return 0;
}