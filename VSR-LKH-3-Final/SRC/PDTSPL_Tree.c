#include "LKH.h"
#include "Segment.h"

#define Dad Nearest
#define FirstSon OldPred
#define LastSon OldSuc
#define NextTourNode Mark

void Perturb();
void InsertSubTree(Node *N, Node *Prev, Node *Dad);
void RemoveSubTree(Node *N);
GainType Tree2Tour();
void Tour2Tree();

GainType TreeCost() 
{
    GainType Cost = 0;
    Node *N = Depot;
    do
        Cost += C(N, N->Suc) - N->Pi - N->Suc->Pi;
    while ((N = N->Suc) != Depot);
    return Cost / Precision;
}

void Tour2Tree() 
{
    Node *Current = Depot, *N;
    int *Stack, StackTop = -1;
    int Forward = SUCC(Depot)->Id != Depot->Id + DimensionSaved;
    assert(Stack = (int *) malloc(Dim * sizeof(int)));
    N = FirstNode;
    do
        N->Dad = N->FirstSon = N->LastSon = N->Next = 0;
    while ((N = N->Suc) != FirstNode);
    Stack[++StackTop] = Depot->Id;
    do {
        if (Current->Delivery) {
            N = &NodeSet[Stack[StackTop]];
            Current->Dad = N;
            Current->Prev = N->LastSon;
            if (!N->FirstSon)
                N->FirstSon = N->LastSon = Current;
            else {
                N->LastSon->Next = Current;
                N->LastSon = Current;
            }
            Stack[++StackTop] = Current->Id;
        } else if (Current->Pickup)
            StackTop--;
        Current = Forward ? SUCC(Current) : PREDD(Current);
    } while (Current != Depot);
}

void RemoveSubTree(Node *N) 
{
    Node *Prev = N->Prev;
    if (Prev)
        Prev->Next = N->Next;
    if (N->Next)
        N->Next->Prev = Prev;
    if (N->Dad->FirstSon == N)
        N->Dad->FirstSon = N->Next;
    if (N->Dad->LastSon == N)
        N->Dad->LastSon = Prev;
    N->Dad = N->Prev = N->Next = 0;
}

Node *BestPrev, *BestDad;
GainType BestMin;

void FindBestPrevDad(Node *N, Node *Root) {
    Node *Son, *Prev;
    GainType d;
    if (Root == Depot) {
        if (!Depot->FirstSon) {
            BestPrev = 0;
            BestDad = Depot;
            return;
        }
        BestMin = INT_MAX;
    }
    Prev = Root->LastSon;
    if (Prev) {
        InsertSubTree(N, Prev, Root);
        if ((d  = Random() /* Tree2Tour() */) < BestMin) {
            BestMin = d;
            BestPrev = Prev;
            BestDad = Root;
        }
        RemoveSubTree(N);
    }
    Son = Root->FirstSon;
    while (1) {
        Prev = Son ? Son->Prev : 0;
        InsertSubTree(N, Prev, Root);
        if ((d = Random()/* Tree2Tour() */) < BestMin) {
            BestMin = d;
            BestPrev = Prev;
            BestDad = Root;
        }
        RemoveSubTree(N);
        if (!Son)
            break;
        FindBestPrevDad(N, Son);
        Son = Son->Next;
    }
}

void InsertSubTree(Node *N, Node *Prev, Node *Dad) {
    N->Prev = Prev;
    if (Prev) {
        N->Next = Prev->Next;
        if (Prev->Next)
            Prev->Next->Prev = N;
        Prev->Next = N;
    } else
        N->Next = Dad->FirstSon;
    if (N->Next)
        N->Next->Prev = N;
    if (!Dad->FirstSon)
        Dad->FirstSon = Dad->LastSon = N;
    else if (!N->Prev)
        Dad->FirstSon = N;
    else if (!N->Next)
        Dad->LastSon = N;
    N->Dad = Dad;
}

void Perturb()
{
    int Count = 0, i, j;
    Node **TreeSet, *N;
    assert(TreeSet = (Node **) malloc(Dim * sizeof(Node *)));
    N = Depot;
    do {
        if (N->Delivery)
            TreeSet[Count++] = N;
    } while ((N = N->Suc) != Depot);
    for (i = 1; i < Count; i++) {
        N = TreeSet[i];
        TreeSet[i] = TreeSet[j = Random() % (i + 1)];
        TreeSet[j] = N;
    }
    Tour2Tree();
    for (i = 0; i < 40; i++) {
        N = TreeSet[i];
        RemoveSubTree(N);
        FindBestPrevDad(N, Depot);
        InsertSubTree(N, BestPrev, BestDad);
    }
    Tree2Tour();
}

static Node *Last;

void DFS(Node *Current)
{
    Node *N = Current == Depot || Current->Delivery ?
          Current : &NodeSet[Current->Pickup];
    if (Last) 
        Last = Last->NextTourNode = N;
    else
        Last = N;
    N = Current->FirstSon;
    while (N) {
        DFS(N);
        N = N->Next;
    }
    if (Current != Depot) {
        N = Current->Delivery ? &NodeSet[Current->Delivery] : Current;
        Last = Last->NextTourNode = N;
    }
}

GainType Tree2Tour()
{
    Node *N;
    GainType Cost;
    Last = 0;
    DFS(Depot);
    Last->NextTourNode = Depot;
    N = Depot;
    Follow(N, N);
    do {
        Follow(N->NextTourNode, N);
    } while ((N = N->NextTourNode) != Depot);
    do {
        Precede(&NodeSet[N->Id + DimensionSaved], N);
    } while ((N = N->NextTourNode) != Depot);
    Cost = 0;
    N = Depot;
    do
        Cost += C(N, N->Suc) - N->Pi - N->Suc->Pi;
    while ((N = N->Suc) != Depot);
//    printff("Cost = %lld\n", Cost / Precision);
    assert(Penalty() == 0);
    return Cost / Precision;
}
