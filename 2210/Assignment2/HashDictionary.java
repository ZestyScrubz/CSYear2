import java.util.LinkedList;

public class HashDictionary implements DictionaryADT {


    private final LinkedList<Layout>[] table;
    int size;


    public HashDictionary(int size) {
        this.size = size;
        table = new LinkedList[size];
        // each index in the array is initialized with an empty linked list
        for (int i = 0; i < size; i++) table[i] = new LinkedList<>();
    }

    /* Hash function that directly casts the char to an int. In Java, char values are represented by their corresponding Unicode integer values, so this directly provides a unique integer for each character. */
    private int hash(String key) {
        int hash = 0;
        int prime = 33; // or 31, both are good choices
        for (int i = 0; i < key.length(); i++) {
            hash = (prime * hash + key.charAt(i)) % size;
        }
        return Math.floorMod(hash, size); // ensures non-negative result
    }

    public int put(Layout data) throws DictionaryException {
        String key = data.getBoardLayout();
        int index = hash(key);

        LinkedList<Layout> list = table[index];

        // if this table is empty, create a new linked list
        if (list == null) {
            list = new LinkedList<Layout>();
            table[index] = list;
        } else {
            // check if there are duplicate keys, if there are then throw exception
            for (int i = 0; i < list.size(); i++) {
                Layout current = list.get(i);
                if (current.getBoardLayout().equals(key)) {
                    throw new DictionaryException("Duplicate key: " + key);
                }
            }
            
        }
        
        // check if this insertion causes a collision
        int collision;
        if (list.isEmpty()) {
            collision = 0;
        } else {
            collision = 1;
        }

        // add the new layout
        list.add(data);

        return collision;

    }

    public void remove(String boardLayout) throws DictionaryException {
        int index = hash(boardLayout);
        LinkedList<Layout> list = table[index];

        // First check if the list exists or is empty
        if (list == null || list.isEmpty()) {
            throw new DictionaryException("Board layout not found in dictionary.");
        }

        // Search for the layout in the list
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).getBoardLayout().equals(boardLayout)) {
                list.remove(i);  // just remove it
                return;          // and stop
            }
        }

        // If we reach here, it means we didn’t find the layout
        throw new DictionaryException("Board layout not found in dictionary.");
    }

    /*
    * A method which returns the score stored in the object in the dictionary with key boardLayout, or -1 if there no object in the dictionary with that key
     */
    public int get(String boardLayout) {

        int index = hash(boardLayout);
        LinkedList<Layout> list = table[index];
        
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).getBoardLayout().equals(boardLayout)) {
                return (list.get(i).getScore());
            }
        }
        
        return -1; 
    }
}