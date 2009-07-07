#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct collection {
    int data;
    struct collection *next;
} Collection;


int ListLength  (Collection *list);
int CreateList  (Collection *list, int n);
int DispList    (Collection *list);
int SortList    (Collection **list);
int DestroyList (Collection **list);
int isEmpty     (Collection *list);

Collection * MergeList          (Collection *list1, Collection *list2);
Collection * GetIntersection    (Collection *list1, Collection *list2);
Collection * GetDiffset         (Collection *list1, Collection *list2);

int main (int argc, char **argv) {
    Collection *List1, *List2, *NewList;

    List1       = (Collection *) malloc (sizeof (Collection));
    List1->next = NULL;
    List2       = (Collection *) malloc (sizeof (Collection));
    List2->next = NULL;

    srandom (time (NULL));

    printf      ("Original lists:\n");
    CreateList  (List1, 10);
    DispList    (List1);
    CreateList  (List2, 6);
    DispList    (List2);
    printf      ("Sorted lists:\n");
    SortList    (&List1);
    DispList    (List1);
    SortList    (&List2);
    DispList    (List2);
    NewList =   MergeList (List1, List2);
    printf      ("Merged list:\n");
    DispList    (NewList);
    DestroyList (&NewList);
    NewList =   GetIntersection (List1, List2);
    printf      ("Intersection:\n");
    DispList    (NewList);
    DestroyList (&NewList);
    NewList =   GetDiffset (List1, List2);
    printf      ("Different set:\n");
    DispList    (NewList);
    DestroyList (&NewList);

    DestroyList (&List1);
    DestroyList (&List2);
    return 0;
}

int isEmpty (Collection *list) {
    return (list->next == NULL);
}

int ListLength (Collection *list) {
    int n = 0;
    while (list != NULL) {
        n++;
        list = list->next;
    }
    return n;
}

int CreateList (Collection *list, int n) {
    int i;
    Collection *tmp = list;
    for (i = 0; i < n-1; i++) {
        tmp->data = random () % 200 + 1;
        tmp->next = (Collection *) malloc (sizeof (Collection));
        tmp = tmp->next;
    }
    list->data = 0;
    tmp->data = random () % 200 + 1;
    tmp->next = NULL;
    return 0;
}

int DispList (Collection *list) {
    while (list != NULL) {
        printf ("%d ", list->data);
        list = list->next;
    }
    puts("");
    return 0;
}

int SortList (Collection **list) {
    Collection *p = (*list)->next, *q, *r;
    if (p != NULL) {
        r = p->next;
        p->next = NULL;
        p = r;
        while (p != NULL) {
            r = p->next;
            q = *list;
            while (q->next != NULL && q->next->data < p->data)
                q = q->next;
            p->next = q->next;
            q->next = p;
            p = r;
        }
    }
    return 0;
}

int DestroyList (Collection **list) {
    if ((*list)->next != NULL)
        DestroyList (&((*list)->next));
    else
        free (*list);
    return 0;
}

Collection * MergeList (Collection *list1, Collection *list2) {
    int flag; 
    Collection *ret, *p, *q, *tail;
    ret = (Collection *) malloc (sizeof (Collection)); 
    ret->data = 0;
    p = list1->next;
    q = ret;
    while (p != NULL) {
        q->next = (Collection *) malloc (sizeof (Collection));
        memcpy ((void *)q->next, (void *)p, sizeof (Collection));
        q = q->next;
        p = p->next;
    }
    q = ret;
    while (q->next != NULL) {
        q = q->next;
        tail = q;
    }

    while (list2 != NULL) {
        p = list1;
        while (p != NULL) {
            if (list2->data == p->data) {
                flag = 1;
                break;
            }
            p = p->next;
            flag = 0;
        }
        if (flag == 0) {
            tail->next = (Collection *) malloc (sizeof (Collection));
            tail->next->data = list2->data;
            tail = tail->next;
        }
        list2 = list2->next;
    }
    return ret;
}

Collection * GetIntersection (Collection *list1, Collection *list2) {
    Collection *ret, *p, *q;
    list1 = list1->next;
    list2 = list2->next;
    ret = (Collection *) malloc (sizeof (Collection));
    ret->data = 0;
    ret->next = NULL;
    p = ret;
    while (list1 != NULL) {
        q = list2;
        while (q != NULL) {
            if (list1->data == q->data) {
                p->next = (Collection *) malloc (sizeof (Collection));
                p->next->data = q->data;
                p = p->next;
                p->next = NULL;
                break;
            }
            q = q->next;
        }
        list1 = list1->next;
    }

    return ret;
}

Collection * GetDiffset (Collection *list1, Collection *list2) {
    Collection *ret, *q, *p;
    int flag;
    list1 = list1->next;
    list2 = list2->next;
    ret = (Collection *) malloc (sizeof (Collection));
    ret->data = 0;
    ret->next = NULL;
    p = ret;

    while (list1 != NULL) {
        q = list2;
        flag = 0;
        while (q != NULL) {
            if (list1->data == q->data) {
                flag = 1;
                break;
            }
            q = q->next;
        }
        if (flag == 0) {
            p->next = (Collection *) malloc (sizeof (Collection));
            p->next->data = list1->data;
            p = p->next;
        }
        list1 = list1->next;
    }
    return ret;
}

