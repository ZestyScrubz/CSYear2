import java.util.ArrayList;

public class nathanBSTOrderedDictionary implements BSTOrderedDictionaryADT {
    BSTNode root;
    int numInternalNodes;

    public nathanBSTOrderedDictionary() {
        root = new BSTNode();
        numInternalNodes = 0;
    }

    // getter method
    public BSTNode getRoot() {
        return root;
    }

    // getter method
    public int getNumInternalNodes() {
        return numInternalNodes;
    }

    /**
     * using the compareTo method to search alphabetically for the key k in the BST
     * we can find the node with the matching key
     * @param r the root node of the BST
     * @param key the key to search for
     * @return the ArrayList of MultimediaItems associated with the key k, or null if not found
     */
    public ArrayList<MultimediaItem> get(BSTNode r, String k) {
        // since were searching using a BST, once it reaches a null node, the key is not present
        if (r == null || r.isLeaf()) {
            return null;
        }

        // the key is the name attribute of the Data object stored in each node
        // so we compare k to the name of the Data object at the current node r
        if (k.equals(r.getData().getName())) {
            return r.getData().getMedia();

            // compare alphabetically to decide whether to go left or right in the BST
        } else if (k.compareTo(r.getData().getName()) < 0) {
            return get(r.getLeftChild(), k);
        } else {
            return get(r.getRightChild(), k);
        }
    }

    /**
     * insert a new node with the given key with the content and type as a MultimediaItem
     * @param r the node given of the BST
     * @param key the key to insert
     * @param content the content of the MultimediaItem to insert
     * @param type the type of the MultimediaItem to insert 
     */
    public void put(BSTNode r, String k, String content, int type) {

        MultimediaItem item = new MultimediaItem(content, type);
        Data data = new Data(k);
        
        // check if the root/tree is empty/null
        if (r.isLeaf()) {
            // insert new node as the root
            // initialize left and right children as leaf nodes
            BSTNode leftLeaf = new BSTNode();
            BSTNode rightLeaf = new BSTNode();
            BSTNode newNode = new BSTNode(null, leftLeaf, rightLeaf, data); 

            // set the new node as the root
            root = newNode; 

            // set data and add multimedia item to the new node
            newNode.getData().add(item);

            // set parents for leaf nodes
            leftLeaf.setParent(newNode);
            rightLeaf.setParent(newNode);

            // increment internal node count
            numInternalNodes++;

        } else {
            // compare to decide where to insert the new node
            int compare = k.compareTo(r.getData().getName());
            if (compare == 0) { // key already exists, just add the multimedia item to the existing data
                r.getData().add(item);
                return;
            }

            // go left if key is smaller alphabetically, go right if larger
            if (compare < 0) {
                // only add a new node if we reach a leaf
                if (r.getLeftChild().isLeaf()) {
                    BSTNode leftLeaf = new BSTNode();
                    BSTNode rightLeaf = new BSTNode();
                    BSTNode newNode = new BSTNode(r, leftLeaf, rightLeaf, data);

                    r.setLeftChild(newNode);
                    newNode.getData().add(item);
                    leftLeaf.setParent(newNode);
                    rightLeaf.setParent(newNode);

                    numInternalNodes++;
                } else {
                    // recursively go left
                    put(r.getLeftChild(), k, content, type);
                }
            } else if (compare > 0) {
                if (r.getRightChild().isLeaf()) {
                    BSTNode leftLeaf = new BSTNode();
                    BSTNode rightLeaf = new BSTNode();
                    BSTNode newNode = new BSTNode(r, leftLeaf, rightLeaf, data);

                    r.setRightChild(newNode);
                    newNode.getData().add(item);
                    leftLeaf.setParent(newNode);
                    rightLeaf.setParent(newNode);

                    numInternalNodes++;
            } else {
                    // recursively go right
                    put(r.getRightChild(), k, content, type);
                }
            }
        }
    }

    /**
     * remove the node with the given key from the BST and rearrange the tree accordingly
     * @param r the node given of the BST
     * @param key the key to remove
     * @throws DictionaryException if the key is not found in the dictionary
     */
    public void remove(BSTNode r, String k) throws DictionaryException {
        BSTNode p = findNode(r, k);

        // check if p doesn't exist, then throw exception if not found
        // (original code mistakenly checked `r.isLeaf()` here which tests
        // the passed-in root rather than the found node `p`)
        if (p == null) {
            throw new DictionaryException("Key not found in dictionary.");
        }

        // if a child c of p is a leaf
        if (p.getLeftChild().isLeaf() || p.getRightChild().isLeaf()) {
            BSTNode c;
            // let c be the non-leaf child of p
            if (!p.getLeftChild().isLeaf()) {
                c = p.getLeftChild();
            } else {
                c = p.getRightChild();
            }

            // if parent is not null, then make c a child of p's parent instead of p
            if (p.getParent() != null) {
                // determine if p is a left or right child
                if (p == p.getParent().getLeftChild()) {
                    p.getParent().setLeftChild(c);
                } else {
                    p.getParent().setRightChild(c);
                }
                c.setParent(p.getParent());
            } else {
                // make c the root
                root = c;
                c.setParent(null);
            }
            numInternalNodes--;
        } else {
            // s is smallest right subtree of p
            // p.setRecord to s's record
            // remove s from the tree
            BSTNode s = smallestNode(p.getRightChild());
            p.setData(s.getData());
            remove(s, s.getData().getName());
        } 
    }

