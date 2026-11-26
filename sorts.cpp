#include <iostream>
#include <ctime>


void insertsort(int array[], int n) {
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void heapify(int array[], int n, int i) {
    int mayor = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[mayor])
        mayor = left;

    if (right < n && array[right] > array[mayor])
        mayor = right;

    if (mayor != i) {
        std::swap(array[i], array[mayor]);
        heapify(array, n, mayor);
    }
}

void heapsort(int array[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int partition(int array[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (array[mid] < array[low])
        std::swap(array[low], array[mid]);
    if (array[high] < array[low])
        std::swap(array[low], array[high]);
    if (array[mid] < array[high])
        std::swap(array[mid], array[high]);

    int pivot = array[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return i + 1;
}

void quicksort(int array[], int low, int high) {
    while (low < high) {
        if (high - low < 10) {
            insertsort(array + low, high - low + 1);
            return;
        }
        
        int pivot = partition(array, low, high);
        

        if (pivot - low < high - pivot) {
            quicksort(array, low, pivot - 1);
            low = pivot + 1;
        } else {
            quicksort(array, pivot + 1, high);
            high = pivot - 1;
        }
    }
}


void bubblesort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; 
    }
}


void selectionsort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        if (min != i) {
            std::swap(array[i], array[min]);
        }
    }
}

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergesort_helper(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort_helper(array, left, mid);
        mergesort_helper(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void mergesort(int array[], int n) {
    mergesort_helper(array, 0, n - 1);
}

int main() {
    const int n = 500;
    int* arreglo = new int[n];

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < n; i++) {
        arreglo[i] = rand() % 1000;
    }

    std::cout << "Tipos de Sort y Su Tiempo de Ejecucion\n"
              << "1. BubbleSort\n"
              << "2. SelectionSort\n"
              << "3. InsertSort\n"
              << "4. QuickSort\n"
              << "5. MergeSort\n"
              << "6. HeapSort\n"
              << "Opcion deseada: ";
    
    int entrada;
    std::cin >> entrada;

    clock_t t0, t1;

    switch(entrada) {
        case 1:
            std::cout << "Utilizando BubbleSort para ordenar..." << std::endl;
            t0 = clock();
            bubblesort(arreglo, n);
            t1 = clock();
            break;

        case 2:
            std::cout << "Utilizando SelectionSort para ordenar..." << std::endl;
            t0 = clock();
            selectionsort(arreglo, n);
            t1 = clock();
            break;

        case 3:
            std::cout << "Utilizando InsertSort para ordenar..." << std::endl;
            t0 = clock();
            insertsort(arreglo, n);
            t1 = clock();
            break;

        case 4:
            std::cout << "Utilizando QuickSort para ordenar..." << std::endl;
            t0 = clock();
            quicksort(arreglo, 0, n - 1);
            t1 = clock();
            break;

        case 5:
            std::cout << "Utilizando MergeSort para ordenar..." << std::endl;
            t0 = clock();
            mergesort(arreglo, n);
            t1 = clock();
            break;

        case 6:
            std::cout << "Utilizando HeapSort para ordenar..." << std::endl;
            t0 = clock();
            heapsort(arreglo, n);
            t1 = clock();
            break;

        default:
            std::cout << "Opcion invalida" << std::endl;
            delete[] arreglo;
            return 1;
    }

    double time = static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion: " << time << " segundos" << std::endl;

    delete[] arreglo;
    return 0;
}