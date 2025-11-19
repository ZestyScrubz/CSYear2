
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
     * finds in the tree with root r the BSTNode with the given key attribute key
     * 
     * @return the list of MultimediaItem object with the given key
     * @return null if there are nonode in the tree storing the given key
     */
    public ArrayList<MultimediaItem> get(BSTNode r, String key) {

        if (r == null || r.isLeaf()) {
            return null; // key not found
        }

        int result = key.compareTo(r.getData().getName());

        if (result == 0) {
            return r.getData().getMedia();
        } else if (result < 0) {
            return get(r.getLeftChild(), key);
        } else {
            return get(r.getRightChild(), key);
        }
    }

    /**
     * adds the given information to the tree with root r
     */
    public void put(BSTNode r, String key, String content, int type) {

        // create a new node object with key and content and type
        Data newData = new Data(key);
        MultimediaItem newItem = new MultimediaItem(content, type);
        ArrayList<MultimediaItem> p = get(r, key);

        // if there exists a node with key, add new multimediaitem with content and type
        // search through the tree to find where the root is
        if (p != null) {
            get(r, key).add(newItem); // getting the arraylist with the root r and the key
        } else {
            BSTNode newNode = new BSTNode(r);
            newData.add(newItem);
            numInternalNodes++;
        }
    }

    /**
     * removes from the binary search tree with root r the BSTNode storing the given
     * key attribute key
     * 
     * @param r root node
     */
    public void remove(BSTNode r, String k) throws DictionaryException {
        // 1. search the tree for the root with the key
        // 2. else if the root left node is null, make the new root the right tree
        // 3. else if the root right node is null, make the new root the left tree
        // 4. else if (they are both not null), we will replace the root with the
        // smallest of the right subtree (could have also done the largest of the right
        // subtree)
        // Note: we dont need to check if its a leaf, since if both side is null, then
        // we will make the parent point to null
        // 5. if it is not in the tree, throw exception

        if (r.isLeaf()) {
            throw new DictionaryException("Key not found");
        }

        int result = k.compareTo(r.getData().getName());

        if (result < 0) {
            // if the key k is smaller than the root, search left subtree
            remove(r.getLeftChild(), k);
        } else if (result > 0) {
            // if the key k is larger than the root, search right subtree
            remove(r.getRightChild(), k);
        } else {
            BSTNode left = r.getLeftChild();
            BSTNode right = r.getRightChild();
            // if we found the key
            if (left == null) {
                // if the left is null, set right subtree to be the new root
                r.setData(right.getData());
                r.setRightChild(right.getRightChild());
                r.setLeftChild(right.getLeftChild());
                numInternalNodes--;
            } else if (right == null) {
                // if the right is null, set left subtree to be the new root
                r.setData(left.getData());
                r.setRightChild(left.getRightChild());
                r.setLeftChild(left.getLeftChild());
                numInternalNodes--;
            } else {
                // if the left and right are not null (the root is not a leaf), find the
                // smallest in the right subtree
                BSTNode cur = right;

                // loop left until we hit the leaf
                while (!cur.isLeaf()) {
                    cur = cur.getLeftChild();
                }

                r.setData(cur.getData());
                remove(r.getRightChild(), r.getData().getName());

            }

        }

    }

    public void remove(BSTNode r, String k, int type) throws DictionaryException {

    }

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
