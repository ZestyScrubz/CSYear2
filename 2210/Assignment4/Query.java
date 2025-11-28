/* 
This class implements a text-based application that allows the user to access the information in the
multimedia ordered dictionary. 
Student Name: Isaac Tran
Student email: itran9@uwo.ca
Student ID: 251446564
Due Date: 2025-11-20
*/

import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


public class Query {

    static BSTOrderedDictionary dictionary;

    public static void main(String[] args) {
        String result, nextCommand;

        StringReader keyboard = new StringReader();
            // `StringReader` is a simple helper that prints a prompt and reads a
            // line from stdin. We use it to interactively accept commands.
        if (args.length != 1) {
            System.out.println("Usage: java Query fileName");
            System.exit(0);
        }

        new Query(args[0]); // pass the filename
    // Build the dictionary by reading the provided input file. The
    // constructor performs the file parsing and populates `dictionary`.

        while (true) {
            String raw = keyboard.read("Enter next command: ");
            if (raw == null) break;
            nextCommand = raw.trim();
            if (nextCommand.equalsIgnoreCase("end")) {
                break;
            }

            result = processCommand(nextCommand);
            if (!result.isEmpty()) {
                System.out.println(result);
            }
        }
    }

    public Query(String inputFile) {
        dictionary = new BSTOrderedDictionary();
        // build dictionary from input file

        try (BufferedReader br = new BufferedReader(new FileReader(inputFile))) {
            String keyLine;
            while ((keyLine = br.readLine()) != null) {
                keyLine = keyLine.trim();
                String contentLine = br.readLine();
                if (contentLine == null) break; // odd number of lines: stop
                contentLine = contentLine.trim();
                // Read the content line paired with this key. If there is no
                // following line the pair is incomplete and we stop.

                String key = keyLine.toLowerCase();

                int type = 1;
                String lowContent = contentLine.toLowerCase();
                if (!lowContent.contains(" ") && lowContent.contains(".")) {
                    if (lowContent.endsWith(".wav") || lowContent.endsWith(".mid")) {
                        type = 2;
                    } else if (lowContent.endsWith(".jpg") || lowContent.endsWith(".gif")) {
                        type = 3;
                    } else if (lowContent.endsWith(".html")) {
                        type = 4;
                    } else {
                        type = 1;
                    }
                }

                dictionary.put(dictionary.getRoot(), key, contentLine, type);
            }
        } catch (FileNotFoundException e) {
            System.out.println("Cannot open file: " + inputFile);
            System.exit(1);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
            System.exit(1);
        }
        // finished building dictionary
    }

    

