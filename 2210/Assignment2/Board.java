

public class Board implements BoardADT{

    // store the game board
    char[][] theBoard;

    int boardSize, emptyPositions, maxLevels;

    public Board (int board_size, int empty_positions, int max_levels) {

        boardSize = board_size;
        emptyPositions = empty_positions;
        maxLevels = max_levels;

        // initialize the board, and make all the position empty
        theBoard = new char[board_size][board_size];
        for (int row = 0; row < board_size; row++) {
            for (int col = 0; col < board_size; col++) {
                theBoard[row][col] = 'E';
    }
}

    }

    public HashDictionary makeDictionary() {
        HashDictionary dictionary;
        boolean isPrime = true;

        // The loop runs only up to √n since any factor larger than √n would have a corresponding smaller factor already checked.
        for (int i = 2; i <= Math.sqrt(boardSize); i++) {
            if (boardSize % i == 0) {
                isPrime = false;
                break;
            }
        }

        if (boardSize < 10000 && isPrime){
            dictionary = new HashDictionary(boardSize);
        } else {
            dictionary = new HashDictionary(9973);
        }

        return dictionary;
    }

    public int repeatedLayout(HashDictionary dict) {
        String s = boardToString();
        return dict.get(s);
    }

    /*
     * This method first represents the content of theBoard as a String s as described in Section 2.1; then it creates a Layout object storing s and score and inserts this object in dict.
     */
    public void storeLayout(HashDictionary dict, int score) {
        String s = boardToString();
        Layout object = new Layout(s, score);
        try {
            dict.put(object);
        } catch (Exception e) {
            
        }
        
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

        // if there is no symbol, then there will be no winning case
        if (symbol != 'B' && symbol != 'R') return false;

        // check win in row
        // iterate through the rows to find if there are adjacent symbol
        for (int row = 0; row < boardSize; row++) {
            // every new row, make the "win" true and only change to false if theres no win in that row
            boolean win = true;

            // iterate through the columns
            for (int col = 0; col < boardSize; col++) {
                // if the symbol is not the same as the symbol, then no win
                if (theBoard[row][col] != symbol) {
                    win = false;
                    break;
                }
            }

            if (win) return true;
        }


        // check win in col
        // iterate through the columns to find if there are adjacent symbol
        for (int col = 0; col < boardSize; col++) {
            // every new row, make the "win" true and only change to false if theres no win in that row
            boolean win = true;

            // iterate through the columns
            for (int row = 0; row < boardSize; row++) {
                // if the symbol is not the same as the symbol, then no win
                if (theBoard[row][col] != symbol) {
                    win = false;
                    break;
                }
            }

            if (win) return true;
        }

        // check win diagonally
        boolean diagonalWin = true;
        for (int i = 0; i < boardSize; i++) {
            if (theBoard[i][i] != symbol) { 
                diagonalWin = false;
                break; 
            }
        }

        if (diagonalWin) return true;

        // check win other diagonally
        boolean antiDiagonalWin = true;
        for (int i = 0; i < boardSize; i++) {
            if (theBoard[i][boardSize - 1 - i] != symbol) { 
                antiDiagonalWin = false; 
                break; 
            }
        }
        if (antiDiagonalWin) return true;

        return false;
    }

    public boolean isDraw(char symbol, int emptyPositions) {

        if (winner(symbol)) return false; // someone already won, we dont need to check if there is a draw

        // check if there are any empty position on the board
        int emptyCount = 0;
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                if (theBoard[row][col] == 'E') {
                    emptyCount++;
                }
            }
        }

        // if there are more empty tiles than required, not a draw
        if (emptyCount > emptyPositions) return false;

        // if emptyPosition == 0 and there are not empty position left, then draw
        if (emptyPositions == 0 && emptyCount == 0) {
            return true;
        } else {
            // if there are equal empty positions and empty count then there is a draw
            // and none of the empty adjacent tiles of the empty position is the symbol type
            if (emptyCount == emptyPositions) {
                // iterate through the whole board and find empty position and check adjacent
                for (int row = 0; row < boardSize; row++) {
                    for (int col = 0; col < boardSize; col++) {
                        if (theBoard[row][col] == 'E') {
                            // if there is adjacent symbol then its not a draw
                            if (hasAdjacentType(row, col, symbol)) {
                                return false;
                            }
                        }
                    }
                }
            }

            return true;
        }

    }

    public int evaluate(char symbol, int emptyPositions) {
        if (winner('R')) return 3;
        if (winner('B')) return 0;
        if (isDraw(symbol, emptyPositions)) return 2;
        return 1;
    }

    /* Private Helper Method */

    /*** 
    Given the tile, check all the adjecent tiles if its the same symbol
    @return true is there is an adjacent tile of the symbol, false otherwise
    ***/ 

    private boolean hasAdjacentType(int row, int col, char symbol) {

        // Loops over all tiles surrounding (row, col) including diagonals.
        for (int r = row - 1; r <= row + 1; r++) { // iterate one left from the tiles to one to the right of the tile
            for (int c = col - 1; c <= col + 1; c++) { // iterate from tiles above to tiles below of the main tile
                // skip the middle tile / main tile
                if (r == row && c == col) continue;

                if (r >= 0 && r < boardSize && c >= 0 && c < boardSize) {
                    if (theBoard[r][c] == symbol) {
                        return true;
                    }
                }
            }
        }

        return false;

    }

    private String boardToString() {
        String result = "";

        // interate through the rows
        for (int col = 0; col < boardSize; col++) {
            for (int row = 0; row < boardSize; row++) {
                result += theBoard[row][col];
            }
        }

        return result;
    }

}
