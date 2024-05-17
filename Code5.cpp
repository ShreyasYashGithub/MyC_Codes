#include <stdio.h>
#include <stdlib.h>


struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left;
    struct SYMBOL *right;
};


struct MinHeapNode {
    struct SYMBOL *symbol;
};


struct MinHeapNode* createMinHeapNode(struct SYMBOL *symbol) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->symbol = symbol;
    return node;
}


void swapMinHeapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}


void minHeapify(struct MinHeapNode** minHeap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && minHeap[left]->symbol->frequency < minHeap[smallest]->symbol->frequency)
        smallest = left;

    if (right < size && minHeap[right]->symbol->frequency < minHeap[smallest]->symbol->frequency)
        smallest = right;

    if (smallest != index) {
        swapMinHeapNodes(&minHeap[index], &minHeap[smallest]);
        minHeapify(minHeap, size, smallest);
    }
}


struct MinHeapNode* buildHuffmanTree(struct SYMBOL* symbols[], int size) {
    struct MinHeapNode* minHeap[size];
    int i;
    for (i = 0; i < size; i++) {
        minHeap[i] = createMinHeapNode(symbols[i]);
    }

    int heapSize = size;
    while (heapSize > 1) {
        struct MinHeapNode* left = minHeap[0];
        minHeap[0] = minHeap[heapSize - 1];
        heapSize--;
        minHeapify(minHeap, heapSize, 0);

        struct MinHeapNode* right = minHeap[0];
        minHeap[0] = createMinHeapNode(NULL);
        minHeap[0]->symbol = (struct SYMBOL*)malloc(sizeof(struct SYMBOL));
        minHeap[0]->symbol->frequency = left->symbol->frequency + right->symbol->frequency;
        minHeap[0]->symbol->alphabet = '-';
        minHeap[0]->symbol->left = left->symbol;
        minHeap[0]->symbol->right = right->symbol;

        minHeapify(minHeap, heapSize, 0);
    }
    return minHeap[0];
}


void inorderTraversal(struct SYMBOL* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        if (root->alphabet != '-')
            printf("%c ", root->alphabet);
        inorderTraversal(root->right);
    }
}

int main() {
    int numAlphabets;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &numAlphabets);

    struct SYMBOL* symbols[numAlphabets];

    printf("Enter the alphabets: ");
    for (int i = 0; i < numAlphabets; i++) {
        symbols[i] = (struct SYMBOL*)malloc(sizeof(struct SYMBOL));
        scanf(" %c", &(symbols[i]->alphabet));
    }

    printf("Enter their frequencies: ");
    for (int i = 0; i < numAlphabets; i++) {
        scanf("%d", &(symbols[i]->frequency));
        symbols[i]->left = NULL;
        symbols[i]->right = NULL;
    }

    struct MinHeapNode* root = buildHuffmanTree(symbols, numAlphabets);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root->symbol);
    printf("\n");

    return 0;
}

