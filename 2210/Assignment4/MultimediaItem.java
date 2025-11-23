/* 
This class represents each one of the multimedia objects stored in the arrayList of a node of the
binary search tree
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-11-20
*/
public class MultimediaItem {
    // Instance variables
    private String content;
    private int type;

    /*
     * 1: if content is text
     * 2: if content is the name of an audio file
     * 3: if content is the name of an image file
     * 4: if content is the name of an html document.
     */

    /**
     * creates a new MultimediaItem object
     * whose instance variables have the values specified by the parameters.
     */
    public MultimediaItem(String newContent, int newType) {
        content = newContent;
        type = newType;
    }

    /**
     * @return the content of this node
     */
    public String getContent() {
        return content;
    }

    /**
     * @return the type of this node
     */
    public int getType() {
        return type;
    }

}
