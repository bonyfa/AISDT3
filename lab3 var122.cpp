#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>

using namespace std;

struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats insertion(std::vector<int>& arr)
{
    // cout<<"In insert"<<endl;
    size_t n = arr.size();
    stats statics;
    for (size_t i = 1; i < n; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            ++statics.comparison_count;
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
                ++statics.copy_count;
            }
            else
                break;
        }
    }
    return statics;
}

void quick_sort(std::vector<int>& arr, int left, int right, stats& s)
{
    int i = left, j = right;
    int main = arr[left];
    while (i <= j)
    {
        while (arr[i] < main)
        {
            s.comparison_count++;
            i++;
        }
        while (arr[j] > main)
        {
            s.comparison_count++;
            j--;
        }
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
            s.copy_count++;
        }
    }

    if (left < j)
        quick_sort(arr, left, j, s);
    if (i < right)
        quick_sort(arr, i, right, s);
}
stats quick_sort(std::vector<int>& arr, int size)
{
    stats statistics;
    if (size < 2)
    {
        return statistics;
    }
    quick_sort(arr, 0, size - 1, statistics);
    return statistics;
}
void heapify(vector<int>& arr, size_t size, int i, stats& result) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    ++result.comparison_count;
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }
    ++result.comparison_count;
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        ++result.copy_count;
        heapify(arr, size, largest, result);
    }
}

stats heap_sort(vector<int>& arr)
{
    stats result;
    size_t size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i, result);

    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        ++result.copy_count;
        heapify(arr, i, 0, result);
    }
    return result;
}



std::vector<int> normal_vector(int size)
{
    std::vector<int> arr;
    for (int i = 0; i < size; ++i)
    {
        arr.push_back(i);
    }
    return arr;
}

std::vector<int> reverse_vector(int size)
{
    std::vector<int> arr;
    for (int i = size - 1; i >= 0; --i)
    {
        arr.push_back(i);
    }
    return arr;
}

std::vector<int> random_vector(int size)
{
    std::vector<int> arr;
    for (int i = 0; i < size; ++i)
    {
        arr.push_back(rand() % 100);
    }
    return arr;
}
template <class Iterator>
stats insertion(Iterator begin, Iterator end)
{
    stats statics;
    for (Iterator i = begin; i != end; ++i)
    {
        for (Iterator j = i; j != begin; --j)
        {
            ++statics.comparison_count;
            if (*j < *(j - 1))
            {
                swap(*j, *(j - 1));
                ++statics.copy_count;
            }
            else
                break;
        }
    }
    return statics;
}

template <class Iterator>
void quick_sort(Iterator begin, Iterator end, stats& s)
{
    if (distance(begin, end) < 2)
    {
        return;
    }
    Iterator i = begin;
    Iterator main = prev(end);
    Iterator pivot = next(begin, distance(begin, end) / 2);
    iter_swap(pivot, main);
    pivot = main;
    for (Iterator j = begin; j != main; ++j)
    {
        if (*j < *main)
        {
            if (*i != *j)
            {
                iter_swap(i, j);
                s.copy_count++;
            }
            ++i;
        }
        s.comparison_count++;
    }
    iter_swap(i, main);
    s.copy_count++;
    quick_sort(begin, i, s);
    quick_sort(next(i), end, s);
}

template <class Iterator>
stats quick_sort(Iterator begin, Iterator end)
{
    stats statistics;
    if (distance(begin, end) < 2)
    {
        return statistics;
    }
    quick_sort(begin, end, statistics);
    return statistics;
}


template <typename Iterator>
void heapify(Iterator begin, Iterator end, Iterator it, stats& result) {
    auto size = distance(begin, end);
    auto i = distance(begin, it);
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;
    ++result.comparison_count;
    if (left < size && *(begin + left) > *(begin + largest)) {
        largest = left;
    }
    ++result.comparison_count;
    if (right < size && *(begin + right) > *(begin + largest)) {
        largest = right;
    }

    if (largest != i) {
        iter_swap(it, begin + largest);
        ++result.copy_count;
        heapify(begin, end, begin + largest, result);
    }
}

template <typename Iterator>
stats heap_sort(Iterator begin, Iterator end) {
    stats result;
    auto size = distance(begin, end);

    for (auto i = size / 2 - 1; i >= 0; --i)
        heapify(begin, end, begin + i, result);

    for (auto i = size - 1; i >= 0; --i) {
        iter_swap(begin, begin + i);
        ++result.copy_count;
        heapify(begin, begin + i, begin, result);
    }
    return result;
}

#define SIZE 1000

using namespace std;

