#include<stdio.h>
#include<stdlib.h>
#define SIZE 50
#define EPS 0.0000000001
int arrLen;


void assignmentForChar(char* x, char* y)
{
    *x = *y;
}

void assignment(void* x, void* y, size_t size)
{
    char* x1 = (char*) x;
    char* y1 = (char*) y;
    int i;
    for (i = 0; i < size; ++i)
    {
        *(x1 + i) = *(y1 + i);
    }
    x = (void*) x1;
    y = (void*) y1;
}


int compForString(void* x, void* y)
{
    char *a = *(char**) x;
    char *b = *(char**) y;
    int ind = 0;
    while (a[ind] != '\0' && b[ind] != '\0')
    {
        if (a[ind] < b[ind])
        {
            return 1;
        }
        if (a[ind] > b[ind])
        {
            return 0;
        }
        ++ind;
    }
    return 1;
}


int compForInt(void* a, void* b)
{
    int* x = (int*) a;
    int* y = (int*) b;
    if (*x <= *y)
    {
        return 1;
    }
    return 0;
}

int compForDouble(void* a, void* b)
{
    double* x = (double*) a;
    double* y = (double*) b;
    if (EPS <= *y - *x)
    {
        return 1;
    }
    return 0;
}


void merge(void** array, int left, int middle, int right, size_t size, int (*cmp)(void *, void *))
{
    int i = 0;
    int j = 0;

    while (left + i < middle && middle + j < right)
    {
        if (!cmp((array[0] + (middle + j) * size), (array[0] + (left + i) * size)))
        {
            assignment(array[1] + (i + j) * size, array[0] + (left + i) * size, size);
            ++i;
        }
        else
        {
            assignment(array[1] + (i + j) * size,  array[0] + (middle + j) * size, size);
            ++j;
        }
    }
    while (left + i < middle)
    {
        assignment(array[1] + (i + j) * size, array[0] + (left + i) * size, size);
        ++i;
    }
    while (middle + j < right)
    {
        assignment(array[1] + (i + j) * size,  array[0] + (middle + j) * size, size);
        ++j;
    }
    int ind;
    for (ind = 0; ind < (right - left); ++ind)
    {
        assignment(array[0] + (left + ind) * size, array[1] + ind * size, size);
    }
}


void mergeSort(void** array, int left, int right, size_t size, int (*cmp)(void *, void *))
{
    if (right - left > 1)
    {
        int middle = (left + right) / 2;
        mergeSort(array, left, middle, size, cmp);
        mergeSort(array, middle, right, size, cmp);

        merge(array, left, middle, right, size, cmp);
    }
}


int* readInts()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &arrLen);


    int* a = (int*) malloc(arrLen * sizeof(int));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%d", &a[i]);
    }
    fclose(input);
    return a;
}

void writeInts(int* a)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}


char** readStrings()
{
    char** a;
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("input error");
    }
    else
    {
        fscanf(input, "%d", &arrLen);
        a = (char**) malloc(arrLen * sizeof(char*));
        int i;
        int maxLength;
        char symbol = fgetc(input);
        char* tmp;

        for (i = 0; i < arrLen; ++i)
        {
            maxLength = SIZE;
            int j;
            a[i] = (char*) malloc(maxLength * sizeof(char));

            for (j = 0; (symbol = getc(input)) != '\n'; ++j)
            {
                if (j >= maxLength - 1)
                {
                    tmp = (char*) realloc(a[i], maxLength * 2 * sizeof(char));
                    if (tmp == NULL)
                    {
                        printf("error");
                        break;
                    }
                    else
                    {
                        a[i] = tmp;
                        maxLength = maxLength * 2;
                    }
                }
                a[i][j] = symbol;
            }
            a[i][j] = '\0';
        }
    }
    fclose(input);
    return a;
}

void writeStrings(char** array)
{
    FILE* output = fopen("output.txt", "w");
    int i, j;
    for (i = 0; i < arrLen; ++i)
    {
        for (j = 0; array[i][j] != '\0'; ++j)
        {
            fprintf(output, "%c", array[i][j]);
        }
        fprintf(output, "\n");
    }
    fclose(output);
}

double* readDoubles()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &arrLen);


    double* a = (double*) malloc(arrLen * sizeof(double));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%lf", &a[i]);
    }
    fclose(input);
    return a;
}

void writeDoubles(double* a)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%lf ", a[i]);
    }
    fclose(output);
}

int main()
{
    char** a = readStrings();
    char*** array = (char***) malloc(2 * sizeof(char**));
    array[0] = a;
    array[1] = (char**) malloc(arrLen * sizeof(char*));

    mergeSort((void**)array, 0, arrLen, sizeof(char*), compForString);
    writeStrings(array[1]);

    free(array[0]);
    free(array[1]);
    free(array);

    return 0;
}
