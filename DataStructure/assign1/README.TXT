
<README.TXT>
20161248 Jeon Woongbae
Email : wbjeon2k@gmail.com || woongbae@unist.ac.kr

- CircularList.h

In the CircularList class, the CNode class, which is the node class, is defined as an inner class.
CirculasList has 3 private members : cursor, AVLhead, lsize
cursor is to check the back of the circular list.
AVLhead is the head node of the available space list.
lsize is an integer to mark the size of the circular list.

Member function details

getNode() : returns CNode object
if the available space list is empty, return new CNode
otherwise, take one off from the list and return it.

add() : add a node after the cursor

~CircularList() : destructor
push every nodes into the available space list,
and then delete the available space list using cleanup().

empty() : if the cursor is NULL, then return true. Otherwise, return false

back() : return element where cursor locates

front() : return element where cursor->next locates

advance() : move cursor forward 1 time

size() : return lsize

reverse() : advance cursor, link cursor->next to cursor(link backward) for all the nodes

cleanup(): delete available space list


- assignment1.cpp

getpriority(): return icp
( : return 0
*,/ : return 1
+,- : return 2
otherwise: throw runtime error

getinstackpriority(): return isp
*,/ : return 1
+,- : return 2
( : return 3
otherwise: throw runtime error

postfix(expression){
  for all tokens in the expression: starting from front{
    if token is a number : add it to result
    if token is a closed paranthesis : pop stack until it reaches to open paranthesis
    otherwise : push it to stack
  }
}

eval(expression){
  push tokens into the stack.
  when it reaches to an operator, pop two tokens, and evaluate with the proper operator
  if it fails to pop two tokens, then throw runtime error, because of mismatch in operator & operand.
  when the result overflows, then throw runtime error
  push the result back in the stack
}
