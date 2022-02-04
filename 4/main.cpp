#include <iostream>
using namespace std;

int* getArrayRand(int aSize)
{
    int* pArr = nullptr;
    try {
        pArr = (int*) new int[aSize];
        for (int i = 0; i < aSize; i++)
        {
            pArr[i] = rand() % 1000;
        }
    }
    catch (const std::exception&)
    {
        cout << "No memory allocated." << endl;
    }
    return pArr;
}

void freeArray(int* pArr)
{
    if (pArr != nullptr)
    {
        delete pArr;
        pArr = nullptr;
    }
}

void printArray(const int* pArr, const int aSize)
{
    for (int i = 0; i < aSize; i++)
    {
        cout << pArr[i] << " ";
    }
    cout << endl;
}

void swapInt(int* pA, int* pB)
{
    int t = *pA; *pA = *pB; *pB = t;
}

void sortHoara(int* pArr, int aFirst, int aLast)
{
    int indFirst = aFirst;
    int indLast = aLast;
    int ref = pArr[(indLast + indFirst) / 2];

    do {
        while (pArr[indFirst] < ref) indFirst++;
        while (pArr[indLast] > ref) indLast--;
        if (indFirst <= indLast) {
            swapInt(&pArr[indFirst], &pArr[indLast]);
            indFirst++;
            indLast--;
        }
    } while (indFirst <= indLast);
    if (indFirst < aLast) sortHoara(pArr, indFirst, aLast);
    if (aFirst < indLast) sortHoara(pArr, aFirst, indLast);
}

void sortLomuto(int* pArr, int aFirst, int aLast)
{
    if (aFirst < aLast)
    {
        int indFirst = aFirst;
        int ref = pArr[aLast];
        for (int i = aFirst; i < aLast; i++)
        {
            if (pArr[i] <= ref)
            {
                swapInt(&pArr[indFirst], &pArr[i]);
                indFirst++;
            }
        }
        swapInt(&pArr[aLast], &pArr[indFirst]);
        sortLomuto(pArr, aFirst, indFirst - 1);
        sortLomuto(pArr, indFirst + 1, aLast);
    }
}

void sortThickPartitioning(int* pArr, int aFirst, int aLast)
{
    if (aFirst < aLast)
    {
        int ref = pArr[aLast];

        int l_indFirst = aFirst;
        int l_indLast = aLast - 1;
        int r_indFirst = aFirst - 1;
        int r_indLast = aLast;

        while (l_indFirst <= l_indLast)
        {
            while (pArr[l_indFirst] < ref) l_indFirst++;
            while (pArr[l_indLast] > ref) l_indLast--;
            if (l_indFirst >= l_indLast) break;
            swapInt(&pArr[l_indFirst], &pArr[l_indLast]);
            if (pArr[l_indFirst] == ref)
                swapInt(&pArr[++r_indFirst], &pArr[l_indFirst++]);
            if (pArr[l_indLast] == ref)
                swapInt(&pArr[--r_indLast], &pArr[l_indFirst--]);
        }
        swapInt(&pArr[l_indFirst], &pArr[aLast]);

        l_indLast = l_indFirst - 1;
        l_indFirst++;

        for (int k = aFirst; k <= r_indFirst; k++, l_indLast--)
            swapInt(&pArr[k], &pArr[l_indFirst]);
        for (int k = aLast - 1; k >= r_indLast; k++, l_indFirst++)
            swapInt(&pArr[k], &pArr[l_indFirst]);

        sortThickPartitioning(pArr, aFirst, l_indLast);
        sortThickPartitioning(pArr, l_indFirst, aLast);
    }
}

void sortInserts(int* pArr, int aFirst, int aLast)
{
    if (aFirst >= aLast) return;
    int indLast = aFirst;
    while (indLast < aLast)
    {
        indLast++;
        for (int i = aFirst; i < indLast; i++)
            if (pArr[i] > pArr[indLast])
                swapInt(&pArr[i], &pArr[indLast]);
    }
}

