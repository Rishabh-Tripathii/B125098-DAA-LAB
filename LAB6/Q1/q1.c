#include <stdio.h>
#include <stdlib.h>
int main(){
    int n;
    printf("Enter n:");
    scanf("%d",&n);
    int *fib= (int *)malloc(n * sizeof(int));
    if(n<0){
        printf("Invalid value of n");
    }
    fib[0]=0;
    if(n>=1) fib[1]=1;
    for(int i=2;i<=n;i++){
        fib[i]=fib[i-1]+fib[i-2];
    }
    printf("The value of %dth fibonacci number is %d",n,fib[n]);
    free(fib);
    return 0;
}