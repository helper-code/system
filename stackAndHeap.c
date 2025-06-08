#include <stdio.h>
#include <stdlib.h> // For malloc, free

// Function to demonstrate stack allocation
void stackExample() {
    int stackVar = 10; // allocated on stack
    printf("Stack Variable Value: %d\n", stackVar);
    printf("Address of Stack Variable: %p\n", (void*)&stackVar);
}

// Function to demonstrate heap allocation
void heapExample() {
    int *heapVar = (int *)malloc(sizeof(int)); // allocated on heap

    if (heapVar == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    *heapVar = 20;
    printf("Heap Variable Value: %d\n", *heapVar);
    printf("Address of Heap Variable: %p\n", (void*)heapVar);

    free(heapVar); // free the allocated memory
}

// Function causing stack overflow (dangerous!)
void triggerStackOverflow(int counter) {
    printf("Stack depth: %d\n", counter);
    triggerStackOverflow(counter + 1); // Infinite recursion
}

int main() {
    printf("===== Stack Memory Example =====\n");
    stackExample();
    // 'stackVar' no longer exists here (stack memory reclaimed)

    printf("\n===== Heap Memory Example =====\n");
    heapExample();

    printf("\n===== Dynamic Array on Heap =====\n");
    int size = 5;
    int *dynamicArray = (int *)malloc(size * sizeof(int)); // Heap array
    if (dynamicArray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 10; // Initialize
    }
    printf("Dynamic array values: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamicArray[i]);
    }
    free(dynamicArray); // Free heap array

    printf("\n\n===== Stack Overflow Example (Uncomment to crash) =====\n");
    // triggerStackOverflow(1); // Uncomment to see stack overflow

    printf("\n===== Memory Leak Demo (Comment out free to leak) =====\n");
    int *leakyPtr = (int *)malloc(sizeof(int));
    *leakyPtr = 123;
    printf("Leaky pointer value: %d\n", *leakyPtr);
    // free(leakyPtr); // Uncomment to fix the leak

    return 0;
}