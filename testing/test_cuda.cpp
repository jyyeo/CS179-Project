#include <cstdlib>

#include "addVec.cu"

int main(int argc, char const *argv[])
{
	float arr1[10], arr2[10], arr3[10];
	for (int i = 0, i < 10, i++) {
		arr1[i] = i + 0.5;
		arr2[i] = i - 0.5;
		arr3[i] = 0.0;
		printf("%f\n", arr1[i]+arr2[i]);
	}
	return 0;
}