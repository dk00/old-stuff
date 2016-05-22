template<class t> class stack   // t 是 stack 裡面資料的型態
{
public:
    struct node     // node
    {
        t data;
        node *next;
    }*top;
    stack()         // Constructor(建構子)
    {
        top=NULL;   // 把 stack 設為空的
    }               // 請參考 c++ / 物導程設的書籍
    ~stack()        // Destructor(解構子)
    {
        clear();    // 這個是把 stack 裡的東西清空
    }
    void clear()
    {
        node *ptr=top;  // 從 top 開始拿
        while(top!=NULL)
        {
            ptr=top;    // ptr 跟著 top 往下走
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
