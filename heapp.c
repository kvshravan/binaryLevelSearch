#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
void heapify(int *,int,int);
void swap(int,int,int *);
void buildmaxheap(int *,int);
int n,*level;
void heapsort(int *x,int n){
	int i;
	buildmaxheap(x,n);
	for(i=n-1;i>=0;i--){
		swap(0,i,x);
		heapify(x,i,0);
	}
}
void buildmaxheap(int *x,int n){
	int i;
	for(i=n/2-1;i>=0;i--)
	heapify(x,n,i);
}

void heapify(int *x,int n,int i){
	int l = 2*i+1;
	int r = 2*i+2;
	int largest = i;
	if(l<n && x[i]<x[l])
	largest = l;
	if(r<n && x[r]>x[largest])
	largest =r;
	if(largest!=i){
	swap(i,largest,x);
	heapify(x,n,largest);
}
}
void swap(int a,int b,int *x){
	int temp = x[b];
	x[b] = x[a];
	x[a] = temp;
}
int levelSearch(int *x,int low,int high,int key,int startOffset,int endOffset,int prevmid){
	if(low<=high){
		int iStart,iEnd,i,upQuery,downQuery;
		double val;
		bool dFlag = false,uFlag = false;
		int mid = ceil((double)(low+high)/2);
		val = (double)(level[mid]+1)/(double)(level[prevmid]+1);
		iStart = level[mid]+val*startOffset;
		iEnd= iStart+(double)(val*(endOffset+1))-1;
		upQuery = downQuery = iStart-1;
		for(i=iStart;i<=iEnd;i++){
	 	if(x[i] >key){
			downQuery++;
			dFlag=true;
			if(uFlag){
			levelSearch(x,low,mid-1,key,downQuery-iStart,i-1-iStart,mid);
			upQuery = i-1,downQuery = i;
			uFlag = false;
			}
		}
		else if(x[i] < key){
			upQuery++;
			uFlag=true;
			if(dFlag){
			levelSearch(x,mid+1,high,key,upQuery-iStart,i-1-iStart,mid);
			downQuery = i-1,upQuery = i;
			dFlag = false;
			}
		}
		else{
			return i;
			break;
		}
		}
		if(dFlag)
		levelSearch(x,mid+1,high,key,upQuery+1-iStart,level[mid+1]-level[mid]-1,mid);
		else
		levelSearch(x,low,mid-1,key,downQuery+1-iStart,upQuery-iStart,mid);
		
	}
}
int main(){
	int *x,i,level_max,j,T=1,ans;
	n=134217728;
	while(T--){
	x=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	x[i] = rand()%n;

	//heapsort(x,n);
//	printf("bleh");
	buildmaxheap(x,n);
	level_max = ceil(log2(n) -1);
	level = (int *)malloc((level_max+2)*sizeof(int));
	level[level_max] = n>>1,level[level_max+1] = n;
	for(i=level_max-1;i>=0;i--)
	level[i] = level[i+1]>>1;
//	scanf("%d",&i);
	//for(i=0;i<n;i++)
	//printf("\t %d ",x[i]);
	i=x[2839223];
	int mid = ceil((double)(level_max)/2);
	//printf("mid %d\n",mid);
	ans = levelSearch(x,0,level_max,i,0,level[mid+1]-level[mid]-1,mid);
	printf(" %d %d %d\n",i,ans,x[ans]);
//	for(j=0;j<n;j++)
//	if(x[j]==i){
//	printf("%d %d %d",i,j,x[j]);
//	break;
//	}
	free(x);
//	for(i=0;i<n;i++)
//	if(x[i]==0)
//	printf("\n*%d*\n",i);
	//scanf("%d",&i);
	//printf("%d\n",search_heap(x,n,i));
	
}
}
