
import java.util.Dictionary;

public class Board implements BoardADT{

    // store the game board
    char[][] theBoard;

    int boardSize, emptyPositions, maxLevels;

    public Board (int board_size, int empty_positions, int max_levels) {

        boardSize = board_size;
        emptyPositions = empty_positions;
        maxLevels = max_levels;

    }

    public HashDictionary makeDictionary() {
        HashDictionary dictionary;
        boolean isPrime = true;

        // The loop runs only up to √n since any factor larger than √n would have a corresponding smaller factor already checked.
        for (int i = 2; i > Math.sqrt(boardSize); i++) {
            if (boardSize % i == 0) isPrime = false;
        }

        if (boardSize < 10000 && isPrime){
            dictionary = new HashDictionary(boardSize);
        }

        return dictionary;
    }

    public int repeatedLayout(HashDictionary dict) {

    }

    public void storeLayout(HashDictionary dict, int score) {

    }

    public void saveTile(int row, int col, char symbol){
        theBoard[row][col] = symbol;
    }

    public boolean positionIsEmpty (int row, int col) {
        return (theBoard[row][col] == 'E');
    }

    public boolean isComputerTile (int row, int col) {
        return (theBoard[row][col] == 'R');
    }

    public boolean isHumanTile (int row, int col) {
        return (theBoard[row][col] == 'B');
    }

    public boolean winner (char symbol) {
        // check left
        if (theBoard[row][col - 1] != null) {
            return (theBoard[row][col - 1] == symbol);
        }

        // check right

        // check top

        // check down

        // check top-left

        // check top-right

        // check bot-left

        // check bot-right
    }

    public boolean isDraw(char symbol, int empty positions) {}

    public int evaluate(char symbol, int empty positions) {}

}
