#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define MAX_CODE 256

typedef struct Node {
    char symbol;
    long long freq;
    int minSymbol;
    int isLeaf;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *data[MAX];
    int size;
} MinHeap;

typedef struct {
    char symbol;
    long long freq;
    int length;
    char code[MAX_CODE];
} SymbolInfo;

/* Create a new node */
Node *createNode(char symbol, long long freq,
                 int isLeaf, Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->symbol = symbol;
    node->freq = freq;
    node->isLeaf = isLeaf;
    node->left = left;
    node->right = right;

    if (isLeaf) {
        node->minSymbol = (unsigned char)symbol;
    } else {
        node->minSymbol = left->minSymbol < right->minSymbol
                              ? left->minSymbol
                              : right->minSymbol;
    }

    return node;
}

/* Compare nodes deterministically */
int smaller(Node *a, Node *b) {
    if (a->freq != b->freq)
        return a->freq < b->freq;

    return a->minSymbol < b->minSymbol;
}

/* Insert a node into the min-heap */
void insertHeap(MinHeap *heap, Node *node) {
    int i = heap->size++;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (!smaller(node, heap->data[parent]))
            break;

        heap->data[i] = heap->data[parent];
        i = parent;
    }

    heap->data[i] = node;
}

/* Remove and return the minimum node */
Node *extractMin(MinHeap *heap) {
    Node *minimum = heap->data[0];
    Node *last = heap->data[--heap->size];

    if (heap->size == 0)
        return minimum;

    int i = 0;

    while (2 * i + 1 < heap->size) {
        int child = 2 * i + 1;

        if (child + 1 < heap->size &&
            smaller(heap->data[child + 1],
                    heap->data[child])) {
            child++;
        }

        if (!smaller(heap->data[child], last))
            break;

        heap->data[i] = heap->data[child];
        i = child;
    }

    heap->data[i] = last;

    return minimum;
}

/* Calculate Huffman code lengths */
void calculateLengths(Node *root, int depth,
                      SymbolInfo info[], int *count) {
    if (root == NULL)
        return;

    if (root->isLeaf) {
        info[*count].symbol = root->symbol;
        info[*count].freq = root->freq;

        /*
         * A single-symbol alphabet is assigned
         * a one-bit code instead of an empty code.
         */
        info[*count].length = depth == 0 ? 1 : depth;

        (*count)++;
        return;
    }

    calculateLengths(root->left, depth + 1, info, count);
    calculateLengths(root->right, depth + 1, info, count);
}

/* Sort symbols by code length, then symbol */
int compareSymbols(const void *a, const void *b) {
    const SymbolInfo *x = (const SymbolInfo *)a;
    const SymbolInfo *y = (const SymbolInfo *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol -
           (unsigned char)y->symbol;
}

/* Increment a binary code */
int incrementCode(char code[], int length) {
    int i = length - 1;

    while (i >= 0 && code[i] == '1') {
        code[i] = '0';
        i--;
    }

    if (i < 0)
        return 0;

    code[i] = '1';
    return 1;
}

/* Generate canonical Huffman codes */
void generateCanonicalCodes(SymbolInfo info[], int n) {
    qsort(info, n, sizeof(SymbolInfo), compareSymbols);

    /*
     * The first code is all zeros.
     */
    memset(info[0].code, '0', info[0].length);
    info[0].code[info[0].length] = '\0';

    for (int i = 1; i < n; i++) {
        int previousLength = info[i - 1].length;
        int currentLength = info[i].length;

        strcpy(info[i].code, info[i - 1].code);

        if (!incrementCode(info[i].code, previousLength)) {
            printf("Invalid code lengths.\n");
            exit(1);
        }

        if (currentLength < previousLength) {
            printf("Invalid code lengths.\n");
            exit(1);
        }

        for (int j = previousLength; j < currentLength; j++)
            info[i].code[j] = '0';

        info[i].code[currentLength] = '\0';
    }
}

/* Free allocated tree memory */
void freeTree(Node *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    int n;
    MinHeap heap = {.size = 0};
    SymbolInfo info[MAX];

    printf("Enter number of symbols (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    int seen[256] = {0};

    printf("Enter each symbol and its positive frequency:\n");

    for (int i = 0; i < n; i++) {
        char symbol;
        long long freq;

        if (scanf(" %c %lld", &symbol, &freq) != 2 ||
            freq <= 0 || seen[(unsigned char)symbol]) {
            printf("Invalid input or duplicate symbol.\n");
            return 1;
        }

        seen[(unsigned char)symbol] = 1;

        Node *node = createNode(symbol, freq, 1, NULL, NULL);
        insertHeap(&heap, node);
    }

    /* Build the Huffman tree */
    while (heap.size > 1) {
        Node *left = extractMin(&heap);
        Node *right = extractMin(&heap);

        if (left->freq > 0 &&
            right->freq > __LONG_LONG_MAX__ - left->freq) {
            printf("Frequency sum overflow.\n");
            freeTree(left);
            freeTree(right);

            while (heap.size > 0)
                freeTree(extractMin(&heap));

            return 1;
        }

        Node *parent = createNode(
            '\0',
            left->freq + right->freq,
            0,
            left,
            right
        );

        insertHeap(&heap, parent);
    }

    Node *root = extractMin(&heap);

    /* Calculate code lengths */
    int count = 0;
    calculateLengths(root, 0, info, &count);

    /* Generate canonical codes */
    generateCanonicalCodes(info, count);

    printf("\nCanonical Huffman Codebook:\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    long long totalCost = 0;

    for (int i = 0; i < count; i++) {
        printf("%c\t%lld\t\t%d\t%s\n",
               info[i].symbol,
               info[i].freq,
               info[i].length,
               info[i].code);

        totalCost += info[i].freq * info[i].length;
    }

    printf("\nWeighted path length: %lld\n", totalCost);

    freeTree(root);

    return 0;
}