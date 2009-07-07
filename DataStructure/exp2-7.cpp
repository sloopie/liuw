#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int power;     
    int modulus;  
    struct node *next;
} Poly;

Poly * new_node () {
    return (Poly *) malloc (sizeof (Poly));
}

int DispPoly (Poly *poly) {
    while (poly != NULL) {
        printf ("%dx%d ", poly->modulus, poly->power);
        poly = poly->next;
    }
    puts("");
    return 0;
}

Poly * add (Poly *p1, Poly *p2) {
    Poly *ret, *p, *q, *tail;
    int flag;

    ret = new_node ();
    p = p1->next;
    q = ret;
    memcpy ((void *)ret, (void *)p1, sizeof (Poly));
    while (p != NULL) {
        q->next = new_node ();
        memcpy ((void *)q->next, (void *)p, sizeof (Poly));
        q = q->next;
        p = p->next;
    }

    p = ret;
    while (p->next != NULL) {
        p = p->next;
        tail = p;
    }

    while (p2 != NULL) {
        p = ret;
        flag = 0;
        while (p != NULL) {
            if (p2->power == p->power) {
                p->modulus += p2->modulus;
                flag = ;
                break;
            }
            flag = 1;
            p = p->next;
        }
        if (flag == 1) {
            tail->next = new_node ();
            tail = tail->next;
            tail->power = p2->power;
            tail->modulus = p2->modulus;
        }
        p2 = p2->next;
    }
    return ret;
}

int main (int argc, char **argv) {
    Poly *poly1, *poly2, *poly3, *t;

    poly1 = new_node ();
    poly1->power = 5;
    poly1->modulus = 2;
    t = new_node();
    t->power = 3;
    t->modulus = 1;
    poly1->next = t;

    poly2 = new_node ();
    poly2->power = 0;
    poly2->modulus = 4;
    t = new_node ();
    t->power = 1;
    t->modulus = 1;
    poly2->next = t;
    t = new_node ();
    t->power = 3;
    t->modulus = 3;
    poly2->next->next =t;

    DispPoly (poly1);
    DispPoly (poly2);

    poly3 = add (poly1, poly2);
    DispPoly (poly3);

    return 0;
}
