#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <queue>

struct node {
    int numNode;
    struct node* nextNode;
};

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front, * rear;
};

int* CreateGraph(int vertexes) {
    int* Mtrx = (int*)malloc(sizeof(int) * vertexes * vertexes);
    if (!Mtrx) return 0;
    for (int i = 0; i != vertexes; i++) {
        *(Mtrx + i * vertexes + i) = 0;
        for (int j = 0; j < i; j++) {
            *(Mtrx + i * vertexes + j) = rand() % 2;
            *(Mtrx + j * vertexes + i) = *(Mtrx + i * vertexes + j);
        }
    }
    return Mtrx;
}

void breadthFirstSearchAdjacencyMatrix(int* matrix, int startNode, int numNodes) {
    int* visited = (int*)malloc(sizeof(int) * numNodes);
    if (!visited) return;
    std::queue<int>queue;
    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
    }
    visited[startNode] = 1;
    queue.push(startNode);

    while (!queue.empty()) {
        int currentNode = queue.front();
        printf("%d ", currentNode + 1);

        queue.pop();

        for (int i = 0; i < numNodes; i++) {
            if (*(matrix + currentNode * numNodes + i) && !visited[i]) {
                visited[i] = 1;
                queue.push(i);
            }
        }
    }
}



void ShowGraph(int* graph, int vertexes) {
    if (!graph) return;
    for (int i = 0; i != vertexes; i++) {
        for (int j = 0; j != vertexes; j++) {
            printf("%i ", *(graph + i * vertexes + j));
        }
        printf("|%i", i + 1);
        printf("\n");
    }
}


struct QueueNode* newQueueNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}


struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}


bool isEmpty(struct Queue* q) {
    return (q->front == NULL);
}

void enQueue(struct Queue* q, int data) {
    struct QueueNode* temp = newQueueNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}


void deQueue(struct Queue* q) {
    if (isEmpty(q)) {
        return;
    }
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}


void breadthFirstSearchCustomQueue(int* graph, int numNodes, int startNode) {
    bool* visited = (bool*)malloc(numNodes * sizeof(bool));  // Массивдляотслеживанияпосещенныхвершин
    for (int i = 0; i < numNodes; i++) {
        visited[i] = false;  // Инициализируем все вершины как непосещенные
    }

    struct Queue* q = createQueue(); // Инициализируем очередь

    visited[startNode] = true; // Помечаем начальную вершину как посещенную
    enQueue(q, startNode); // Добавляем начальную вершину в очередь

    while (!isEmpty(q)) {
        int currentNode = q->front->data;
        printf("%d ", currentNode + 1); // Выводим вершину

        deQueue(q); // Удаляем вершину из очереди

        for (int i = 0; i < numNodes; i++) {
            if (*(graph + currentNode * numNodes + i) && !visited[i]) {
                visited[i] = true; // Помечаем вершину как посещенную
                enQueue(q, i); // Добавляем вершину в очередь для дальнейшего обхода
            }
        }
    }

    free(visited);
}


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    int vertexNum = 0;
    printf("Колво вершин: ");
    scanf("%d", &vertexNum);
    int* adjacencyMatrix = CreateGraph(vertexNum);
    ShowGraph(adjacencyMatrix, vertexNum);

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    breadthFirstSearchAdjacencyMatrix(adjacencyMatrix, 0, vertexNum);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения обхода в ширину с использованием стандартной очереди: %f секунд\n", cpu_time_used);
    start = clock();
    // Выполняем обход в ширину с использованием очереди, реализованной самостоятельно
    breadthFirstSearchCustomQueue(adjacencyMatrix, vertexNum, 0);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения обхода в ширину с использованием самостоятельно реализованной очереди: %f секунд\n", cpu_time_used);

    return 0;
}
