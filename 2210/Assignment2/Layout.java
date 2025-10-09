public class Layout {
    /*
     * A constructor which initializes a new
    Layout object with the specified attributes boardLayout and score. The string boardLayout
    will be used as the key attribute for every Layout object.
     */

    String boardLayout;
    int score;

    public Layout(String boardLayout, int score) {
        this.boardLayout = boardLayout;
        this.score = score;
    }

    // Returns the boardLayout key attribute stored in a Layout object.
    public String getBoardLayout() {
        return this.boardLayout;
    }

    // Returns the score stored in a Layout object
    public int getScore() {
        return this.score;
    }
}
