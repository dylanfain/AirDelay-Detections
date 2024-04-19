#include <vector>

void heapify(std::vector<FlightData>& flightData, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && flightData[left].arrivalDelay > flightData[largest].arrivalDelay) {
        largest = left;
    }

    if (right < n && flightData[right].arrivalDelay > flightData[largest].arrivalDelay) {
        largest = right;
    }

    if (largest != i) {
        std::swap(flightData[i], flightData[largest]);
        heapify(flightData, n, largest);
    }
}

void heapSort(std::vector<FlightData>& flightData) {
    int n = flightData.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(flightData, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(flightData[0], flightData[i]);
        heapify(flightData, i, 0);
    }
}

// Helper function to merge two sorted subarrays
void merge(std::vector<FlightData>& flightData, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<FlightData> L(n1), R(n2);

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; ++i) {
        L[i] = flightData[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = flightData[middle + 1 + j];
    }

    // Merge the temp arrays back into flightData[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].arrivalDelay <= R[j].arrivalDelay) {
            flightData[k] = L[i++];
        } else {
            flightData[k] = R[j++];
        }
        ++k;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        flightData[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        flightData[k++] = R[j++];
    }
}

// Merge sort function
void mergeSort(std::vector<FlightData>& flightData, int left, int right) {
    if (left < right) {
        // Find the middle point
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(flightData, left, middle);
        mergeSort(flightData, middle + 1, right);

        // Merge the sorted halves
        merge(flightData, left, middle, right);
    }
}