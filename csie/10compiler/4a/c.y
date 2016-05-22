%{
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<stdio.h>
#include<cstdarg>
using namespace std;
int lineno = 1,error = 0;
extern "C" {
  int yyparse(void);
  int yylex(void);  
  int yywrap(){
    return 1;
  }
  void yyerror(const char *msg) {
    error = lineno;
  }
}
class Frame {
public:
  Frame();
  void NewVal(const string& name);
  int LoadVal(const string& name);
  int LoadArray(const string& name);
  int StoreVal(const string& name);
  void clear();  
private:
  int count;
  map<string,int> var_table;
};
stack<Frame> frames;
Frame current;
void Code(const char fmt[], ...);
void _Code(const char fmt[], ...);
void Comment(const char fmt[], ...);
void VarDecl(vector<string>& list);
int BeginLabel();
int EndLabel();
void Begin(int);
void End(int);
int LoopBeginLabel();
int LoopEndLabel();
void LoopBegin();
void LoopEnd();
string tmp;
bool NoLoad;
stack<int> labels, loops;
int dim_count, _label_num = 0, __tmp;
%}
%union {
  char sval[2048];
  int ival;
}
%token    <sval> ID
%token    <ival> NUM
%token    INT
%token    IF
%token    ELSE
%token    WHILE
%token    CONTINUE
%token    BREAK
%token    SCAN
%token    PRINT
%token    SIGN
%token    OP
%token    CMP
%token    LE
%token    GE
%token    EQ
%type     <sval> var

%right    '='
%left     OR
%left     AND
%left     EQ NE
%left     '<' LE '>' GE
%left     '+' '-'
%left     '*' '/'
%right    '!'
%%
blockStmt : '{' {
            frames.push(current);
          }
          varDecl stmts '}' {
            if (!frames.empty()) {
              current = frames.top();
              frames.pop();
            }
            else current.clear();
          }
          ;
varDecl   :
          | varDecl INT {
            dim_count = 0;
          } ArrayDim list ';';
ArrayDim  :
          | ArrayDim '[' NUM ']' {
            Code("ldc %d", $3);
            ++dim_count;
          }
          ;
list      : ID {
            current.NewVal($1);
          }
          | list ',' ID {
            current.NewVal($3);
          }
          ;
var       : ID {
            current.LoadVal($1);
          }
          | ID {
            current.LoadArray($1);
          } Index {
            Code("iaload");
          }
          ;
Index     : '[' arithExpr ']'
          | Index {
            Code("aaload");
          } '[' arithExpr ']'
          ;
stmts     :
          | stmts stmt
          ;          
stmt      : blockStmt
          | ID '=' arithExpr ';' {
            current.StoreVal($1);
          }
          | ID {
            current.LoadArray($1);
          } Index '=' arithExpr ';' {
            Code("iastore");
          }          
          | IF '(' boolExpr ')' { 
            Begin(0);
            Begin(0);
            Code("ifeq L%d", EndLabel());
          } blockStmt {            
            int tmp = EndLabel();
            End(0);
            Code("goto L%d", EndLabel());
            _Code("L%d:\n", tmp);
          } Else {
            End(1);
          }         
          | WHILE {
            LoopBegin();
          } '(' boolExpr ')' {
            Code("ifeq L%d", LoopEndLabel());
          } blockStmt {
            Code("goto L%d", LoopBeginLabel());
            LoopEnd();
          }
          | CONTINUE ';' {
            Code("goto L%d", LoopBeginLabel());
          }
          | BREAK ';' {
            Code("goto L%d", LoopEndLabel());
          }
          | SCAN '(' varList ')' ';'
          | PRINT '(' expList ')' ';'
          ;
Else      :
          | ELSE blockStmt;
varList   : ScanArg
          | varList ',' ScanArg
          ;
ScanArg   : ID {
          	Code("new BufferedReader");
        	  Code("dup");
          	Code("new InputStreamReader");
          	Code("dup");
          	Code("getstatic InputStream in @ System");
          	Code("invokespecial void <init>(InputStream) @ InputStreamReader");
          	Code("invokespecial void <init>(Reader) @ BufferedReader");
          	Code("invokevirtual String readLine() @ BufferedReader");
          	Code("invokestatic int parseInt(String) @ Integer");
            current.StoreVal($1);
          }
          | ID {
            current.LoadArray($1);
          } Index {
          	Code("new BufferedReader");
        	  Code("dup");
          	Code("new InputStreamReader");
          	Code("dup");
          	Code("getstatic InputStream in @ System");
          	Code("invokespecial void <init>(InputStream) @ InputStreamReader");
          	Code("invokespecial void <init>(Reader) @ BufferedReader");
          	Code("invokevirtual String readLine() @ BufferedReader");
          	Code("invokestatic int parseInt(String) @ Integer");
            Code("iastore");            
          }
          ;
expList   : PrintArg 
          | expList ',' PrintArg
          ;
PrintArg  : {
            Code("getstatic PrintStream out @ System");
          } arithExpr {            
            Code("invokevirtual void println(int) @ PrintStream");
          }
          ;
