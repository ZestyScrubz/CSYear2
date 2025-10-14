/* 
An object of this class stores in two instance variables a board layout and its associated integer score,
as explained above. Each board layout will be represented as a String as follows.
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-10-14
*/

public class Layout {

    String boardLayout; // "RRBEEREBB"
    int score; // 0, 1, 2, 3

    /*
    A constructor which initializes a new
    Layout object with the specified attributes boardLayout and score. The string boardLayout
    will be used as the key attribute for every Layout object.
     */

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
