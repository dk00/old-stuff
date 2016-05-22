memory_explorer(int *p)
{
    int *q=p;
    while(*p--);
    while(*q++);
    return q-p-3;
}
