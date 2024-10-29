#include <iostream>
#include <vector>
#include <random>
//#include <math.h>

using namespace std;

void printVec(vector<double>* vec)
{
	for (int i = 0; i < vec->size(); i++)
	{
		cout << &vec[i] << " ";
	}
}

int main()
{
	srand(time(0));	
	int n = 10;
	int m = 12;

	vector<double> a(n - 1, 0);
	vector<double> b(n - 1, 0);
	vector<double> c(n, 0);

	for (int i = 0; i < n - 1; i++)
	{
		a[i] = rand() % 201 - 100.0;
		b[i] = rand() % 201 - 100.0;
	}
	c[0] = rand() % (m + 1) + m + b[0];
	c[n - 1] = rand() % (m + 1) + m + a[n - 2];
	for (int i = 1; i <= n - 2; i++)
	{
		c[i] = rand() % (m + 1) + m + b[i] + a[i];
	}
	printVec(a);
	printVec(b);
	printVec(c);


	return 0;
}