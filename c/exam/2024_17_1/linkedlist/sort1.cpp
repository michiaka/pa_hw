#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Titem {
    struct Titem *m_Next;
    struct Titem *m_Prev;
    char *m_text;
} TITEM;

typedef struct {
    TITEM *m_first;
    TITEM *m_last;
} S;

void deleteList(TITEM *lst) {
    while (lst) {
        TITEM *tmp = lst->m_Next;
        free(lst->m_text);
        free(lst);
        lst = tmp;
    }
}

bool insertItem(S *s, const char *text) {
    TITEM *cur = s->m_first;
    while (cur) {
        if (strcmp(text, cur->m_text) == 0) {
            return false; // Duplicate found
        }
        cur = cur->m_Next;
    }

    TITEM *newNode = (TITEM *)malloc(sizeof(TITEM));
    newNode->m_text = strdup(text);
    newNode->m_Next = newNode->m_Prev = NULL;

    if (!s->m_first) { // Empty list
        s->m_first = s->m_last = newNode;
    } else {
        newNode->m_Prev = s->m_last;
        s->m_last->m_Next = newNode;
        s->m_last = newNode;
    }

    return true;
}

void swapLists(S *s, TITEM *prev, TITEM *cur) {
    if (!prev || !cur) {
        printf("No need to swap\n");
        return;
    }

    if (!prev->m_Prev && !cur->m_Next) {
        s->m_first = cur;
        s->m_last = prev;
        cur->m_Next = prev;
        prev->m_Prev = cur;
        cur->m_Prev = NULL;
        prev->m_Next = NULL;
    } else if (!prev->m_Prev) {
        s->m_first = cur;
        cur->m_Next->m_Prev = prev;
        prev->m_Next = cur->m_Next;
        cur->m_Next = prev;
        prev->m_Prev = cur;
        cur->m_Prev = NULL;
    } else if (!cur->m_Next) {
        s->m_last = prev;
        prev->m_Prev->m_Next = cur;
        cur->m_Prev = prev->m_Prev;
        cur->m_Next = prev;
        prev->m_Prev = cur;
        prev->m_Next = NULL;
    } else {
        cur->m_Next->m_Prev = prev;
        prev->m_Prev->m_Next = cur;
        cur->m_Prev = prev->m_Prev;
        prev->m_Next = cur->m_Next;
        cur->m_Next = prev;
        prev->m_Prev = cur;
    }
}

void printList(S *s) {
    printf("------------------------------------\n");
    TITEM *currentDoubly = s->m_first;
    while (currentDoubly != NULL) {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly = currentDoubly->m_Next;
    }
    printf("NULL\n");
    printf("------------------------------------\n");
}

void bubblesortList(S *s) {
    TITEM *cur;
    TITEM *last = NULL;
    int swapped;

    // Handle empty or single-node list
    if (s->m_first == NULL || s->m_first->m_Next == NULL) {
        return;
    }

    do {
        swapped = 0;
        cur = s->m_first;

        while (cur->m_Next != last) {
            if (strcmp(cur->m_text, cur->m_Next->m_text) > 0) {
                swapLists(s, cur, cur->m_Next);
                swapped = 1;
            }
            cur = cur->m_Next;
        }

        // Move the last boundary of sorted elements
        last = cur;

    } while (swapped);
}
int main() {
    S s = {0};

    if (!insertItem(&s, "5")) ;
    if (!insertItem(&s, "1")) ;
    if (!insertItem(&s, "4")) ;
    if (!insertItem(&s, "3")) ;
    if (!insertItem(&s, "2")) ;
    if (!insertItem(&s, "6")) ;

    // Display the doubly linked list
    printList(&s);

    bubblesortList(&s);

    // Display the sorted doubly linked list
    printList(&s);

    deleteList(s.m_first);
    return 0;
}
