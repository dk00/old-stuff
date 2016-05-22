n;main(i){return n?i<2?i:main(i-1)+main(i-2):
scanf("%d",&n)&&printf("%d\n",n>0?main(n):0);}
