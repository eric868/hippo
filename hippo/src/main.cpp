#include <iostream>
#include <string>
#include "dictionary.h"

using namespace std;

void bubble_sort(std::vector<int>& nums)
{
	int size = nums.size();
	for (int i = 0; i < size; ++i)
	{
		bool ischange = false;
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (nums[j] > nums[j + 1])
			{
				int tmp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;

				ischange = true;
			}
		}

		if (!ischange) break;
	}
}


struct CmpTest
{
	char    a;
	short   b;
	int*     c;
	char    d;
};


int main()
{
	CmpTest t, t1;
	t.c = new int(10);
	t1.c = new int(10);
	int i = memcmp(&t, &t1, sizeof(CmpTest));

	getchar();
	return 0;
}