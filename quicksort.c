#include <stdio.h>
void swap(int *a, int *b) {
int t = *a;
*a = *b;
*b = t;
}
int median(int array[], int low, int high) {
int pivot;
int mid = (low + high) / 2;
if (array[mid] < array[low])
swap(&array[mid], &array[low]);
if (array[high] < array[low])
swap(&array[high], &array[low]);
if (array[high] < array[mid])
swap(&array[high], &array[mid]);
swap(&array[mid], &array[high-1]);
pivot = array[high-1];
return array[high-1];
}
void quickSort( int a[], int left, int right){
int pivot, i, j, t;
if (left <=right){
pivot = median( a, left, right );
i = left;
j = right-1;
while(i<j){
while(a[i]<=pivot && i<=right)
i++;
while( a[j] > pivot )
j--;
if( i < j )
swap( &a[i], &a[j] );
else break;
}
swap( &a[i], &a[right]);
quickSort( a, left, i-1);
quickSort( a, i+1, right);
}}
int main(){
int a[30],n,i;
printf("\nNo. of Elements: ");
scanf("%d",&n);
printf("Enter Array Elements: ");
printf("\n");
i=0;
do{
scanf("%d",&a[i]);
i++;
}while(getchar()!='\n' && i<n);
quickSort(a,0,n-1);
printf("Sorted Array (Quick Sort): ");
printf("\n");
for(i=0;i<n;i++)
printf("%d ",a[i]);
return 0;
}