    /**
     * removes the multimedia items of the given type from the data associated with the given key
     * @param r the node given of the BST
     * @param key the key to remove multimedia items from a certain node
     * @param type the type of items to remove
     */
    public void remove(BSTNode r, String k, int type) throws DictionaryException {
        ArrayList<MultimediaItem> p = get(r, k);

        // throw exception if the key is not found
        if (p == null) {
            throw new DictionaryException("Key not found in dictionary.");
        }

        // remove all multimedia items of the given type using a for loop
            for (int i = p.size() - 1; i >= 0; i--) { // has to check the 0th index 
                if (p.get(i).getType() == type) {
                    p.remove(i); // arraylist method
                }
            }

            // now after removing the items, use the other remove method to remove the node
            if (p.isEmpty()) {
                remove(r, k);
            }
    }

    /**
     * find the node with the smallest key larger than the given key
     * @param r the node given of the BST
     * @param key the key to find the successor of
     * @return the data of the successor node, or null if it doesnt exist
     */
    public Data successor(BSTNode r, String k) {
        BSTNode p = findNode(r, k);
        if (p == null) return null;
        // if p is an internal node AND p has a right child thats also an internal node
        if (!p.isLeaf() && !p.getRightChild().isLeaf()) {
            return smallest(p.getRightChild());
        } else {
            p = p.getParent();
            while (p != null && k.compareTo(p.getData().getName()) > 0) {
                p = p.getParent();
            }
            if (p == null) return null;
            return p.getData();
        }
    }

    /**
     * find the node with the largest key smaller than the given key
     * @param r the node given of the BST
     * @param key the key to find the predecessor of
     * @return the data of the predecessor node, or null if it doesnt exist
     */
    public Data predecessor(BSTNode r, String k) {
        // find the node with the given key, unless it doesnt exist return null
        BSTNode p = findNode(r, k);
        if (p == null) return null; 

        // if p is not a leaf and has a left child thats not a leaf
        if (!p.isLeaf() && !p.getLeftChild().isLeaf()) {
            return largest(p.getLeftChild()); // keep checking the left child

        } else {
            p = p.getParent();
            while (p != null && k.compareTo(p.getData().getName()) < 0) {
                p = p.getParent();
            }
            if (p == null) return null;
            return p.getData();
        }
    }

    /**
     * finds the smallest key in the BST
     * @param r the node given of the BST
     * @return the data of the node with the smallest key, or null if the tree is empty
     */
    public Data smallest(BSTNode r) {
        // if the tree is empty ir a leaf node
        if (r == null || r.isLeaf()) {
            return null;
        }

        // the smallest key is found at the leftmost node
        BSTNode current = r;
        while (!current.getLeftChild().isLeaf()) {
            current = current.getLeftChild();
        }

        return current.getData();
    }

    /**
     * finds the largest key in the BST
     * @param r the node given of the BST
     * @return the data of the node with the largest key, or null if the tree is empty
     */
    public Data largest(BSTNode r) {
        // if the tree is empty or a leaf node
        if (r == null || r.isLeaf()) {
            return null;
        }

        // the largest key is found at the rightmost node
        BSTNode current = r;
        while (!current.getRightChild().isLeaf()) {
            current = current.getRightChild();
        }

        return current.getData();
    }
    
    /* --- Helper Methods --- */

    /**
     * find the node with the given key in the BST
     * @param r the node given of the BST
     * @param key the key to search for the node
     * @return the node with the given key, or null if not found
     */
    private BSTNode findNode(BSTNode r, String key) {
        // check if the tree is empty or a leaf node
        if (r == null || r.isLeaf()) {
            return null;
        }

        // same logic as the get method but returns the node instead of the media list
        if (key.equals(r.getData().getName())) {
            return r;
        } else if (key.compareTo(r.getData().getName()) < 0) {
            return findNode(r.getLeftChild(), key);
        } else {
            return findNode(r.getRightChild(), key);
        }
    }

    /**
     * find the node with the smallest key in the subtree rooted at r
     * @param r the node given of the BST
     * @return the node with the smallest key, or null if the tree is empty
     */
    private BSTNode smallestNode(BSTNode r) {
        // if the tree is empty or a leaf node
        if (r == null || r.isLeaf()) {
            return null;
        }

        // the smallest key is found at the leftmost node
        BSTNode current = r;
        while (!current.getLeftChild().isLeaf()) {
            current = current.getLeftChild();
        }

        return current;
    }

}
