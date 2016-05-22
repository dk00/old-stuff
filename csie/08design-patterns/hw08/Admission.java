import java.io.*;
import java.util.*;
import java.text.*;
class AdmissionException extends Exception
{
	AdmissionException()
	{
		super();
	}
	AdmissionException(String s)
	{
		super(s);
	}
}
class Student implements Comparable
{
	String name;
	int id,n,score[];
	Student(String data,int _n)
	{
		id=Integer.parseInt("1"+data.substring(0,6))-1000000;
		name=data.substring(7);
		n=_n;
		score=new int[n];
		for(int i=0;i<n;i++)
			score[i]=0;
	}
	public int compareTo(Object O)
	{
		Student o=(Student)O;
		int i,sum=0;
		for(i=0;i<n;i++)
			sum+=o.score[i]-score[i];
		if(sum!=0)
			return sum;
		for(i=0;i<n;i++)
			if(score[i]!=o.score[i])
				return o.score[i]-score[i];
		return 0;
	}
}
public class Admission
{
	static void puts(String s){System.out.println(s);}
	static void exit(String mes)throws AdmissionException
	{
		throw new AdmissionException(mes);
	}
	static int getint(BufferedReader in)throws AdmissionException
	{
		int x=-1;
		String tmp=null;
		try{while((tmp=in.readLine())!=null)
		{
			if(tmp.length()<1 || '0'>tmp.charAt(0) || tmp.charAt(0)>'9')
				continue;
			try{
				x=Integer.parseInt(tmp);
			}catch(NumberFormatException e){
				continue;
			}
			break;
		}}catch(IOException e){exit(e.toString());}
		return x;
	}
	static BufferedReader openfile(String filename)
	{
		BufferedReader in;
		try{
			in=new BufferedReader(new FileReader(filename));//
		}catch(FileNotFoundException e){
			return null;
		}
		return in;
	}
	public static void main(String arg[])throws AdmissionException
	{
		BufferedReader in=openfile("condition");
		if(in==null)
		{
			if((in=openfile("cond"))==null)
				exit("條件檔案 condition 和 cond 都不存在");
			puts("java.io.FileNotFoundException: condition (系統找不到指定的檔案。)");//
		}
		int i,j,m=-1,k=-1,n=-1,tmp=1;
		k=getint(in);
		n=getint(in);
		tmp=getint(in);
		if(n<0 || k<0)
			exit("條件檔案條件不足");
		if(tmp>=0)
			puts(new Exception("條件檔案資料過多").toString());
		if(n>5)
		{
			puts("AdmissionException: 考試科目過多，改為五科");
			n=5;
		}

		if((in=openfile("name"))==null)
		{
			if((in=openfile("names"))==null)
				exit("考生檔案 name 和 names 都不存在");
			puts("java.io.FileNotFoundException: name (系統找不到指定的檔案。)");
		}
		if((m=getint(in))<0)
			exit("考生總數錯誤");
		boolean err=false;
		String data=null;
		Student s[]=new Student[m],h[]=new Student[1000000];
		for(i=0;i<m;i++)
		{
			try{data=in.readLine();}
			catch(IOException e){exit(e.toString());}
			if(data==null)exit("考生檔案資料過少");
			for(j=0;j<data.length() && j<6;j++)
				if('0'>data.charAt(j) || data.charAt(j)>'9')
					break;
			if(data.length()<8 || j<6 || data.charAt(6)!=' ' || data.charAt(7)==' ')
			{
				err=true;
				puts("考生資料錯誤："+data);
				continue;
			}
			s[i]=new Student(data,n);
			if(h[s[i].id]!=null)
				puts("AdmissionException: 准考證號碼重複 "+s[i].id);
			h[s[i].id]=s[i];
		}
		try{if(in.readLine()!=null)exit("考生檔案資料過多");}
		catch(IOException e){exit(e.toString());}
		if(err)exit("考生檔案資料錯誤");

		err=false;
		for(i=0;i<n;i++)
		{
			if((in=openfile("score"+(i+1)))==null)
				exit("分數檔 score"+(i+1)+" 不存在");
			try{while((data=in.readLine())!=null)
			{	
				if(data.length()<8 || data.charAt(6)!=' ' || data.charAt(7)==' ')
				{
					err=true;
					puts("分數資料錯誤："+data);
					continue;
				}
				try{
					tmp=Integer.parseInt(data.substring(7));
				}catch(NumberFormatException e){
					err=true;
					puts("分數資料錯誤："+data);
					continue;
				}
				if(h[j=Integer.parseInt("1"+data.substring(0,6))-1000000]==null)
					puts("准考證號碼 "+data.substring(0,6)+" 不存在");
				else
					h[j].score[i]=tmp;
			}}catch(IOException e){exit(e.toString());}
			if(err)exit("分數檔案資料錯誤");
		}
		Arrays.sort(s);
		if(k>m)
		{
			//puts("錄取名額超過考生總數");
			k=m;
		}
		while(k<m && s[k-1].compareTo(s[k])==0)k++;
		String names[]=new String[k];
		for(i=0;i<k;i++)
			names[i]=s[i].name;
		Arrays.sort(names,Collator.getInstance(new Locale("zh","TW", "")));
		PrintStream out=null;
		try{out=new PrintStream("result");}
		catch(FileNotFoundException e){exit(e.toString());}
		for(i=0;i<k;i++)
			out.println(names[i]);
	}
}
