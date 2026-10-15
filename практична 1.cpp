#include <iostream>
#include <iomanip>
using namespace std;

int linearSearch(const int a[], int n, int key, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (a[i] == key) return i;
    }
    return -1;
}

int binarySearch(const int a[], int n, int key, int& comparisons) {
    int left = 0, right = n - 1;
    comparisons = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (a[mid] == key) return mid;
        if (a[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void printSearch(const int a[], int n, int key, bool binary) {
    int comparisons;
    int index = binary ? binarySearch(a, n, key, comparisons)
        : linearSearch(a, n, key, comparisons);
    cout << "Ключ: " << key << ", індекс: " << index
        << ", порівнянь: " << comparisons << '\n';
}

int main() {
    setlocale(LC_ALL, "");
    const int n = 7;
    int a[n] = { 19, 37, 5, 23, 14, 1, 30 };
    int sorted[n] = { 1, 5, 14, 19, 23, 30, 37 };
    int keys[3] = { 5, 30, 22 };
    cout << "ПРАКТИЧНА РОБОТА №1. ВАРІАНТ 7\n";
    cout << "\nЗавдання 1. Прямий пошук\n";
    for (int key : keys) printSearch(a, n, key, false);
    cout << "\nЗавдання 2. Бінарний пошук\n";
    for (int key : keys) printSearch(sorted, n, key, true);

    cout << "\nЗавдання 3. Автоматизовані перевірки\n";
    int one[1] = { 8 }, two[5] = { 3, 6, 9, 11, 20 };
    int testKeys[12] = { 8, 3, 3, 9, 20, 10, 1, 25, 8, 5, 30, 22 };
    int expected[12] = { 0, -1, 0, 2, 4, -1, -1, -1, -1, 1, 5, -1 };
    for (int t = 0; t < 12; t++) {
        int comparisons = 0, result;
        if (t == 0) result = binarySearch(one, 1, testKeys[t], comparisons);
        else if (t == 1) result = binarySearch(one, 1, testKeys[t], comparisons);
        else if (t == 8) result = binarySearch(two, 0, testKeys[t], comparisons);
        else if (t >= 9) result = binarySearch(sorted, n, testKeys[t], comparisons);
        else result = binarySearch(two, 5, testKeys[t], comparisons);
        cout << "Тест " << t + 1 << ": " << (result == expected[t] ? "Успішно" : "Помилка") << '\n';
    }

    cout << "\nЗавдання 4. Порівняльний експеримент\n";
    int sizes[4] = { 10, 100, 1000, 100000 };
    for (int size : sizes) {
        int* data = new int[size];
        for (int i = 0; i < size; i++) data[i] = i;
        for (int scenario = 0; scenario < 3; scenario++) {
            int key = scenario == 0 ? 0 : (scenario == 1 ? size - 1 : size);
            int c1, c2;
            linearSearch(data, size, key, c1);
            binarySearch(data, size, key, c2);
            cout << "n=" << size << "  " << char('A' + scenario)
                << "  прямий=" << c1 << "  бінарний=" << c2 << '\n';
        }
        cout << "\nЗавдання 5. Середні значення, n=" << size << '\n';
        long long sum1 = 0, sum2 = 0;
        for (int i = 0; i < 1000; i++) {
            int key = (i * 37) % size, c1, c2;
            linearSearch(data, size, key, c1);
            binarySearch(data, size, key, c2);
            sum1 += c1;
            sum2 += c2;
        }
        cout << fixed << setprecision(3) << "Прямий=" << sum1 / 1000.0
            << "  бінарний=" << sum2 / 1000.0 << '\n';
        delete[] data;
    }

    cout << "\nЗавдання 6. Невпорядкований масив\n";
    int wrong[6] = { 12, 3, 19, 5, 8, 1 };
    int right[6] = { 1, 3, 5, 8, 12, 19 };
    for (int key : wrong) {
        int c1, c2;
        int before = binarySearch(wrong, 6, key, c1);
        int after = binarySearch(right, 6, key, c2);
        cout << "Ключ " << key << ": до=" << before << ", після=" << after << '\n';
    }
}