
import java.util.ArrayList;

public class BSTOrderedDictionary implements BSTOrderedDictionaryADT {

    BSTNode root;
    int numInternalNodes;

    /*
     * contructer that:
     * creates an empty BSTOrderedDictionary in which the root is a
     * leaf BSTNode and numInternalNodes = 0.
     */
    public BSTOrderedDictionary() {
        root = new BSTNode(); // creates a new leaf node
        numInternalNodes = 0;
    }

    public BSTNode getRoot() {
        return root;
    }

    public int getNumInternalNodes() {
        return numInternalNodes;
    }

    /**
     * finds in the tree with root r the BSTNode with the given key attribute
     * key
     *
     * @return the list of MultimediaItem object with the given key
     * @return null if there are nonode in the tree storing the given key
     */
    public ArrayList<MultimediaItem> get(BSTNode r, String key) {

        // if there is a key in the tree with root r
        if (key.equals(r.getData().getName())) {
            return r.getData().getMedia();
        }

        return null;

    }

    /**
     * adds the given information to the tree with root r
     */
    public void put(BSTNode r, String key, String content, int type) {
        Data newData = new Data(key);
        MultimediaItem newItem = new MultimediaItem(content, type);

        // if tree is empty / subtree is empty
        if (r.getData() == null) {
            r.setData(newData);
        } // if there exists a node with key, add new multimediaitem with content and type
        else if (key.equals(r.getData().getName())) {
            r.getData().add(newItem);
        } // no node exist with this key, create a new node
        else {
            newData.add(newItem);
            numInternalNodes++;
        }
    }

    /**
     * removes from the binary search tree with root r the BSTNode storing the
     * given key attribute key
     */
    public void remove(BSTNode r, String k) throws DictionaryException {

    }

    public void remove(BSTNode r, String k, int type) throws DictionaryException;

    public Data successor(BSTNode r, String k);

    public Data predecessor(BSTNode r, String k);

    /**
     * returns the Data object storing the smallest key in the tree with root r;
     * returns null if the tree is empty.
     *
     * @param r root of the tree
     * @return smallest returns the Data object sotring the smallest key
     * @return null if tree is empty
     */
    public Data smallest(BSTNode r) {

        // check if tree is empty
        if (r == null) {
            return null;
        }

        // recursively call the left child since the left most is the smallest
        // base case: if it's a leaf return the data
        if (r.isLeaf()) {
            return r.getData();
        } else {
            smallest(r.getLeftChild());
        }

        // idk what this is
        return r.getData();
    }

    /**
     * returns the Data object storing the largest key in the tree with root r;
     * returns null if the tree is empty.
     *
     * @param r root of the tree
     * @return largest returns the Data object sotring the largest key
     * @return null if tree is empty
     */
    public Data largest(BSTNode r) {

        // check if tree is empty
        if (r == null) {
            return null;
        }

        // recursively call the left child since the left most is the smallest
        // base case: if it's a leaf return the data
        if (r.isLeaf()) {
            return r.getData();
        } else {
            largest(r.getRightChild());
        }

        // idk what this is
        return r.getData();
    }

}
