package hw06.b96902120;
import java.util.*;
import java.io.File;
import org.w3c.dom.*;
import java.text.Collator;
import javax.xml.parsers.DocumentBuilderFactory;
public class Examination{
    static String LIMIT="錄取名額",STUDENT="考生",SUBJECT="科目",EXAMID="准考證",SN="編號";
    int Limit,nSubject;
    HashMap<String,Student> Idmap;
    Student StuList[];
    public Examination(String filename){
        try{
            Document x=DocumentBuilderFactory.newInstance()
            .newDocumentBuilder().parse(new File(filename));
            Limit=Integer.parseInt(x.getChildNodes().item(0)
                .getAttributes().getNamedItem(LIMIT).getNodeValue());
            NodeList t=x.getElementsByTagName(SUBJECT);
            nSubject=t.getLength();
            NodeList u=x.getElementsByTagName(STUDENT);
            Idmap=new HashMap<String,Student>();
            StuList=new Student[u.getLength()];
            for(int i=0;i<u.getLength();i++)
                Idmap.put(u.item(i).getAttributes().getNamedItem(EXAMID).getNodeValue(),
                StuList[i]=new Student(u.item(i).getFirstChild().getNodeValue(),nSubject));
            for(int i=0;i<t.getLength();i++)
            {
                int k=Integer.parseInt(t.item(i).getAttributes().
                getNamedItem(SN).getNodeValue());
                NodeList v=t.item(i).getChildNodes();
                for(int j=0;j<v.getLength();j++)
                    if(v.item(j).hasAttributes())
                        Idmap.get(v.item(j).getAttributes().getNamedItem(EXAMID)
                        .getNodeValue()).Score[k]=Integer.parseInt
                        (v.item(j).getFirstChild().getNodeValue());
            }
        }catch(Exception e){
            System.out.println(e.toString());
        }
    }
    public String listTop(){
        Arrays.sort(StuList);
        int i,j;
        for(i=0;i<StuList.length
        && (i<Limit || (i>0 && StuList[i].compareTo(StuList[i-1])==0));i++);
        String NameList[]=new String[i];
        for(j=0;j<i;j++)
            NameList[j]=StuList[j].Name;
        Arrays.sort(NameList,Collator.getInstance(new Locale("zh","TW", "")));
        if(NameList.length<1)return "";
        String result=NameList[0];
        for(j=1;j<i;j++)
            result=result+" "+NameList[j];
        return result;
    }
}
