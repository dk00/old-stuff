package hw08.b96902120;
import java.io.*;
import java.util.*;
import com.sun.tools.javac.tree.*;

public class NodeCountingVisitor extends TreeScanner{
    Map<String,Integer> h=new LinkedHashMap<String,Integer>();
    public NodeCountingVisitor(){
        String nodes[]=new String[]{
            "JCCompilationUnit",
            "JCImport",
            "JCClassDecl",
            "JCMethodDecl",
            "JCVariableDecl",
            "JCSkip",
            "JCBlock",
            "JCDoWhileLoop",
            "JCWhileLoop",
            "JCForLoop",
            "JCEnhancedForLoop",
            "JCLabeledStatement",
            "JCSwitch",
            "JCCase",
            "JCSynchronized",
            "JCTry",
            "JCCatch",
            "JCConditional",
            "JCIf",
            "JCExpressionStatement",
            "JCBreak",
            "JCContinue",
            "JCReturn",
            "JCThrow",
            "JCAssert",
            "JCMethodInvocation",
            "JCNewClass",
            "JCNewArray",
            "JCParens",
            "JCAssign",
            "JCAssignOp",
            "JCUnary",
            "JCBinary",
            "JCTypeCast",
            "JCInstanceOf",
            "JCArrayAccess",
            "JCFieldAccess",
            "JCIdent",
            "JCLiteral",
            "JCPrimitiveTypeTree",
            "JCArrayTypeTree",
            "JCTypeApply",
            "JCTypeParameter",
            "JCWildcard",
            "JCAnnotation",
            "JCModifiers",
            "JCErroneous",
            "LetExpr",
            "TypeBoundKind"
        };
        for(String p:nodes)
            h.put(p,0);
    }
    public void scan(JCTree T) {
        super.scan(T);
        if(T==null)return;        
        String[] tmp=T.getClass().getName().split("\\$");
        String name=tmp[tmp.length-1];
        Integer x=h.get(name);
        if(x!=null)
            h.put(name,x+1);
    }
    public void count(JCTree a){
        this.scan(a);
    }
    public void list(PrintStream a){
        Set<String> node=h.keySet();
        for(String p:node)
            System.out.printf("%23s\t%d\n",p,h.get(p));
    }
}
