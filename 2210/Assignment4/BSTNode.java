public class BSTNode {

    BSTNode parent;
    BSTNode leftChild;
    BSTNode rightChild;
    Data data;

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

    boolean isLeaf() {
        return (leftChild == null && rightChild == null || data == null);
    }

}
