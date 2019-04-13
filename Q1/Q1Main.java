

public class Q1Main{
	
	public static void main(String[] args){
		// args 0 - name of file to read in a list of names
		String inputFileName = null;
		// args 1 - name of file to write out the sorted list of names
		String outputFileName = null;
		if(args.length == 1){
			inputFileName = args[0];
		}
		else if(args.length == 2){
			inputFileName = args[0];
			outputFileName = args[1];
		}
		
		// call method to bubble sort list of names
		new Q1Main().sortNames(inputFileName,outputFileName);
	}
	
	public void sortNames(String input, String output){
		System.out.println(input);
		System.out.println(output);
	}
}