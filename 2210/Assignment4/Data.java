/* 
This class represents the data items that will be stored in the internal nodes of the binary search
tree implementing the ordered dictionary.
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-11-20
*/

import java.util.ArrayList;

public class Data {
    private String name;
    private ArrayList<MultimediaItem> media;

    /**
     * creates a new Data object with the given key attribute and an empty media
     * list.
     * 
     * @param newName the key attribute
     */
    public Data(String newName) {
        this.name = newName;
        media = new ArrayList<MultimediaItem>();
    }

    // adds newItem to the media list of this object
    public void add(MultimediaItem newItem) {
        media.add(newItem);
    }

    /**
     * @return the name of attribute of this object
     */
    public String getName() {
        return name;
    }

    /**
     * @return the media list stored in this object.
     */
    public ArrayList<MultimediaItem> getMedia() {
        return media;
    }

}
