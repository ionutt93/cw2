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

public class Q3Main {

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

	private int partition(final String[] names, final int lo, final int hi) {
		final String pivot = names[hi];
		int i = lo;

		for (int j = lo; j < hi; j++) {
			if (names[j].compareTo(pivot) <= 0) {
				String temp = names[i];
				names[i] = names[j];
				names[j] = temp;
				i++;
			}
		}

		String temp = names[i];
		names[i] = names[hi];
		names[hi] = temp;

		return i;
	}

	private void sort(final String[] names, final int li, final int hi) {
		if (li < hi) {
			int pivotIndex = partition(names, li, hi);
			sort(names, li, pivotIndex - 1);
			sort(names, pivotIndex + 1, hi);
		}
	}

	public void sortNames(String input, String output) throws Exception {
		System.out.println(input);
		System.out.println(output);
		final String[] names = readNames(input);
		sort(names, 0, names.length - 1);
		writeNamesToFile(output, names);
	}

	public static void main(String[] args) throws Exception {
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

		// call method to quick sort list of names
		new Q3Main().sortNames(inputFileName, outputFileName);
	}

}