#include <stdio.h>
void swap(int *x,int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void bubbleSort(int A[],int n)
{
	for(int i = 0; i < n - 1;i++)
		{
			for(int j = 0; j < n - 1 - i;j++)
			{
				if(A[j]>A[j+1])
				swap(&A[j],&A[j+1]);
			}
		}
}

int main()
{
	int A[] = {3,7,9,10,6,5,12,4,11,2};
	int n = sizeof(A)/sizeof(A[0]);
	bubbleSort(A,n);

	for(int i=0;i<n;i++)
	printf("%d ",A[i]);
}