    public static String processCommand(String command) {
        String[] tokens = command.trim().split("\\s+");
        if (tokens.length == 0) return "Invalid command";

        String cmd = tokens[0].toLowerCase();

        try {
            switch (cmd) {

                case "get": {
                    if (tokens.length < 2) return "Invalid command";
                    String key = tokens[1].toLowerCase();
                    ArrayList<MultimediaItem> items = dictionary.get(dictionary.getRoot(), key);
                    ArrayList<String> lines = new ArrayList<>();

                    // for every item in the array list we get the type and play the corresponding content based on the number
                    if (items != null && !items.isEmpty()) {
                        for (MultimediaItem item : items) {
                            try {
                                switch (item.getType()) {
                                    case 1:
                                        lines.add(item.getContent());
                                        break;
                                    case 2:
                                        new SoundPlayer().play(item.getContent());
                                        break;
                                    case 3:
                                        new PictureViewer().show(item.getContent());
                                        break;
                                    case 4:
                                        new ShowHTML().show(item.getContent());
                                        break;
                                }
                            } catch (MultimediaException e) {
                                lines.add("Cannot display/play: " + item.getContent());
                            }
                        }
                        return String.join("\n", lines);
                    } else {
                        String s = "The word " + key + " is not in the ordered dictionary.\n";
                        Data pred = dictionary.predecessor(dictionary.getRoot(), key);
                        Data succ = dictionary.successor(dictionary.getRoot(), key);
                        // if the predeceding word is null we will print nothing else we will print the key
                        s += "Preceding word: " + (pred != null ? pred.getName() : "") + "\n";
                        s += "Following word: " + (succ != null ? succ.getName() : "");
                        return s;
                    }
                }

                case "remove": {
                    if (tokens.length != 2) return "Invalid command";
                    String key = tokens[1].toLowerCase();
                    dictionary.remove(dictionary.getRoot(), key);
                    return "";
                }

                case "delete": {
                    if (tokens.length != 3) return "Invalid command";
                    String key = tokens[1].toLowerCase();
                    int type;
                    try {
                        type = Integer.parseInt(tokens[2]);
                    } catch (NumberFormatException e) {
                        return "Invalid type value: " + tokens[2];
                    }
                    dictionary.remove(dictionary.getRoot(), key, type);
                    return "";
                }

                case "add": {
                    if (tokens.length < 4) return "Invalid command";
                    String key = tokens[1].toLowerCase();
                    int type;
                    try {
                        type = Integer.parseInt(tokens[tokens.length - 1]);
                    } catch (NumberFormatException e) {
                        return "Invalid type value: " + tokens[tokens.length - 1];
                    }
                    String content = tokens[2];
                    for (int i = 3; i < tokens.length - 1; i++) {
                        content = content + " " + tokens[i];
                    }
                    dictionary.put(dictionary.getRoot(), key, content, type);
                    return "";
                }

                case "next": {
                    if (tokens.length != 3) return "Invalid command";
                    String key = tokens[1].toLowerCase();
                    int d;
                    try { d = Integer.parseInt(tokens[2]); } 
                    catch (NumberFormatException e) { return "Invalid number: " + tokens[2]; }

                    ArrayList<String> out = new ArrayList<>();
                    ArrayList<MultimediaItem> nodeMedia = dictionary.get(dictionary.getRoot(), key);
                    if (nodeMedia != null) out.add(key);

                    Data succ = (nodeMedia != null) ? dictionary.successor(dictionary.getRoot(), key) 
                                                    : dictionary.successor(dictionary.getRoot(), key);
                    if (!out.isEmpty() && succ == null) return String.join(" ", out);
                    if (out.isEmpty() && succ == null) return "There are no keys larger than or equal to " + key;

                    String last = out.isEmpty() ? succ.getName() : key;
                    if (out.isEmpty()) out.add(succ.getName());

                    for (int i = (nodeMedia != null ? 0 : 1); i < d; i++) {
                        Data nextSucc = dictionary.successor(dictionary.getRoot(), last);
                        if (nextSucc == null) break;
                        out.add(nextSucc.getName());
                        last = nextSucc.getName();
                    }

                    return String.join(" ", out);
                }

                case "prev": {
                    if (tokens.length != 3) return "Invalid command";
                    String key = tokens[1].toLowerCase();
                    int d;
                    try { d = Integer.parseInt(tokens[2]); } 
                    catch (NumberFormatException e) { return "Invalid number: " + tokens[2]; }

                    ArrayList<String> out = new ArrayList<>();
                    ArrayList<MultimediaItem> nodeMedia = dictionary.get(dictionary.getRoot(), key);
                    if (nodeMedia != null) out.add(key);

                    Data pred = (nodeMedia != null) ? dictionary.predecessor(dictionary.getRoot(), key)
                                                    : dictionary.predecessor(dictionary.getRoot(), key);
                    if (!out.isEmpty() && pred == null) return String.join(" ", out);
                    if (out.isEmpty() && pred == null) return "There are no keys smaller than or equal to " + key;

                    String last = out.isEmpty() ? pred.getName() : key;
                    if (out.isEmpty()) out.add(pred.getName());

                    for (int i = (nodeMedia != null ? 0 : 1); i < d; i++) {
                        Data nextPred = dictionary.predecessor(dictionary.getRoot(), last);
                        if (nextPred == null) break;
                        out.add(nextPred.getName());
                        last = nextPred.getName();
                    }

                    return String.join(" ", out);
                }

                case "first": {
                    Data s = dictionary.smallest(dictionary.getRoot());
                    if (s == null) return "The ordered dictionary is empty.";
                    return s.getName();
                }

                case "last": {
                    Data l = dictionary.largest(dictionary.getRoot());
                    if (l == null) return "The ordered dictionary is empty.";
                    return l.getName();
                }

                case "size": {
                    int n = dictionary.getNumInternalNodes();
                    return "There are " + n + " keys in the ordered dictionary";
                }

                default:
                    return "Invalid command";
            }
        } catch (DictionaryException e) {
            return "No record in the ordered dictionary has key " + (tokens.length > 1 ? tokens[1].toLowerCase() : "") + ".";
        }
    }
}
