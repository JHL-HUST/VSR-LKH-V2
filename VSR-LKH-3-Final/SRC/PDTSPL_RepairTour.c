#include "LKH.h"
#include "Segment.h"

/* The PDTSPL_RepairTour function creates a feasible tour from a given tour.
 */

GainType PDTSPL_RepairTour()
{
    Node **Fringe, *First, *Last, *N;
    int FringeNodes = 0, Min, i, j;
    GainType Cost;
    int *Stack, StackTop = -1;
    int Forward = SUCC(Depot)->Id != Depot->Id + DimensionSaved;

    assert(Stack = (int *) malloc(Dim * sizeof(int)));
    assert(Fringe = (Node **) malloc(Dim * sizeof(Node *)));
    First = Last = Depot;
    First->Prev = First->Next = First;
    FringeNodes = 0;
    N = Depot;
    i = 0;
    do {
        if (N->Delivery)
            Fringe[FringeNodes++] = N;
        if (N->Delivery || N->Pickup)
            N->Rank = ++i;
        N = Forward ? SUCC(N) : PREDD(N);
    } while (N != Depot);
    while (FringeNodes > 0) {
        Min = INT_MAX;
        for (j = 0; j < FringeNodes; j++) {
            N = Fringe[j];
            if ((N->Delivery || 
                (StackTop >= 0 && N->Pickup == Stack[StackTop])) &&
                N->Rank < Min) {
                Min = N->Rank;
                i = j;
            }
        }
        N = Fringe[i];
        Fringe[i] = Fringe[--FringeNodes];
        if (N->Delivery) {
            Stack[++StackTop] = N->Id;
            Fringe[FringeNodes++] = &NodeSet[N->Delivery];
        } else
            StackTop--;
        N->Prev = Last;
        N->Next = First;
        First->Prev = Last->Next = N;
        Last = N;
    }
    free(Fringe);
    free(Stack);
    N = First;
    Follow(N, N);
    do {
        Follow(N->Next, N);
    } while ((N = N->Next) != First);
    do {
        Precede(&NodeSet[N->Id + DimensionSaved], N);
    } while ((N = N->Next) != First);
    Cost = 0;
    N = First;
    do
        Cost += C(N, N->Suc) - N->Pi - N->Suc->Pi;
    while ((N = N->Suc) != First);
    CurrentPenalty = 0;
    return Cost / Precision;
}