void sortQuickImprovement(int* pArr, int aFirst, int aLast)
{
    if (aFirst >= aLast) return;
    if ((aLast - aFirst) <= 10)
        sortInserts(pArr, aFirst, aLast);
    else
    {
        int m[3] = { pArr[aFirst],
                    pArr[(aFirst + aLast) / 2],
                    pArr[aLast] };
        sortInserts(m, 0, 2);
        int ref = m[1];

        int indFirst = aFirst;
        int indLast = aLast;

        do {
            while (pArr[indFirst] < ref) indFirst++;
            while (pArr[indLast] > ref) indLast--;
            if (indFirst <= indLast) {
                swapInt(&pArr[indFirst], &pArr[indLast]);
                indFirst++;
                indLast--;
            }
        } while (indFirst <= indLast);
        if (indFirst < aLast) sortQuickImprovement(pArr, indFirst, aLast);
        if (aFirst < indLast) sortQuickImprovement(pArr, aFirst, indLast);
    }
}

struct basket
{
    int cnt;
    int* pInt;
};

basket* getBaskets(const int aNumberBaskets, const int aSizeBasket)
{
    basket* pBskt = nullptr;
    try {
        pBskt = new basket[aNumberBaskets];
        if (pBskt != nullptr)
        {
            for (int i = 0; i < aNumberBaskets; i++)
            {
                pBskt[i].cnt = 0;
                pBskt[i].pInt = new int[aSizeBasket];
            }
        }
    }
    catch (const std::exception&)
    {
        cout << "No memory allocated." << endl;
    }
    return pBskt;
}

void freeBaskets(basket* pBskt, const int aNumberBaskets)
{
    if (pBskt != nullptr)
    {
        for (int i = 0; i < aNumberBaskets; i++)
        {
            delete pBskt[i].pInt;
        }

        delete pBskt;
        pBskt = nullptr;
    }
}

void sortBasket(int* pArr, int aSize)
{
    const int NUMBER_BASKETS = 10;

    basket* pBskt = getBaskets(NUMBER_BASKETS, aSize);
    if (pBskt == nullptr) return;

    for (int digit = 1; digit < 1000000000; digit *= 10)
    {
        for (int i = 0; i < aSize; i++)
        {
            if (pArr[i] % 2 == 0)
            {
                int d = (pArr[i] / digit) % NUMBER_BASKETS;
                pBskt[d].pInt[pBskt[d].cnt++] = pArr[i];
                pArr[i] = -1;
            }
        }
        int ind = 0;
        for (int i = 0; i < NUMBER_BASKETS; i++)
        {
            for (int j = 0; j < pBskt[i].cnt; j++)
            {
                while (pArr[ind] != -1) ind++;
                if (pArr[ind] == -1)
                    pArr[ind] = pBskt[i].pInt[j];
                ind++;
            }
            pBskt[i].cnt = 0;
        }
    }
    freeBaskets(pBskt, NUMBER_BASKETS);
}

void task_1(void)
{
    cout << "Task 1\n" << endl;

    const int SIZE_ARRAY = 20;

    int* pArr = getArrayRand(SIZE_ARRAY);
    cout << "Array before sorting:" << endl;
    printArray((const int*)pArr, SIZE_ARRAY);
    sortQuickImprovement(pArr, 0, SIZE_ARRAY - 1);
    cout << "Array after sorting:" << endl;
    printArray((const int*)pArr, SIZE_ARRAY);
    freeArray(pArr);
    cout << endl;
}

void task_2(void)
{
    cout << "Task 2\n" << endl;

    const int SIZE_ARRAY = 40;

    int* pArr = getArrayRand(SIZE_ARRAY);
    cout << "Array before sorting:" << endl;
    printArray((const int*)pArr, SIZE_ARRAY);
    sortBasket(pArr, SIZE_ARRAY);
    cout << "Array after sorting:" << endl;
    printArray((const int*)pArr, SIZE_ARRAY);
    freeArray(pArr);
    cout << endl;
}

int main() {

    task_1();

    task_2();

    return 0;
}
