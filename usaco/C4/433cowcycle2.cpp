#include <stdio.h>
#include <stdlib.h>

const double epsilon = 1e-13;

int F,R,F1,F2,R1,R2;
int GearF[20];
int GearR[20];
double bestvar;
int BestGearF[20];
int BestGearR[20];

void Try() {
    static int f,r,N,a,b;
    static double S[100];
    static double m,var;
    if(GearF[F-1]*GearR[R-1]<3*GearF[0]*GearR[0]) return;
				/* note use of integers */
    N=0;
    for(f=F-1; f>=0; f--)
        for(r=0; r<R; r++)
            S[N++]=double(GearF[f])/GearR[r];
    /* sort */
    for(a=1; a<N; a++) {
        b=a;
        while(b>0 && S[b-1]<S[b]) {
            m=S[b-1]; S[b-1]=S[b]; S[b]=m;
            b--;
        }
    }
    /* build difference table */
    N--;
    for(a=0; a<N; a++) S[a]-=S[a+1];

    /* calculate mean */
    m=0.0;
    for(a=0; a<N; a++) m+=S[a];
    m/=N;

    /* calculate variance */
    var=0.0;
    for(a=0; a<N; a++) var+=S[a]*S[a];
    var=var/N-m*m;
    if(var<bestvar) {
        bestvar=var-epsilon;
        for(a=0; a<F; a++) BestGearF[a]=GearF[a];
        for(a=0; a<R; a++) BestGearR[a]=GearR[a];
    }
}

void rekR(int nr,int least) {
    int i;
    if(nr==R) Try();
    else {
        for(i=least; i<=R2; i++) {
            GearR[nr]=i;
            rekR(nr+1,i+1);
        }
    }
}

void rekF(int nr,int least) {
    int i;
    if(nr==F) rekR(0,R1);
    else {
        for(i=least; i<=F2; i++) {
            GearF[nr]=i;
            rekF(nr+1,i+1);
        }
    }
}

void Read() {
    FILE *f=fopen("cowcycle.in","r");
    fscanf(f,"%d%d%d%d%d%d",&F,&R,&F1,&F2,&R1,&R2);
    fclose(f);
}

void Write() {
    int i;
    FILE *f=fopen("cowcycle.out","w");
    for(i=0; i<F; i++) {
        fprintf(f,"%d",BestGearF[i]);
        if(i<F-1) fputc(' ',f);  else fputc('\n',f);
    }
    for(i=0; i<R; i++) {
        fprintf(f,"%d",BestGearR[i]);
        if(i<R-1) fputc(' ',f);  else fputc('\n',f);
    }
    fclose(f);
}

int main() {
    Read();  // F,R,F1,F2,R1,R2
    bestvar=1e100;
    rekF(0,F1);
    Write();
    return 0;
}
