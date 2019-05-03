import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Q1Main {

	// bubble sort array in place
	public void sort(String[] names) {
		boolean isSorted = false;
		while (!isSorted) {
			isSorted = true;
			for (int i = 1; i < names.length; i++) {
				if (names[i - 1].compareTo(names[i]) > 0) {
					String temp = names[i];
					names[i] = names[i - 1];
					names[i - 1] = temp;
					isSorted = false;
				}
			}
		}
	}

	// reads file and splits it into names
	public String[] readNames(String pathString) throws IOException, URISyntaxException {
		File file = Paths.get(pathString).toFile();
		FileReader fileReader = new FileReader(file);
		BufferedReader reader = new BufferedReader(fileReader);

		StringBuilder content = new StringBuilder();
		String line;
		while ((line = reader.readLine()) != null) {
			content.append(line);
			content.append("\n");
		}
		reader.close();

		return content.toString().split(",");
	}

	// writes the names to a file
	public void writeNamesToFile(String pathString, String[] names) throws IOException, URISyntaxException {
		File file = Paths.get(pathString).toFile();
		FileWriter fileWriter = new FileWriter(file);
		BufferedWriter writer = new BufferedWriter(fileWriter);

		writer.write(String.join(",", Arrays.asList(names)));
		writer.close();
	}

	// invocation method which reads the names, sorts them and writes them to a file
	public void sortNames(String input, String output) throws IOException, URISyntaxException {
		System.out.println(input);
		System.out.println(output);
		final String[] names = readNames(input);
		sort(names);
		writeNamesToFile(output, names);
	}

	public static void main(String[] args) throws IOException, URISyntaxException {
		// args 0 - name of file to read in a list of names
		String inputFileName = "names.txt";
		// args 1 - name of file to write out the sorted list of names
		String outputFileName = "sorted.txt";
		if (args.length == 1) {
			inputFileName = args[0];
		} else if (args.length == 2) {
			inputFileName = args[0];
			outputFileName = args[1];
		}
		// call method to bubble sort list of names
		new Q1Main().sortNames(inputFileName, outputFileName);
	}

}