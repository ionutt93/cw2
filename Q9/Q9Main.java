
/* This program implements a Vigenere cypher a to encrypt a message of any length using the Keyword LOVELACE */

import java.io.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Q9Main {

	public static void main(String[] args) throws IOException {
		// args 0 - name of file to read in the text to encrypt
		String inputFileName = "sonnet-lxiii.txt";
		// args 1 - name of file to write out the encrypted text
		String outputFileName = "encrypted-sonnet-lxiii.txt";
		if (args.length == 1) {
			inputFileName = args[0];
		} else if (args.length == 2) {
			inputFileName = args[0];
			outputFileName = args[1];
		}

		// call method to encrypt text
		new Q9Main().encryptText(inputFileName, outputFileName);
	}

	public void encryptText(String inputFileName, String outputFileName) throws IOException {

		String original_msg = readFile(inputFileName);
		System.out.println("\nOriginal:\n" + original_msg);
		String new_msg = remove_ichars(original_msg);
		System.out.println("\nAfter punctuation removal:\n" + new_msg);

		String encrypted_msg = encrypt(new_msg, "LOVELACE");
		saveEncryptedMessage(outputFileName, encrypted_msg);
		System.out.println("\nEncrypted:\n" + encrypted_msg);
	}

	// function that removes all the numbers, punctuations from a String
	private String remove_ichars(String original_msg) {
		original_msg = original_msg.replaceAll("[^a-zA-Z]", "");
		return original_msg;
	}

	private int getPosition(char c) {
		return (int) Character.toUpperCase(c) - 65; // subtract 65 to return position value in alphabet
	}

	// function match the message to its key by repeating the keyword until it is
	// the same length as the message
	private String matchString(String message, String keyword) {
		final String[] keyChars = keyword.split(""); // create String array

		// map each char in message to corresponding char in keyword
		return IntStream.range(0, message.length()).mapToObj(i -> keyChars[i % keyChars.length])
				.collect(Collectors.joining());
	}

	// in java % produces the remainder, so we implement the modulus this way to
	// take into account negative numbers
	private int mod(int a, int b) {
		return ((a % b) + b) % b; // use modulo to deal with ascii values greater than 26. Alphabet will loop back
															// round.
	}

	// function to encrypt the message character m using the key character k
	private char encryptChar(char m, char k) {
		int a = getPosition(m) + getPosition(k);// add the position values of m and k together
		return (char) (mod(a, 26) + 65); // add 65 to return the corresponding uppercase letter value
	}

	// function to encrypt a message using the Vigenère cypher method
	private String encrypt(String message, String key) {
		// ca = ma + kb mod 26
		final String matchedKey = matchString(message, key);
		return IntStream.range(0, message.length()) // for each letter in the message...
				.mapToObj(i -> encryptChar(message.charAt(i), matchedKey.charAt(i))) // ...encrypt the letter using the
																																							// corresponding key letter
				.map(String::valueOf) // turn unicode values back to Strings
				.collect(Collectors.joining()); // join the String letters together
	}

	// function to read data from an input stream
	private String readFromInputStream(InputStream inputStream) throws IOException {
		StringBuilder resultStringBuilder = new StringBuilder();
		try (BufferedReader br = new BufferedReader(new InputStreamReader(inputStream))) {
			String line;
			while ((line = br.readLine()) != null) {
				resultStringBuilder.append(line).append("\n");
			}
		}
		return resultStringBuilder.toString();
	}

	// function to read text from file
	private String readFile(String fileName) throws IOException {
		ClassLoader classLoader = getClass().getClassLoader();
		InputStream inputStream = classLoader.getResourceAsStream(fileName);
		String data = readFromInputStream(inputStream);
		return data;
	}

	// function to save the encrypted message in a new file
	private void saveEncryptedMessage(String outputFileName, String encryptedMessage) {
		try {
			BufferedWriter buffWriter = new BufferedWriter(new FileWriter((outputFileName)));
			buffWriter.append(encryptedMessage);
			buffWriter.close(); // must close file when done
		} catch (IOException exp) {
			exp.printStackTrace();
		}
	}
}
