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