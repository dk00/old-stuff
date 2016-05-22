#include <stdio.h>

int a[500][500];
int c[250010];
int u[250000];

int main() {
	   int n,m,k,i,j,N,p,d;
	      while(scanf("%d %d %d",&n,&m,&k)==3) {
			        N = n*n;
					      p = 0;
						        for( i=0; i<n; i++ ) {
									         for( j=0; j<=i; j++ ) {
												             a[j][i-j] = p++;
															          }
											       }
								      for( i=1; i<n; i++ ) {
										           d = n-i;
												            for( j=0; j<d; j++ ) {
																            a[i+j][n-j-1] = p++;
																			         }
															      }
									        for( i=0; i<N; i++ ) {
												         u[i] = 0;
														       }
											      c[0] = m-1;
												        u[c[0]] = 1;
														      for( i=1; i<=k; i++ ) {
																           c[i] = a[c[i-1]/n][c[i-1]%n];
																		            if(u[c[i]]) {
																						            k%=i;
																									            break;
																												         }else {
																															             u[c[i]] = 1;
																																		          }
																					      }
															        printf("%d\n",c[k]+1);
																	   }
		     return 0;
}


