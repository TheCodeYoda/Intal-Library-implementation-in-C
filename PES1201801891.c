#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "intal.h"

#define max(a,b) a>b?a:b

static void swap_n(char** s1, char** s2)
{
    char* temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

static void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

static char* strrev(const char* s) 
{ 
	int n = strlen(s); 
	char *rev = malloc(sizeof(char) * (n + 1));
	strcpy(rev, s); 
    for (int i=0, j=n-1; i<j; i++,j--) 
		swap(&rev[i], &rev[j]);        
	return rev; 
} 

static int td(char a) {
	int b = a - '0';
	return b;
}

static char ts(int a) {
	char b= (char)(a+48);
	return b;
}

static char *strip(char *a) {
	int n=strlen(a);
	int s;
	for(int i=0;i<n;i++) {
		if(a[i]!='0') {
			s=i;
			break;
		}
	}
	if(s!=0) {
		for(int i=s;i<=n;i++)
			a[i-s]=a[i];
	}
	return a;
}


char* intal_add(const char* intal1,const char* intal2) {
	int n1=strlen(intal1);
	int n2=strlen(intal2);
	int k;
	if(n1>n2) k=n1;
	else k=n2;
	char *res=malloc(sizeof(char)*(k+2));
	res[k+1]='\0';
	int i=n1-1;
	int j=n2-1;
	int l=k;
	int carry=0;
	while(i>=0 && j>=0) {
		int a=td(intal1[i]);
		int b=td(intal2[j]);
		int ans=(a+b+carry)%10;
		res[l]=ts(ans);
		//printf("\n%d+%d=%c %d",a,b,res[l],l);
		carry=(a+b+carry)/10;
		i--;
		j--;
		l--;
	}
	while(i>=0) {
		int a=td(intal1[i]);
		int ans=(a+carry)%10;
		res[l]=ts(ans);
		carry=(a+carry)/10;
		i--;
		l--;
	}
	while(j>=0) {
		int b=td(intal2[j]);
		int ans=(b+carry)%10;
		res[l]=ts(ans);
		//printf("\n%d %c",ans,res[l]);
		carry=(b+carry)/10;
		j--;
		l--;
	}
	res[l]=ts(carry);
	return strip(res);
}

int intal_compare(const char* intal1, const char* intal2) {
	int n1=strlen(intal1);
	int n2=strlen(intal2);
	if(n1>n2) return 1;
	else if(n2>n1) return -1;
	for(int i=0;i<n1;i++) {
		int a=td(intal1[i]);
		int b=td(intal2[i]);
		if(a>b) return 1;
		else if(a<b) return -1;
	}
	return 0;
}

char* intal_diff(const char* intal1,const char* intal2) {
	int n1=strlen(intal1);
	int n2=strlen(intal2);
	int k=intal_compare(intal1,intal2);
	int l;
	char *res;
	if(k==0) {
		res=malloc(sizeof(char)*2);
		res[0]='0';
		res[1]='\0';
		return res;
	}
	
	if(k==1) {
		res=malloc(sizeof(char)*(n1+1));
		l=n1-1;
	}
	else {
		res=malloc(sizeof(char)*(n2+1));
		l=n2-1;
	}
	res[l+1]='\0';
	int borrow=0;
	int i=n1-1;
	int j=n2-1;
	while(i>=0 && j>=0) {
		int ans;
		int a=td(intal1[i]);
		int b=td(intal2[j]);
		if(k==1) {
			if(a-borrow-b<0) {
				ans=(a-borrow)+10-b;
				borrow=1;
			}
			else {
				ans=(a-borrow)-b;
				borrow=0;
			}
		}
		else {
			if(b-borrow-a<0) {
				ans=(b-borrow)+10-a;
				borrow=1;
			}
			else {
				ans=(b-borrow)-a;
				borrow=0;
			}
		}
		res[l]=ts(ans);
		//printf("\n%d-%d=%c %d",a,b,res[l],l);
		i--;
		j--;
		l--;
	}
	if(k==1) {
		while(i>=0) {
			int a=td(intal1[i]);
			if(a-borrow<0) res[l]=ts(a-borrow+10);
			else {
				res[l]=ts(a-borrow);
				borrow=0;
			}
			//printf("\n%c %d",res[l],intal1[i]-borrow);
			l--;
			i--;
		}
	}
	else {
		while(j>=0) {
			int b=td(intal2[j]);
			if(b-borrow<0) res[l]=ts(b-borrow+10);
			else {
				res[l]=ts(b-borrow);
				borrow=0;
			}
			//printf("\n%c %d",res[l],intal2[j]-borrow);
			l--;
			j--;
		}
	}
	return strip(res);
}

char* intal_multiply(const char* int1,const char* int2) {
	int i1, i2, temp;
	i1 = strlen(int1);
	i2 = strlen(int2);
	char *res = malloc(sizeof(char) * (i1 + i2 + 1));
	for (int k = 0; k <= i1 + i2; k++) {
		res[k] = '0';
	}
	char *intal1 = strrev(int1);
	char *intal2 = strrev(int2);
	if (i1 < i2) {
		int temp1;
		char *temp2;
		temp1 = i1;
		i1 = i2;
		i2 = temp1;
		temp2 = intal1;
		intal1 = intal2;
		intal2 = temp2;
	}
		int count = 0;
		int i = 0;
		int j = 0;
		while (i < i2) {
			int carry = 0;
			j = 0;
			while (j < i1) {
				temp = (td(res[j + count]) + td(intal2[i])*td(intal1[j]) + carry);
				carry = temp / 10;
				res[j + count] = ts(temp % 10);
				j++;
			}
			temp = (td(res[j + count]) + carry);
			carry = temp/10;
			res[j + count] = ts(temp%10);
			j++;
			if (carry != 0) {
				res[j + count] = ts(carry);
			}
			i++;
			count++;
		}
		res[j + count - 1] = '\0';
		char *tmp1;
		tmp1=res;
		res = strrev(res);
		free(tmp1);
		int p = 0;
		for (int i = 0; res[i] == '0'; ++i) {
			p++;
		}
		for (i = 0; i < (strlen(res) - p); ++i) {
			res[i] = res[i + p];
		}
		
		
		if (res[0] == '0') {
			res[0] = '0';
			res[1] = '\0';
		} else {
			res[i] = '\0';
		}
		free(intal1);
		free(intal2);
		return res;

}

// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
char* intal_pow(const char* intal1, unsigned int n) {
	if(n==0) {
		char *one=malloc(sizeof(char)*2);
		one[0]='1';
		one[1]='\0';
		return one;
	}
	char *y=intal_pow(intal1,n/2);
	if((n&1)==1) {
		char *res=intal_multiply(intal1,y);
		char *tmp=intal_multiply(res,y);
		free(y);
		free(res);
		return tmp;
	}
	char *res=intal_multiply(y,y);
	free(y);
	return res;
}

char* intal_mod(const char* intal1,const char* intal2)
{
	if(strcmp(intal2,"1")==0)
	{
		char * zero = malloc(sizeof(char)*2);
		zero[1]='\0';
		zero[0]='0';
		return zero;
	}
	int n1 = strlen(intal1);
	char *res,*temp;
	int len;
	res = malloc(sizeof(char)*2);
	res[1] = '\0';res[0] = intal1[0];
	for(int i=0;i<n1;i++)
	{
		while(intal_compare(res,intal2) >= 0)
		{
			temp=res;
			res = intal_diff(temp,intal2);
			free(temp);	
		}
		if(i==n1-1) break;
		len = strlen(res);
		if(len==1 && res[0]=='0'){res[0]=intal1[i+1];continue;}
		res = realloc(res,len+2);
		len+=1;
		res[len] = '\0';
		res[len-1] = intal1[i+1];
	}
	return res;
}


static char* gcd_euclid(char *x,char *y) {
	//printf("%s %s\n",x,y);
	if(!strcmp(x,"0")) {
		// printf("answer: %s\n", y);
		char *res=malloc(sizeof(char)*(strlen(y)+1));
		strcpy(res,y);
		return res;
	}
	// printf("hcd:%s %s\n", y, x);
	char *m=intal_mod(y,x);
	char *res=gcd_euclid(m,x);
	free(m);
	return res;
}
// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if one of intal1 and intal2 is "0".

char* intal_gcd(const char* intal1,const char* intal2) {
	 if(!strcmp(intal1,"0") && !strcmp(intal2,"0")) {
	 	char *zero=malloc(sizeof(char)*2);
	 	zero[0]='0';
	 	zero[1]='\0';
	 	return zero;
	 }
	else  {
		char *res;
		char *x=malloc(sizeof(char)*(strlen(intal1)+1));
		char *y=malloc(sizeof(char)*(strlen(intal2)+1));
		strcpy(x,intal1);
		strcpy(y,intal2);
		res=gcd_euclid(x,y);
		free(x);
		free(y);
		return res;
	}
}

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char* intal_fibonacci(unsigned int n) {
	char *a;
	char *b;
	char *c;
	a=malloc(sizeof(char)*1001);
	a[0]='0';;
	a[1]='\0';
	b=malloc(sizeof(char)*1001);
	b[0]='1';
	b[1]='\0';
	if(n==0)  {
		free(b);
		return a;
	}
	if(n==1) {
		free(a);
		return b;
	}
	if(n==2) {
		free(a);
		return b;
	}
	char *tmp1;
	for(int i=0;i<n-1;i++) {
		tmp1=a;
		c=intal_add(tmp1,b);
		a=b;
		b=c;
		free(tmp1);
	}
	free(a);
	return c;
}

// Returns the factorial of n.
char* intal_factorial(unsigned int n) {
	char *prd;
	prd=malloc(sizeof(char)*2);
	prd[0]='1';
	prd[1]='\0';
	if(n==0) {
		return prd;
	}
	char *x=malloc(sizeof(char)*2);
	x[0]='0';
	x[1]='\0';
	char *tmp;
	for(int i=0;i<n;i++) { 
		tmp=x;
		x=intal_add(tmp,"1");
		free(tmp);
		tmp=prd;
		prd=intal_multiply(tmp,x);
		free(tmp);
		}
	free(x);
	return prd;
}


char* intal_bincoeff(unsigned int n, unsigned int k) {
	char **c;
	if((n-k)<k) k=n-k;
	c=malloc(sizeof(char*)*(k+1));
	for(int i=0;i<k+1;i++) {
		c[i]=malloc(sizeof(char)*2);
		if(i==0) strcpy(c[i],"1");
		else strcpy(c[i],"0");
	}
	char *tmp;
	for(int i=1;i<=n;i++) {
		int z;
		if(i<k) z=i;
		else z=k;
		for(int j=z;j>0;j--) {
			tmp=c[j];
			c[j]=intal_add(tmp,c[j-1]);
			free(tmp);
		}
	}
	char *res=malloc(sizeof(char)*1001);
	strcpy(res,c[k]);
	for(int i=0;i<k+1;i++) free(c[i]);
	free(c);
	return res;
}

int intal_max(char **arr, int n) {
	char *max="0";
	int ind=0;
	for(int i=0;i<n;i++) {
		if(intal_compare(arr[i],max)==1) {
			max=arr[i];
			ind=i;
		}
	}
	return ind;
}

int intal_min(char **arr,int n) {
	char *min=arr[0];
	int ind=0;
	for(int i=0;i<n;i++) {
		if(intal_compare(arr[i],min)==-1) {
			min=arr[i];
			ind=i;
		}
	}
	return ind;
}

int intal_search(char **arr, int n, const char* key) {
	int ind=-1;
	for(int i=0;i<n;i++) {
		if(intal_compare(arr[i],key)==0) {
			ind=i;
			break;
		}
	}
	return ind;
}


static int bin_recurse(char **arr, int l, int r, const char *key) {
	if(r>=l) {
		int mid= l + (r-l)/2;
		//printf("%d\n",mid);
		if((mid==0 || intal_compare(key,arr[mid-1])==1)&& intal_compare(arr[mid],key)==0) 
			return mid;

		else if(intal_compare(arr[mid],key)==-1) 
			return bin_recurse(arr,mid+1,r,key);

		else
			return bin_recurse(arr,l,mid-1,key);
	}
	return -1;
}

int intal_binsearch(char **arr, int n, const char* key) {
	int res=bin_recurse(arr,0,n-1,key);
	return res;
}


static int partition(char **arr,int low,int high) {
	char *pivot=arr[high];
	int i=low-1;
	for(int j=low;j<=high-1;j++) {
		int z=intal_compare(arr[j],pivot);
		if(z==-1) {
			i++;
			swap_n(&arr[i],&arr[j]);
		}
	}
	swap_n(&arr[i+1],&arr[high]);
	return (i+1);
}

static void quickSort(char **arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void intal_sort(char **arr, int n) {
	quickSort(arr,0,n-1);
}


char* coin_row_problem(char **arr, int n) {
	char *zero = malloc(sizeof(char) * 2);
	zero[0] = '0';
	zero[1] = '\0';
	char *temp;
	char *temp_1 = malloc(sizeof(char)*2);
	strcpy(temp_1,"0");
	char *temp_2 = malloc(sizeof(char) * (strlen(arr[0]) + 1));
	strcpy(temp_2, arr[0]);
	char *z;
	for (int i = 2; i <= n; ++i) {
		z=intal_add(arr[i - 1], temp_1);
		if (intal_compare(z, temp_2) == 1) {
			free(z);
			temp = temp_1;
			temp_1 = temp_2;
			temp_2 = intal_add(arr[i - 1], temp);
			free(temp);
		} else {
			free(z);
			free(temp_1);
			temp_1 = temp_2;
			temp_2 = intal_add(temp_2, zero);
		}
	}
	free(zero);
	free(temp_1);
	return temp_2;
}
