#include <stdio.h>

#define N 20
#define K 7
#define OK 0

typedef int Status;

Status main (void) {
	int cnt, mod, tmp;
	int array[N];
	
	for (cnt = 0; cnt < N; cnt ++)
		scanf("%d",&array[cnt]);
	if (N % K) {
		mod = K;
		tmp = array[K];
		do {
			if((mod-K+N) % N == K)
				array[mod] = tmp;
			else 
				array[mod] = array[(mod-K+N) % N];
			mod = (mod-K+N) % N;
		} while (mod != K);		
	} else {
		for (cnt=0; cnt < K; cnt ++) {
			mod = K+cnt;
			tmp = array[K+cnt];
			do{
				if((mod-K+N) % N == K+cnt)
					array[mod] = tmp;
				else
					array [mod] = array[(mod-K+N) % N];
				mod = (mod-K+N) % N;
			} while (mod != K+cnt);			
		}	
	}
	for (cnt=0; cnt < N; cnt ++)
		printf("%d ", array[cnt]);
	
	return OK;	
}
