import java.util.ArrayList;

public class Data {
    String name;
    ArrayList<MultimediaItem> media;

    /**
     * creates a new Data object with the given key attribute and an empty media
     * list.
     * 
     * @param newName the key attribute
     */
    public Data(String newName) {
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
