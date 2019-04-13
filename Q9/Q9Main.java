

public class Q9Main{
	
	public static void main(String[] args){
		// args 0 - name of file to read in the text to encrypt
		String inputFileName = null;
		// args 1 - name of file to write out the encrypted text
		String outputFileName = null;
		if(args.length == 1){
			inputFileName = args[0];
		}
		else if(args.length == 2){
			inputFileName = args[0];
			outputFileName = args[1];
		}
		
		// call method to encrypt text
		new Q9Main().encrypteText(inputFileName,outputFileName);
	}
	
	public void encrypteText(String input, String output){
		System.out.println(input);
		System.out.println(output);
	}
}