#include "LKH.h"

void MTSP_WriteResult(char * FileName, GainType Penalty, GainType Cost)
{
    FILE *ResultFile;
    Node *N, *NextN;
    int Size, Forward;
    char *FullFileName;
    GainType Sum;

    if (FileName == 0)
        return;
    FullFileName = FullName(FileName, Cost);
    if (TraceLevel >= 1)
        printff("Writing MTSP_SOLUTION_FILE: \"%s\" ... ", FullFileName);
    assert(ResultFile = fopen(FullFileName, "w"));
    fprintf(ResultFile, "%s, Cost: " GainFormat "_" GainFormat "\n",
            Name, Penalty, Cost);
    fprintf(ResultFile, "The tours traveled by the %d salesmen are:\n",
            Salesmen);
    N = Depot;
    Forward = N->Suc->Id != N->Id + DimensionSaved; 
    do {
        Sum = 0;
        Size = -1;
        do {
            fprintf(ResultFile, "%d ", N->Id <= Dim ? N->Id : Depot->Id);
            NextN = Forward ? N->Suc : N->Pred;
            Sum += C(N, NextN) - N->Pi - NextN->Pi;
            Size++;
            if (NextN->Id > DimensionSaved)
                NextN = Forward ? NextN->Suc : NextN->Pred;
            N = NextN;
        } while (N->DepotId == 0);
        fprintf(ResultFile, "%d (#%d)  Cost: " GainFormat "\n",
                Depot->Id, Size, Sum / Precision);
    } while (N != Depot);
    fclose(ResultFile);
    if (TraceLevel >= 1)
        printff("done\n");
}
