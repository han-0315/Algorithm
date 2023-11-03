#include <memory>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
	int arr[10];
	for (int i = 1; i <= 10; i++)
		arr[i - 1] = i;
	// memset(arr, 0, sizeof(arr));
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
}