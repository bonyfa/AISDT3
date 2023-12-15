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

}