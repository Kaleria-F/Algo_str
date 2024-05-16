# Решение задачи A1 Set3 по курсу АиСД

## 📌ссылки:

* [Реализацию StringGenerator](generate.cpp)
* [Тестовые данные]()
* Реализацию специализированных алгоритмов сортировки строк
   * [STRING QUICKSORT](algo/str_quickSort.cpp)
   * [STRING MERGESORT](algo/str_mergeSort.cpp)
   * SD RADIX SORT без переключения на STRING QUICKSORT
   * MSD RADIX SORT с переключением на STRING QUICKSORT
* [Данные замеров времени и количества проведенных посимвольных сравнений](results_data)
* [Графики, иллюстрирующие проведенные замеры](Результаты_графики.md)
* Выводы по результатам проведенного эмпирического анализа

* [код на питоне для создания графиков](python/p1)
* [код на питоне для работы с таблицами](python/p2)
_____________________
### Этап 1. Подготовка тестовых данных:

1) сначала написала код для генерации строк и массивов

   [📎 код генерации](generate.cpp)

___________________
### Этап 2. Анализ неспециализированных алгоритмов сортировки:

## **QUICKSORT**

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


   * открытие файла, название столбцов
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

💻 Вывод в консоль выгдядел так:
![image](https://github.com/Kaleria-F/Algo_str/assets/113393162/07dc96d5-1d1c-41b2-b8ab-c727458df985)

📁[результаты](results_data/results_qs.csv)



## **MergeSort**

* дополнила код:

  [📎 код](A1_mergeSort.cpp)

1) функция:
   ```
   void mergeSort(std::vector<std::string> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
   }
   ```
   Для реализации функции, также прописала: 
   
   ```
   void merge(std::vector<std::string> &arr, int left, int mid, int right) {
    int i, j, k; //счетчики
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::string> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
   }   
   ```
📁[результаты](results_data/results_ms.csv)


