/* 
This class represents the nodes of the binary search tree implementing the ordered dictionary. 
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-11-20
*/
public class BSTNode {

    private BSTNode parent;
    private BSTNode leftChild;
    private BSTNode rightChild;
    private Data data;

    public BSTNode() {
        parent = null;
        leftChild = null;
        rightChild = null;
        data = null;
    }

    public BSTNode(BSTNode newParent, BSTNode newLeftChild, BSTNode newRightChild, Data newData) {
        parent = newParent;
        leftChild = newLeftChild;
        rightChild = newRightChild;
        data = newData;
    }

    /*** Getter methods ***/

    public BSTNode getParent() {
        return parent;
    }

    public BSTNode getLeftChild() {
        return leftChild;
    }

    public BSTNode getRightChild() {
        return rightChild;
    }

    public Data getData() {
        return data;
    }

    /*** Setter Methods ***/

    public void setParent(BSTNode newParent) {
        parent = newParent;
    }

    public void setLeftChild(BSTNode newLeftChild) {
        leftChild = newLeftChild;
    }

    public void setRightChild(BSTNode newRightChild) {
        rightChild = newRightChild;
    }

    public void setData(Data newData) {
        data = newData;
    }

    public boolean isLeaf() {
        return data == null;
    }

}
