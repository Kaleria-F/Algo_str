# Решение задачи A1 Set3 по курсу АиСД

## 📌ссылки:

_____________________
### Этап 1. Подготовка тестовых данных:

1) сначала написала код для генерации строк и массивов

   [📎 код генерации](generate.cpp)

___________________
### Этап 2. Анализ неспециализированных алгоритмов сортировки:

#### **QUICKSORT**

* дополнила код:

  [📎 код](A1_quickSort.cpp)
  
1) добавила `#include <chrono>` - для замера времени
2) код для сортировки:
  ```
  void swap(std::string* a, std::string* b) {
    std::string t = *a;
    *a = *b;
    *b = t;
}

int partition (std::vector<std::string>& arr, int low, int high) {
    std::string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(std::vector<std::string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
  ```
3) допонила main так, чтобы щамерялось время раьботы алгоритма на каждом расзмере массива от 100 до 3000 с шагом 100:
  ```
      //в цикле замеряю время для каждого массива
    for (int size = 100; size <= maxSize; size += 100) {
        std::vector<std::string> subUnsortedArray = generator.getSubArray(unsortedArray, size);
        std::vector<std::string> subReverseSortedArray = generator.getSubArray(reverseSortedArray, size);
        std::vector<std::string> subAlmostSortedArray = generator.getSubArray(almostSortedArray, size);

        auto start = std::chrono::high_resolution_clock::now();
        quickSort(subUnsortedArray, 0, subUnsortedArray.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "U  array - size: " << size << ", time: " << diff.count()  << std::endl;

        start = std::chrono::high_resolution_clock::now();
        quickSort(subReverseSortedArray, 0, subReverseSortedArray.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        std::cout << "RS array - size: " << size << ", time: " << diff.count() << std::endl;

        start = std::chrono::high_resolution_clock::now();
        quickSort(subAlmostSortedArray, 0, subAlmostSortedArray.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        std::cout << "AS array - size: " << size << ", time: " << diff.count() << std::endl;
    }
  ```

4) позже переписала код, чтобы результаты созранялись в таблицу, для дальнейшего анализа:


   * открытие и название столбцов
     ```
     std::ofstream file("results_qs.csv");
     file << "Size,U,RS,AS\n";
     ```
     
   * изменение цикла и добавление вывода в файл
     
   ```
       for (int size = 100; size <= maxSize; size += 100) {
        std::vector<std::string> subUnsortedArray = generator.getSubArray(unsortedArray, size);
        std::vector<std::string> subReverseSortedArray = generator.getSubArray(reverseSortedArray, size);
        std::vector<std::string> subAlmostSortedArray = generator.getSubArray(almostSortedArray, size);

        file << size << ",";

        auto start = std::chrono::high_resolution_clock::now();
        quickSort(subUnsortedArray, 0, subUnsortedArray.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        file << diff.count() << ",";

        start = std::chrono::high_resolution_clock::now();
        quickSort(subReverseSortedArray, 0, subReverseSortedArray.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        file << diff.count() << ",";

        start = std::chrono::high_resolution_clock::now();
        quickSort(subAlmostSortedArray, 0, subAlmostSortedArray.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        file << diff.count() << "\n";
    }
   ```

Вывод в консоль выгдядел так:
![image](https://github.com/Kaleria-F/Algo_str/assets/113393162/07dc96d5-1d1c-41b2-b8ab-c727458df985)



