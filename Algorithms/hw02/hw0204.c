#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef enum
{
    PQ_MIN = -1,
    PQ_MAX = 1
} PriorityQueueType;

typedef struct
{
    int *data;
    int size;
    int capacity;
    PriorityQueueType type;
} PriorityQueue;

void pq_init(PriorityQueue *pq, int capacity, PriorityQueueType type);
void pq_destroy(PriorityQueue *pq);
bool pq_is_empty(PriorityQueue *pq);
int pq_top(PriorityQueue *pq);
void pq_insert(PriorityQueue *pq, int value);
int pq_extract_max(PriorityQueue *pq);
int pq_extract_min(PriorityQueue *pq);

int compare_start_time(const void *a, const void *b)
{
    int *segment1 = (int *)a;
    int *segment2 = (int *)b;
    return segment1[0] - segment2[0];
}

int main()
{
    int N, L;
    scanf("%d %d", &N, &L);

    int segments[N][2];
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &segments[i][0], &segments[i][1]);
    }

    qsort(segments, N, sizeof(segments[0]), compare_start_time);

    PriorityQueue pq;
    pq_init(&pq, 16, PQ_MIN); // Start with a smaller capacity of 16

    int currentTime = 0;
    int minSegments = 0;
    int totalTimeWithoutSpeaker = 0;
    int i = 0;

    while (currentTime < L)
    {
        while (i < N && segments[i][0] <= currentTime)
        {
            pq_insert(&pq, -segments[i][1]); // Negative value to use PQ_MIN as PQ_MAX
            i++;
        }

        if (pq_is_empty(&pq))
        {
            if (i < N)
            {
                totalTimeWithoutSpeaker += segments[i][0] - currentTime;
                currentTime = segments[i][0];
            }
            else
            {
                totalTimeWithoutSpeaker += L - currentTime;
                break;
            }
        }
        else
        {
            int maxEndTime = -pq_extract_min(&pq);
            if (maxEndTime > currentTime)
            {
                currentTime = maxEndTime;
                minSegments++;
            }
        }
    }

    printf("%d %d\n", minSegments, totalTimeWithoutSpeaker);

    pq_destroy(&pq);
    return 0;
}

void pq_swap(PriorityQueue *pq, int i, int j)
{
    int temp = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = temp;
}

void pq_resize(PriorityQueue *pq, int new_capacity)
{
    int *new_data = (int *)malloc(new_capacity * sizeof(int));
    for (int i = 0; i < pq->size; i++)
    {
        new_data[i] = pq->data[i];
    }
    free(pq->data);
    pq->data = new_data;
    pq->capacity = new_capacity;
}

void pq_sift_up(PriorityQueue *pq, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (pq->type * pq->data[index] > pq->type * pq->data[parent])
        {
            pq_swap(pq, index, parent);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void pq_sift_down(PriorityQueue *pq, int index)
{
    while (index * 2 + 1 < pq->size)
    {
        int left_child = index * 2 + 1;
        int right_child = index * 2 + 2;
        int swap_index = left_child;
        if (right_child < pq->size && pq->type * pq->data[right_child] > pq->type * pq->data[swap_index])
        {
            swap_index = right_child;
        }

        if (pq->type * pq->data[index] < pq->type * pq->data[swap_index])
        {
            pq_swap(pq, index, swap_index);
            index = swap_index;
        }
        else
        {
            break;
        }
    }
}

void pq_init(PriorityQueue *pq, int capacity, PriorityQueueType type)
{
    pq->data = (int *)malloc(capacity * sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    pq->type = type;
}

void pq_destroy(PriorityQueue *pq)
{
    free(pq->data);
}

bool pq_is_empty(PriorityQueue *pq)
{
    return pq->size == 0;
}

int pq_top(PriorityQueue *pq)
{
    return pq->data[0];
}

void pq_insert(PriorityQueue *pq, int value)
{
    if (pq->size == pq->capacity)
    {
        pq_resize(pq, pq->capacity * 2);
    }
    pq->data[pq->size] = value;
    pq_sift_up(pq, pq->size);
    pq->size++;
}

int pq_extract_max(PriorityQueue *pq)
{
    int value = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];
    pq_sift_down(pq, 0);
    return value;
}

int pq_extract_min(PriorityQueue *pq)
{
    return pq_extract_max(pq);
}