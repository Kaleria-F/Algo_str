#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <fstream>

class StringGenerator {
public:
    StringGenerator() {
        //заглавные и строчные латинские буквы A-Z, a-z
        //цифры 0-9
        //дополнительные символы !@#%:;^&*()-
        characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";
    }

    ///Генерация случайной строки определеннной  длины
    ///@param length - длина строки
    std::string generate(int length) {
        std::string result; // - резултат генерации
        std::random_device rd; //- генератор случайных чисел (??? уточнить можно ли использовать)
        std::mt19937 generator(rd()); //-генератор случайных чисел

        //Цикл генерации строки:
        for (int i = 0; i < length; i++) {
            std::uniform_int_distribution<> distribution(0, characters.size() - 1);
            result += characters[distribution(generator)];
        }

        return result;
    }

    ///Генерация массива случайных строк
    ///@param size - размер массива
    ///@param min_length - минимальная длина строки
    ///@param max_length - максимальная длина строки
    ///@return массив случайных строк
    std::vector<std::string> generateArray(int size, int min_length, int max_length) {
        std::vector<std::string> result; // - резултат генерации
        std::random_device rd; //- генератор случайных чисел
        std::mt19937 generator(rd()); //-генератор случайных чисел

        //Цикл генерации массива строк:
        for (int i = 0; i < size; i++) {
            std::uniform_int_distribution<> length_distribution(min_length, max_length);
            result.push_back(generate(length_distribution(generator)));
        }

        return result;
    }

    ///Генерация отсортированного массива случайных строк
    ///@param size - размер массива
    ///@param min_length - минимальная длина строки
    ///@param max_length - максимальная длина строки
    ///@return отсортированный массив случайных строк
    std::vector<std::string> generateUnsortedArray(int size, int min_length, int max_length) {
        return generateArray(size, min_length, max_length);
    }

    ///Генерация отсортированного массива случайных строк в обратном порядке
    ///@param size - размер массива
    ///@param min_length - минимальная длина строки
    ///@param max_length - максимальная длина строки
    ///@return отсортированный массив случайных строк в обратном порядке
    std::vector<std::string> generateReverseSortedArray(int size, int min_length, int max_length) {
        std::vector<std::string> result = generateArray(size, min_length, max_length);
        std::sort(result.rbegin(), result.rend());
        return result;
    }

    ///Генерация почти отсортированного массива случайных строк
    ///@param size - размер массива
    ///@param min_length - минимальная длина строки
    ///@param max_length - максимальная длина строки
    ///@return почти отсортированный массив случайных строк
    std::vector<std::string> generateAlmostSortedArray(int size, int min_length, int max_length) {
        std::vector<std::string> result = generateArray(size, min_length, max_length);
        std::sort(result.begin(), result.end());

        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, size - 1);

        for (int i = 0; i < size / 10; i++) {
            int index1 = distribution(generator);
            int index2 = distribution(generator);
            std::swap(result[index1], result[index2]);
        }

        return result;
    }

    std::vector<std::string> getSubArray(const std::vector<std::string>& array, int size) {
        if (size > array.size()) {
            throw std::invalid_argument("!!!Size incorrect!!!");
        }
        return std::vector<std::string>(array.begin(), array.begin() + size);
    }



private:
    std::string characters;
};

//_______________________________________________________________________________
// Для QUICKSORT
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

int main() {
    std::ofstream file("results_qs.csv");
    file << "Size,U,RS,AS\n";

    StringGenerator generator;
    int maxSize = 3000; // - макс размер массива
    int minStrLength = 10; // - мин длина строки
    int maxStrLength = 200; // - макс длина строки

    //Генерация трех массивов:
    std::vector<std::string> unsortedArray = generator.generateUnsortedArray(maxSize, minStrLength, maxStrLength);
    std::vector<std::string> reverseSortedArray = generator.generateReverseSortedArray(maxSize, minStrLength, maxStrLength);
    std::vector<std::string> almostSortedArray = generator.generateAlmostSortedArray(maxSize, minStrLength, maxStrLength);

    //в цикле замеряю время для каждого массива
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

    file.close();

    return 0;
}
