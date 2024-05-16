//STRING QUICKSORT
int partition (std::vector<std::string>& arr, int low, int high) {
    std::string pivot = arr[high];
    int i = (low - 1);

    //сортирока
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<std::string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        //рекурсивный вызов для сортировки элементов до и после разделителя
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
