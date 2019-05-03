
/* This program redacts redactable words from a given text file.
A text file containing a pre-defined set of words to redact is also passed in as a program argument.
 Once all the redactable words have been redacted, the new redacted text is saved in an output file*/

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class Q8Main {

	// private ArrayList<String> warAndPeace = new ArrayList<>();
	// private ArrayList<String> redactWords = new ArrayList<>();

	public static void main(String[] args) throws IOException {
		// args 0 - name of file to read in text
		String inputFileName = "warandpeace.txt";
		// args 1 - name of file to read in list of words to redact
		String toRedact = "redact.txt";
		// args 2 - name of file to write out the redacted text
		String outputFileName = "redacted.txt";

		if (args.length == 2) {
			inputFileName = args[0];
			toRedact = args[1];
		} else if (args.length == 3) {
			inputFileName = args[0];
			toRedact = args[1];
			outputFileName = args[2];
		}

		// call method to redact words from input text
		new Q8Main().redactText(inputFileName, toRedact, outputFileName);
	}

	public void redactText(String inputFileName, String toRedact, String outputFileName) throws IOException {

		ArrayList<String> redactWords = readFile(toRedact);
		ArrayList<String> warAndPeace = readFile(inputFileName);
		redact(warAndPeace, redactWords);
		System.out.println(redactWords);
		saveRedactedText(outputFileName, warAndPeace);

	}

	// function to fill the length of the redacted word with '*'
	private static String fill(int length) {
		char[] chars = new char[length];
		Arrays.fill(chars, '*');
		return new String(chars);
	}

	// method to redact a string arraylist given an arraylist of words to redact
	public void redact(ArrayList<String> text, ArrayList<String> redactWords) {

		for (int i = 0; i < text.size(); i++) { // loop through array list of text
			String textWord = text.get(i);
			if (textWord.length() > 1) {
				replaceRedactWords(textWord, text, redactWords, i); // replace all words in redactWords first
				if (!redactWords.contains(textWord)) { // if textWord is a redactWord it should already have been
																								// replaced
					replaceNouns(textWord, text, redactWords, i); // then replace other redactable words aka nouns
				}
			}
		}
	}

	// method to replace all redactWords that are in the text with stars
	private void replaceRedactWords(String textWord, ArrayList<String> text, ArrayList<String> redactWords, int i) {
		String redactWord = null;
		for (int j = 0; j < redactWords.size(); j++) { // loop through array list of redactWords
			redactWord = redactWords.get(j);

			if (textWord.contains(redactWord)) {
				String stars = textWord.replaceAll(redactWord, fill(redactWord.length()));
				text.set(i, stars); // replace index i in text with new stars string
				break; // no need to continue loop as textWord has been replaced in the text

			}
		}
	}

	// method to replace all redactible words in the text( that are not already in
	// redactWords ) with stars
	private void replaceNouns(String textWord, ArrayList<String> text, ArrayList<String> redactWords, int i) {

		if (i != 0) { // not first word in text
			if (Character.isUpperCase(textWord.charAt(0))) { // if first character of textWord is a Capital letter
				String prevWord = text.get(i - 1); // get previous word
				if (prevWord.length() > 1) {
					char c = (prevWord.charAt(prevWord.length() - 1)); // get last character of previous word
					if ((c != '.') && (c != '!') && (c != '?') && (c != '\'')) { // word is not after ./!/?/'
						String stars = textWord.replaceAll("[A-Za-z]", "*"); // replace only alphabetical letters with
																																	// stars
						text.set(i, stars); // replace index i in text with new stars string
					}
				}
			}
		}
	}

	private ArrayList<String> readFile(String inputFileName) {
		ClassLoader classLoader = getClass().getClassLoader(); // must load class
		ArrayList<String> arrayList = new ArrayList<String>();

		try (InputStream in = classLoader.getResourceAsStream(inputFileName);
				BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {
			String line = null;
			while ((line = reader.readLine()) != null) {
				String[] words = line.split(" ");
				arrayList.addAll(Arrays.asList(words));
			}
		} catch (IOException x) {
			System.err.println(x);
		}
		System.out.println(arrayList);
		return arrayList;
	}

	public void saveRedactedText(String outputFileName, ArrayList<String> warAndPeace) {
		PrintWriter writer = null;
		try {
			writer = new PrintWriter(outputFileName, "UTF-8");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		StringBuilder builder = new StringBuilder();
		for (String s : warAndPeace) {
			builder.append(s + " ");
		}
		String str = builder.toString();
		writer.println(str);
		writer.close(); // must close writer
	}

}
