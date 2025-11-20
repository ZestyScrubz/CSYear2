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

        // if there exists a node with key, add new multimediaitem with content and type
        // search through the tree to find where the root is
        if (r.isLeaf()) {
            // tree is empty, insert new node here
            BSTNode newNode = new BSTNode(null, new BSTNode(), new BSTNode(), newData);
            newNode.getData().add(newItem);
            root = newNode;
            numInternalNodes++;
        } else {

            int result = key.compareTo(r.getData().getName());
            if (result == 0) {
                // key already exists, add new multimedia item to existing data
                r.getData().add(newItem);
            }   
            else if (result < 0) {
                // if the key is smaller than the root, go left
                if (r.getLeftChild().isLeaf()) {
                    // if the left child is a leaf, insert new node here
                    BSTNode newNode = new BSTNode(r, new BSTNode(), new BSTNode(), newData);
                    newNode.getData().add(newItem);
                    r.setLeftChild(newNode);
                    numInternalNodes++;
                } else {
                    put(r.getLeftChild(), key, content, type);
                }
            } else {
                // if the key is larger than the root, go right
                if (r.getRightChild().isLeaf()) {
                    // if the right child is a leaf, insert new node here
                    BSTNode newNode = new BSTNode(r, new BSTNode(), new BSTNode(), newData);
                    newNode.getData().add(newItem);
                    r.setRightChild(newNode);
                    numInternalNodes++;
                } else {
                    put(r.getRightChild(), key, content, type);
                }
            }
        }

    }

    /**
     * removes from the binary search tree with root r the BSTNode storing the given
     * key attribute key
     * 
     * @param r root node
     */
    public void remove(BSTNode r, String k) throws DictionaryException {
        BSTNode p = getNode(r, k);

        if (p == null || p.isLeaf()) {
            throw new DictionaryException("Key not found");
        } else {
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

    }

    /**
     * removes from the tree with root r all MultimediaItem objects of the type specified by the third 
     * parameter stored in the ArrayList of the node with key attribute key. If after removing these
     * MultimediaItem objects the ArrayList becomes empty, the BSTNode with key attribute key 
     * must be removed from the tree
     * @param r root node
     * @param k key attribute
     * @param type type of MultimediaItem to be removed
     * @throws DictionaryException if there is no node in the tree storing the given key
     */
    public void remove(BSTNode r, String k, int type) throws DictionaryException {
        BSTNode p = getNode(r, k);

        if (p == null || p.isLeaf()) {
            throw new DictionaryException("Key not found");
        } else {
            ArrayList<MultimediaItem> mediaList = p.getData().getMedia();
            // remove all MultimediaItem objects of the given type
            for (int i = mediaList.size() - 1; i >= 0; i--) {
                if (mediaList.get(i).getType() == type) {
                    mediaList.remove(i);
                }
            }

            // if the media list is empty after removal, remove the node
            if (mediaList.isEmpty()) {
                remove(r, k);
            }
        }

    }

    /**
     * returns the Data objects stored in the successor of the node
     * storing key attribute key in the tree with root r; returns null if the successor does not exist.
     * @param r root of the tree
     * @param k given key
     * @return Data object storing the smallest key larger than k
     * @return null if no such key exists
     */
    public Data successor(BSTNode r, String k) {
        BSTNode p = getNode(r, k);
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
     * returns the Data objects stored in the predecessor of the node storing key 
     * attribute key in the tree with root r; returns null if the predecessor does not exist.
     * @param r root of the tree
     * @param k given key
     * @return Data object storing the largest key smaller than k
     * @return null if no such key exists
     */
    public Data predecessor(BSTNode r, String k) {
        BSTNode p = getNode(r, k);
        if (p == null) return null;
        // if p is an internal node AND p has a left child thats also an internal node
        if (!p.isLeaf() && !p.getLeftChild().isLeaf()) {
            return largest(p.getLeftChild());
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
     * returns the Data object storing the smallest key in the tree with root r; returns null if the tree is empty.
     *
     * @param r root of the tree
     * @return smallest returns the Data object sotring the smallest key
     * @return null if tree is empty
     */
    public Data smallest(BSTNode r) {
        // if the tree is empty
        if (r.isLeaf()) {
            return null;
        }

        // go as far left as possible
        BSTNode current = r;
        while (!current.getLeftChild().isLeaf()) {
            current = current.getLeftChild();
        }

        // the smallest key is stored in this internal node
        return current.getData();
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

        // if the tree is empty
        if (r.isLeaf()) {
            return null;
        }

        // go as far right as possible
        BSTNode current = r;
        while (!current.getRightChild().isLeaf()) {
            current = current.getRightChild();
        }

        // the largest key is stored in this internal node
        return current.getData();
    }

    /** 
     * finds in the tree with root r the BSTNode with the given key attribute key
     * @return the BSTNode storing the given key
     * @return null if there are no node in the tree storing the given key
    */
    private BSTNode getNode(BSTNode r, String key) {
        if (r.isLeaf()) return r;

        int cmp = key.compareTo(r.getData().getName());

        if (cmp == 0)
            return r;
        else if (cmp < 0)
            return getNode(r.getLeftChild(), key);
        else
            return getNode(r.getRightChild(), key);
    }

    private BSTNode smallestNode(BSTNode r) {
        // if the tree is empty
        if (r.isLeaf()) {
            return null;
        }

        // go as far left as possible
        BSTNode current = r;
        while (!current.getLeftChild().isLeaf()) {
            current = current.getLeftChild();
        }

        // the smallest key is stored in this internal node
        return current;
    }


}
