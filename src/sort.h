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