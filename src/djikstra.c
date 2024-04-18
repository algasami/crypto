#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

size_t nodes;
int adjweight[MAX_NODES][MAX_NODES];
int adjlist[MAX_NODES][MAX_NODES + 1] = {0};
size_t previous[MAX_NODES];
int mindist[MAX_NODES];
int visited[MAX_NODES] = {0};

size_t from, to;

/**
 * 定義優先佇列
 * Define Priority Queue
 */
struct PriorityData {
    size_t node;
    int priority;
};

struct PriorityQueue {
    struct PriorityData data[MAX_NODES];
    size_t size;
};

int _priority_queue_cmp(struct PriorityData const *const a,
                        struct PriorityData const *const b) {
    return a->priority - b->priority;
}

//  是否空的
int empty(struct PriorityQueue *const pq) { return !pq->size; }

// 加入佇列並排序
void enqueue(struct PriorityQueue *const pq, struct PriorityData val) {
    pq->data[pq->size++] = val;
    qsort(pq->data, pq->size, sizeof(struct PriorityData),
          (int (*)(const void *, const void *))_priority_queue_cmp);
}

// 砍頭
struct PriorityData dequeue(struct PriorityQueue *const pq) {
    struct PriorityData x = pq->data[0];
    for (size_t i = 1; i < pq->size--; i++) {
        pq->data[i - 1] = pq->data[i];
    }
    return x;
}

struct PriorityQueue traverse_queue = {.size = 0};

int main() {
    memset(mindist, -1, sizeof(mindist));
    printf("Node Count: ");
    scanf("%zu", &nodes);
    printf("Edges x y w until 0 0 0: \n");

    while (1) {
        size_t x, y;
        int w;
        scanf("%zu %zu %d", &x, &y, &w);
        if (x == 0 && y == 0 && w == 0)
            break;
        if (x == y)
            continue;

        adjweight[x][y] = adjweight[y][x] = w;
        adjlist[x][adjlist[x][MAX_NODES]++] = y;
        adjlist[y][adjlist[y][MAX_NODES]++] = x;
        /**
         * 這次結合了相鄰矩陣的快速取值優點與陣列的列舉速度
         * This combines the fast det. of adj matrices
         * and the speed of array traversal
         */
    }

    printf("From: ");
    scanf("%u", &from);
    printf("To: ");
    scanf("%u", &to);

    mindist[from] = 0; // 設定起點到起點的最短距離為0

    enqueue(&traverse_queue,
            (struct PriorityData){.node = from, .priority = 0});

    // BFS開始
    while (!empty(&traverse_queue)) {
        size_t node = dequeue(&traverse_queue).node; // 目前BFS的位置
        visited[node] = 1;
        for (size_t i = 0; i < adjlist[node][MAX_NODES]; i++) {
            size_t adjnode = adjlist[node][i];
            if (visited[adjnode])
                continue;

            // 未走訪的鄰邊
            int thisdist = mindist[node] + adjweight[node][adjnode];
            if (mindist[adjnode] < 0 || (mindist[adjnode] > thisdist)) {
                // 如果沒有最短距離，或者最短距離大於用這種方法走的距離時
                mindist[adjnode] = thisdist;
                previous[adjnode] = node;
            }
            enqueue(&traverse_queue,
                    (struct PriorityData){.node = adjnode,
                                          .priority = mindist[adjnode]});
        }
    }

    printf("best: ");
    size_t current = to;
    // 由最後一路走到前面
    while (current != from) {
        printf("%d<-", current);
        current = previous[current];
    }
    printf("%d", current);

    return 0;
}