

public class Q8Main{
	
	public static void main(String[] args){
		// args 0 - name of file to read in text
		String inputFileName = null;
		// args 1 - name of file to read in list of words to redact
		String toRedact = null;
		// args 2 - name of file to write out the redacted text
		String outputFileName = null;
		
		if(args.length == 2){
			inputFileName = args[0];
			toRedact = args[1];
		}
		else if(args.length == 3){
			inputFileName = args[0];
			toRedact = args[1];
			outputFileName = args[2];
		}
		
		// call method to redact words from input text
		new Q8Main().redactText(inputFileName,toRedact,outputFileName);
	}
	
	public void redactText(String input, String toRedact, String output){
		System.out.println(input);
		System.out.println(toRedact);
		System.out.println(output);
	}
}