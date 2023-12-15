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



#define SIZE 1000

using namespace std;

int main() {
    std::vector<int> v1{ 3,0,2,1,5,9,7 };
    stats s1 = insertion(v1);
    
    cout << "Check sorts: " << endl;

    cout << "Insert: " << endl;
    for (int i = 0; i < v1.size(); ++i) {
        cout << v1[i] << " " << endl;
    }
    cout << "Comparision count: " << s1.comparison_count << endl;
    cout << "Copy count: " << s1.copy_count << endl;

}