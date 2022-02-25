LinkedBinaryTree
/*
20161248 JEON WOONGBAE
wbjeon2k@gmail.com

attatchLeftSubtree:
	parent of the subtree._root = p.v;
	p.v's left child = subtree's root
	make subtree's root as NULL, size as 0 -> delete subtree

attatchRightSubtree:
	same as attatchLeftSubtree

nodeheight:
	get the height of a designated node recursively

others: trivial

*/


assignment2
/*

20161248 JEON WOONGBAE
wbjeon2k@gmail.com

parsePostfixExpression:
	if operand: push
	if operator: pop two operand, make them as children

inorder:
	get token
	if operand: push
	if operator : pop two tokens, combine them, and push expression

simplify_subtree:
	generate positionlist which takes the postfix order
	iterate through the positionlist, which is same as iterating from bottom to top
	if meets operator: check wheter left&right are both constants, compute, and replace node

others: trivial


*/