arithExpr : var
          | NUM {
            Code("ldc %d", $1);
          }
          | '(' arithExpr ')'
          | '+' arithExpr
          | '-' arithExpr           {Code("ineg");}       
          | arithExpr '*' arithExpr {Code("imul");}
          | arithExpr '/' arithExpr {Code("idiv");}
          | arithExpr '+' arithExpr {Code("iadd");}
          | arithExpr '-' arithExpr {Code("isub");}
          ;
boolExpr  : arithExpr '<' {
              Code("ldc 1");
              Code("swap");
          } arithExpr {
            Begin(0);            
            Code("if_icmplt L%d", EndLabel());
            Code("dup");
            Code("isub");
            End(1);
          }
          | arithExpr LE {
              Code("ldc 1");
              Code("swap");
          } arithExpr {
            Begin(0);            
            Code("if_icmplt L%d", EndLabel());
            Code("dup");
            Code("isub");
            End(1);
          }
          | arithExpr {
              Code("ldc 1");
              Code("swap");
          } '>' arithExpr {
            Begin(0);            
            Code("if_icmpgt L%d", EndLabel());
            Code("dup");
            Code("isub");
            End(1);
          }
          | arithExpr {
              Code("ldc 1");
              Code("swap");
          } GE arithExpr {
            Begin(0);            
            Code("if_icmpge L%d", EndLabel());
            Code("dup");
            Code("isub");
            End(1);
          }
          | arithExpr {
              Code("ldc 1");
              Code("swap");
          } EQ arithExpr {
            Begin(0);            
            Code("if_icmpeq L%d", EndLabel());
            Code("dup");
            Code("isub");
            End(1);
          }
          | arithExpr {
              Code("ldc 1");
              Code("swap");
          } NE arithExpr {
            Begin(0);            
            Code("if_icmpne L%d", EndLabel());
            Code("dup");
            Code("isub");
            End(1);
          }
          | boolExpr {
            Begin(0);
            Code("ldc 0");
            Code("swap");
            Code("ifeq L%d", EndLabel());
          } AND boolExpr {
            Code("ifeq L%d", EndLabel());
            Code("pop");
            Code("ldc 1");
            End(1);
          }
          | boolExpr {
            Begin(0);
            Code("ldc 1");
            Code("swap");
            Code("ifne L%d", EndLabel());
          } OR boolExpr {
            Code("ifne L%d", EndLabel());
            Code("pop");
            Code("ldc 0");
            End(1);
          }
          | '!' boolExpr {
            Code("ldc 1");
            Code("ixor");
          }
          ;
%%
void _Code(const char fmt[], ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}
void Code(const char fmt[], ...) {
  putchar('\t');
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  putchar('\n');
}
void Comment(const char fmt[], ...) {
  printf(";");
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  puts("");
}
void Begin(int print) {
  labels.push(++_label_num);
  if (print) {
    _Code("L%d:\n", labels.top()*2);
  }
}
void End(int print) {
  if (print) {
    _Code("L%d:\n", labels.top()*2 + 1);
  }
  if (!labels.empty()) labels.pop();
}
int BeginLabel() {
  return labels.top()*2;
}
int EndLabel() {
  return labels.top()*2 + 1;
}
void LoopBegin() {
  Begin(1);
  loops.push(BeginLabel()/2);
}
void LoopEnd() {
  End(1);
  if (!loops.empty()) 
    loops.pop();
}
int LoopBeginLabel() {
  return loops.top()*2;
}
int LoopEndLabel() {
  return loops.top()*2 + 1;
}
void Head() {
  _Code(".import java.io.*\n");
  _Code(".class c0\n");
  _Code(".method void <init>()\n");
  Code("aload #0");
  Code("invokespecial void <init>() @ Object");
  Code("return");
  _Code(".method public static void main(String[])\n");
}
void Tail() {
  Code("return");
}
Frame::Frame() {
  count = 0;
}
void Frame::NewVal(const string& name) {
  var_table[name] = count++;
  int id = var_table[name];
  Comment("var %s(%d)", name.c_str(), var_table[name]);
  if (dim_count == 0)
    return;
  _Code("\tmultianewarray int");
  for (int i = 0;i < dim_count;++i) _Code("[]");
  _Code(" %d\n", dim_count);
  Code("astore #%d",id);
}
int Frame::LoadVal(const string& name) {
  if (var_table.count(name)) {
    Code("iload #%d", var_table[name]);
  } else {}
}
int Frame::LoadArray(const string& name) {
  if (var_table.count(name)) {
    Code("aload #%d", var_table[name]);
  } else {}
}
int Frame::StoreVal(const string& name) {
  if (var_table.count(name)) {
    Code("istore #%d", var_table[name]);
  } else {}
}
void Frame::clear() {var_table.clear();}
int main(int argc,char **argv) {
  Head();
  yyparse();
  if (error > 0)
    fprintf(stderr, "Fail (around line %d)\n", error);
  else {
    fputs("Pass\n", stderr);
    Tail();
  }
}
