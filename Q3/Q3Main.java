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
		// read line by line
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

	// moves all the names smaller than the pivot before the pivot
	// returns new partitioning index
	private int partition(final String[] names, final int lo, final int hi) {
		final String pivot = names[hi]; // the last element becomes the pivot
		int i = lo;

		for (int j = lo; j < hi; j++) {
			// if an element is smaller than the pivot, move it to the left side
			if (names[j].compareTo(pivot) <= 0) {
				String temp = names[i];
				names[i] = names[j];
				names[j] = temp;
				i++;
			}
		}

		// move the pivot to the correct position, where all the elements on the left
		// are smaller than it and all the elements on the right are bigger
		String temp = names[i];
		names[i] = names[hi];
		names[hi] = temp;

		return i;
	}

	// quick sort algorithm
	private void sort(final String[] names, final int li, final int hi) {
		if (li < hi) {
			// partitions the array and updates the partition index
			int pivotIndex = partition(names, li, hi);
			// recusivelly calls itself on the left partition
			sort(names, li, pivotIndex - 1);
			// and the right partition
			sort(names, pivotIndex + 1, hi);
		}
	}

	// reads the names, sorts them and writes them to a file
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
		String outputFileName = "sorted_names.txt";
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