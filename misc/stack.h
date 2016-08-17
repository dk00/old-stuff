template<class t> class stack   // t �O stack �̭���ƪ����A
{
public:
    struct node     // node
    {
        t data;
        node *next;
    }*top;
    stack()         // Constructor(�غc�l)
    {
        top=NULL;   // �� stack �]���Ū�
    }               // �аѦ� c++ / ���ɵ{�]�����y
    ~stack()        // Destructor(�Ѻc�l)
    {
        clear();    // �o�ӬO�� stack �̪��F��M��
    }
    void clear()
    {
        node *ptr=top;  // �q top �}�l��
        while(top!=NULL)
        {
            ptr=top;    // ptr ��� top ���U��
            delete ptr;
            top=top->next;
        }
    }
    void push(t s)
    {
        node *ptr;
        ptr=new node;
        *ptr=(node){s,top};
        top=ptr;
    }
    t pop()
    {
        t tmp=top->data;
        node *ptr=top;
        top=top->next;
        return tmp;
    }
    void show()
    {
        int count=0;
        node *ptr;
        for(ptr=top;ptr!=NULL;ptr=ptr->next,count++)
            printf("%d\n",ptr->data);
        printf("There're %d elemnet(s) in the stack.\n",count);
    }
};
