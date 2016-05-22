package hw06.b96902120;

public class Student implements Comparable<Student>{
    String Name;
    int Score[];
    public Student(String _name,int n){
        Name=_name;
        Score=new int[n];
    }
    public int compareTo(Student x)
    {
        if(Score.length!=x.Score.length)
            return Score.length<x.Score.length?1:-1;
        int i,sum;
        for(i=sum=0;i<Score.length;i++)
            sum+=Score[i]-x.Score[i];
        if(sum!=0)
            return sum<0?1:-1;
        for(i=0;i<Score.length;i++)
            if(Score[i]!=x.Score[i])
                return Score[i]<x.Score[i]?1:-1;
        return 0;
    }
    public String toString(){
        String res=""+Name;
        for(int i=0;i<Score.length;i++)
            res=res+" "+Score[i];
        return res;
    }
}