int main() {
    std::vector<int> v1{ 3,0,2,1,5,9,7 };
    std::vector<int> v2{ 3,0,2,1,5,9,7 };
    std::vector<int> v3{ 3,0,2,1,5,9,7 };
    stats s1 = insertion(v1);
    stats s2 = quick_sort(v2, v2.size());
    stats s3 = heap_sort(v3);
    
    cout << "Check sorts: " << endl;

    cout << "Insert: " << endl;
    for (int i = 0; i < v1.size(); ++i) {
        cout << v1[i] << " " << endl;
    }
    cout << "Comparision count: " << s1.comparison_count << endl;
    cout << "Copy count: " << s1.copy_count << endl;

    cout << "Qick: " << endl;
    for (int i = 0; i < v2.size(); ++i) {
        cout << v2[i] << " " << endl;
    }
    cout << "Comparision count: " << s2.comparison_count << endl;
    cout << "Copy count: " << s2.copy_count << endl;

    cout << "Heap sort: " << endl;
    for (int i = 0; i < v3.size(); ++i) {
        cout << v3[i] << " " << endl;
    }
    cout << "Comparision count: " << s3.comparison_count << endl;
    cout << "Copy count: " << s3.copy_count << endl;

    std::vector<int> v4{ 3,0,2,1,5,9,7 };
    std::vector<int> v5{ 3,0,2,1,5,9,7 };
    std::vector<int> v6{ 3,0,2,1,5,9,7 };


    cout << "Check Iterator: " << endl << "Insert sort" << endl;
    stats s4 = insertion(v4.begin(), v4.end());
    for (int i = 0; i < v4.size(); ++i) {
        cout << v4[i] << " " << endl;
    }
    cout << "Comparision count: " << s4.comparison_count << endl;
    cout << "Copy count: " << s4.copy_count << endl;

    cout << "Quick sort" << endl;
    stats s5 = quick_sort(v5.begin(), v5.end());
    for (int i = 0; i < v5.size(); ++i) {
        cout << v5[i] << " " << endl;
    }
    cout << "Comparision count: " << s5.comparison_count << endl;
    cout << "Copy count: " << s5.copy_count << endl;

    //Insertion 
    {
        cout << "Insertion sort" << endl;
        size_t comparision = 0, copy = 0;
        cout << "Insertion for 100 arrays" << endl;
        cout << "Size : " << SIZE << endl;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = random_vector(SIZE);
            stats s = insertion(arr.begin(), arr.end());
            comparision += s.comparison_count;
            copy += s.copy_count;
        }
        cout << "Avg comparision: " << comparision / 100 << endl;
        cout << "Avg copy: " << copy / 100 << endl;

        std::vector<int> arr1 = normal_vector(SIZE);
        stats s1 = insertion(arr1.begin(), arr1.end());
        cout << "Comparision: " << s1.comparison_count << endl;
        cout << "Copy: " << s1.copy_count << endl;

        std::vector<int> arr2 = reverse_vector(SIZE);
        stats s2 = insertion(arr2.begin(), arr2.end());
        cout << "Comparision: " << s2.comparison_count << endl;
        cout << "Copy: " << s2.copy_count << endl;
    }

    //Quick
    {
        cout << "Quick sort" << endl;
        size_t comparision = 0, copy = 0;
        cout << "Quick for 100 arrays" << endl;
        cout << "Size : " << SIZE << endl;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = random_vector(SIZE);
            stats s = quick_sort(arr.begin(), arr.end());
            comparision += s.comparison_count;
            copy += s.copy_count;
        }
        cout << "Avg comparision: " << comparision / 100 << endl;
        cout << "Avg copy: " << copy / 100 << endl;

        std::vector<int> arr1 = normal_vector(SIZE);
        stats s1 = quick_sort(arr1.begin(), arr1.end());
        cout << "Comparision: " << s1.comparison_count << endl;
        cout << "Copy: " << s1.copy_count << endl;

        std::vector<int> arr2 = reverse_vector(SIZE);
        stats s2 = quick_sort(arr2.begin(), arr2.end());
        cout << "Comparision: " << s2.comparison_count << endl;
        cout << "Copy: " << s2.copy_count << endl;
    }

    //heap_sort
    {
        cout << "Heap sort" << endl;
        size_t comparision = 0, copy = 0;
        cout << "Heap for 100 arrays" << endl;
        cout << "Size : " << SIZE << endl;
        for (int i = 0; i < 100; ++i) {
            std::vector<int> arr = random_vector(SIZE);
            stats s = heap_sort(arr);
            comparision += s.comparison_count;
            copy += s.copy_count;
        }
        cout << "Avg comparision: " << comparision / 100 << endl;
        cout << "Avg copy: " << copy / 100 << endl;

        std::vector<int> arr1 = normal_vector(SIZE);
        stats s1 = heap_sort(arr1);
        cout << "Comparision: " << s1.comparison_count << endl;
        cout << "Copy: " << s1.copy_count << endl;

        std::vector<int> arr2 = reverse_vector(SIZE);
        stats s2 = heap_sort(arr2);
        cout << "Comparision: " << s2.comparison_count << endl;
        cout << "Copy: " << s2.copy_count << endl;
}