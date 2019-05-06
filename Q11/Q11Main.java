/* This program uses brute force to get the 100th, 1000th, 100,000th and millionth
lexicographic permutation  of the string ABCDEFGHIJ.*/

public class Q11Main {

	// used to time the execution of the program
	final static long startTime = System.currentTimeMillis();

	String[] perm = new String[] { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

	public static void main(String[] args) {

		long[] numPerms = new long[] { 100, 1000, 100000, 1000000 };

		for (long i : numPerms) {

			String permNum = new Q11Main().getPermutation(i);
			System.out.println(String.format("The %dth lexicographic permutation is: %s ", i, permNum));
			final long endTime = System.currentTimeMillis();
			System.out.println("Total execution time: " + (endTime - startTime) + " milliseconds");
		}
	}

	public String getPermutation(long numPerm) {

		int count = 1;

		while (count < numPerm) {
			int N = perm.length;
			int i = N - 1;
			// check if letter at position i-1 is lexicographically greater than letter at
			// position i
			while (perm[i - 1].compareTo(perm[i]) >= 0) {
				i = i - 1; // if so, decrease i by 1

			}
			int j = N;
			// check if letter at position j-1 is lexicographically smaller than letter at
			// position i-1
			while (perm[j - 1].compareTo(perm[i - 1]) <= 0) {
				j = j - 1; // if so, decrease j by 1
			}
			// swap values at position i-1 and j-1
			swap(i - 1, j - 1);

			i++;
			j = N;
			while (i < j) {
				swap(i - 1, j - 1);
				i++;
				j--;
			}
			count++;
		}

		// the string array perm has been ordered into the correct permutation
		// therefore, we want to return the ordered letters of the array
		String permNum = "";
		for (int k = 0; k < perm.length; k++) {
			permNum = permNum + perm[k];
		}

		return permNum;
	}

	// method to switch the positions of two elements in the String array
	public void swap(int i, int j) {
		String temp = perm[i];
		perm[i] = perm[j];
		perm[j] = temp;
	}
}