#include <iostream>
#include <math.h>
#include "Stack.h"
#include "nodeStack.h"

using namespace std;

Stack::Stack()
{
    topNode = NULL;
    nNodes = 0;
}

Stack::~Stack()
{
    this->clear();
}
//----- Basic Functions ------
void Stack::push(float data)
{
    nodeStack *newNode = new (nodeStack);
    newNode->data = data;
    newNode->next = topNode;
    topNode = newNode;
    nNodes++;
}

void Stack::drop()
{
    if (!existTop()) return;
    nodeStack *tmp = topNode;
    topNode = topNode->next;
    delete tmp;
    nNodes--;
    
}

float Stack::top()
{
    if (!existTop()) return 0;
        return topNode->data;
}

float Stack::pop()
{
    float value = top();
    drop();
    return value;
}

//------ Managment Functions -----

void Stack::swap()
{
    if (!existTop() || hasAny(2)) return;
    nodeStack *tmp = topNode;
    topNode = topNode->next;
    tmp->next = topNode->next;
    topNode->next = tmp;
}

void Stack::dup()
{
    if (!existTop()) return;
    push(topNode->data);
}

void Stack::depth()
{
    push(nNodes);
}

void Stack::pick()
{
    if (!existTop()) return;
    int topN = (int)pop();
    if ( nNodes < topN) return;
    int posCount = 1;
    for (nodeStack *tmp = topNode; tmp != NULL; tmp = tmp->next)
    {
        if (posCount == topN)
        {
            push(tmp->data);
            return;
        }
        posCount++;
    }
}

void Stack::dupn()
{
    if (!existTop()) return;
    int topN = (int)pop();
    if (topN > nNodes) topN = nNodes;
    for (int x = 0; x < topN; x++)
    {
        push(topN);
        pick();
    }
}

void Stack::dropn()
{
    if (!existTop()) return;
    int topN = (int)pop();
    if (topN > nNodes) topN = nNodes;
    for (int x = 0; x < topN; x++)
     drop();
}

void Stack::rolld()
{
    if (!existTop()) return;
    int topN = (int)pop();
    if (topN > nNodes || topN == 1) return;
    int posCount = 1;
    for (nodeStack *tmp = topNode; tmp != NULL; tmp = tmp->next)
    {
        if (posCount == (topN - 1))
        {
            nodeStack *tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            tmp2->next = topNode;
            topNode = tmp2;
            return;
        }
        posCount++;
    }
}

void Stack::rollu()
{
    if (!existTop()) return;
    int topN = (int)pop();
    if (topN > nNodes || topN == 1) return;
    int posCount = 1;
    for (nodeStack *tmp = topNode; tmp != NULL; tmp = tmp->next)
    {
        if (posCount == (topN - 1))
        {
            nodeStack *tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            tmp2->next = topNode;
            topNode = tmp2;
            return;
        }
        posCount++;
    }
}

void Stack::clear()
{
    if (!existTop()) return;
    depth();
    dropn();
    
}

void Stack::show()
{
    cout << *this;
}


//------- Operation Functions -------

void Stack::add()
{
    if (!hasAny(2)) return;
    push(pop() + pop());
}


void Stack::sub()
{
    if (!hasAny(2)) return;
        this->swap();
        push(pop() - pop());
}

void Stack::mult()
{
    if (!hasAny(2)) return;
        push(pop() * pop());
}

void Stack::div()
{
    if (!hasAny(2)) return;
        this->swap();
        push(pop() / pop());
}

void Stack::pot()
{
    if (!hasAny(2)) return;
        push(pow(pop(), pop()));
}

//------ External Functions ------

ostream &operator<<(ostream &out, Stack &stack)
{
    if (stack.isEmpty())
        out << ">Ups, The stack is empty!";
    int counterPos = 1;
    for (nodeStack *nodeTmp = stack.topNode; nodeTmp != NULL; nodeTmp = nodeTmp->next)
    {
        out << nodeTmp->data;
        if (counterPos == 1)
            out << " <--- Top";
        if (nodeTmp->next == NULL)
            out << " <--- Bottom";
        out << endl;
        counterPos++;
    }
    out << endl;
    return out;
}

bool Stack::existTop() {
    return topNode != NULL;
}

bool Stack::isEmpty() {
    return nNodes == 0;
}

bool Stack::hasAny(int nNodesMin) {
    return nNodes >= nNodesMin;
}
