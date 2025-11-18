public class MultimediaItem {
    // Instance variables
    String content;
    int type;

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
