
#include <iostream>
class nodeStack;

using namespace std;

class Stack{
private:
    nodeStack *topNode;
    int nNodes;
public:
    friend ostream& operator<<(ostream&, Stack&);
    Stack();
    ~Stack();

    //-------- Basic Methods --------------
    void push(float);         
    void drop();       
    float top();                
    float pop();
    //-------- Managment Methods ---------------
    void swap();                
    void dup();                 
    void depth();                
    void pick();             
    void dupn();       
    void dropn();  
    void rolld();               
    void rollu();
    void show();            
    void clear();   
    //--------- Operation Methods -------------
    void add();                 
    void sub();       
    void div();        
    void mult();
    void pot();

    //--------- Validation Methods --------------
    bool existTop();
    bool isEmpty();
    bool hasAny(int);

    

    
};
