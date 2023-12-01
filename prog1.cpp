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

int ModifyGraph(struct node* list, int* graph, int vertexes) {
    if (!list || !graph) return 0;
    for (int i = 0; i != vertexes; i++) {
        struct node* current = list + i;
        current->numNode = i + 1;
        for (int j = 0; j != vertexes; j++) {
            if (*(graph + i * vertexes + j)) {
                current->nextNode = (struct node*)malloc(sizeof(struct node));
                current = current->nextNode;
                current->numNode = j + 1;
            }
        }
        current->nextNode = NULL;
    }
    return 1;
}

void breadthFirstSearchAdjacencyMatrix(int* matrix, int startNode, int numNodes) {
    int* visited = (int*)malloc(sizeof(int) * numNodes);

    if (!visited || numNodes <= 0) return;
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

void breadthFirstSearchAdjacencyList(struct node* adjacencyList, int startNode, int numNodes) {
    int* visited = (int*)malloc(sizeof(int) * numNodes);

    if (!visited || numNodes<=0) return;
    std::queue<int>queue;
    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
    }
    visited[startNode] = 1;
    queue.push(startNode);

    while (!queue.empty()) {
        int currentNode = queue.front();
        struct node* current = adjacencyList + currentNode;
        printf("%d ", currentNode + 1);

        queue.pop();
        do {
            if (!visited[(current)->numNode - 1]) {
                visited[(current)->numNode - 1] = 1;
                queue.push((current)->numNode - 1);
            }
            current = current->nextNode;
        } while (current);
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

void ShowList(struct node* list, int vertexes) {
    if (!list) return;
    printf("\n");
    for (int i = 0; i != vertexes; i++) {
        struct node* current = list + i;
        //printf("|%i\t|->", current->numNode);
        while (current) {
            printf("|%i|\t->", current->numNode);
            current = current->nextNode;
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    int vertexNum = 0, vertexStart = 0;
    printf("Колво вершин: ");
    scanf("%d", &vertexNum);
    printf("Начальная точка: ");
    
    if (!scanf("%d", &vertexStart) || vertexStart > vertexNum || vertexStart < 0) {
        printf("Нет такой вершины");
        return 0;
    }
        

    int* adjacencyMatrix = CreateGraph(vertexNum);
    ShowGraph(adjacencyMatrix, vertexNum);
    struct node* adjacencyList = (struct node*)malloc(sizeof(struct node) * vertexNum);
    

    breadthFirstSearchAdjacencyMatrix(adjacencyMatrix, vertexStart - 1, vertexNum);
    printf("\n");
    if (!ModifyGraph(adjacencyList, adjacencyMatrix, vertexNum)) return 1;
    ShowList(adjacencyList, vertexNum);
    breadthFirstSearchAdjacencyList(adjacencyList, vertexStart - 1, vertexNum);

    return 0;
}
