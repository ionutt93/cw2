class CustomMap<KeyType, ValueType> {

	private Node<KeyType, ValueType>[] store;
	private int count;
	private int size;

	public CustomMap(int size) {
		this.store = new Node[size];
		this.size = size;
		this.count = 0;
	}

	// if size param is not specified, default size is 100
	public CustomMap() {
		this(100);
	}

	private int hashKey(KeyType key) {
		int index = Math.floorMod(key.hashCode(), store.length);
		return index;
	}

	// resizes the array if over 70% capacity
	private void resizeIfNeeded() {
		if (Math.floor(size * 0.7) < count) {
			System.out.println("Resizing ...");
			Node<KeyType, ValueType>[] oldStore = store;
			size = size * 2;
			count = 0;
			store = new Node[size];

			// adds all the elements from the old store to the new one
			for (int i = 0; i < oldStore.length; i++) {
				Node<KeyType, ValueType> head = oldStore[i];
				while (head != null) {
					add(head.key, head.value);
					head = head.next;
				}
			}

			// checks if all the elements from the previous store have been added to the new
			// one
			for (int i = 0; i < oldStore.length; i++) {
				Node<KeyType, ValueType> head = oldStore[i];
				while (head != null) {
					if (find(head.key) == null) {
						System.out.println("Resizing failed to add " + head.key);
					}
					head = head.next;
				}
			}
		}
	}

	// method to add a new object to the CustomMap given a key and value
	public void add(KeyType key, ValueType value) {
		int index = hashKey(key);

		if (store[index] == null) {
			store[index] = new Node<KeyType, ValueType>(key, value);
		} else {
			Node<KeyType, ValueType> head = store[index];
			while (head != null) {
				if (head.key.equals(key)) {
					head.value = value;
					return;
				}
				head = head.next;
			}

			store[index] = new Node<KeyType, ValueType>(key, value, store[index]);
		}

		count++;
		resizeIfNeeded();
	}

	// method to remove an object from the CustomMap given a key
	public ValueType remove(KeyType key) {
		int index = hashKey(key);

		if (store[index] != null) {

			Node<KeyType, ValueType> head = store[index];
			Node<KeyType, ValueType> previous = null;

			while (head != null && !head.key.equals(key)) {
				previous = head;
				head = head.next;
			}

			if (head != null) {
				if (previous != null) {
					previous.next = head.next;
				} else {
					store[index] = head.next;
				}

				count--;
				return head.value;
			}
		}

		return null;
	}

	// method to return the value of an object given the key
	public ValueType find(KeyType key) {
		int index = hashKey(key);

		if (store[index] != null) {
			Node<KeyType, ValueType> head = store[index];
			while (head != null) {
				if (head.key.equals(key)) {
					return head.value;
				}
				head = head.next;
			}
		}
		return null;
	}
}

class Node<KeyType, ValueType> {
	public final KeyType key;
	public ValueType value;
	public Node<KeyType, ValueType> next;

	Node(KeyType key, ValueType value, Node<KeyType, ValueType> next) {
		this.key = key;
		this.value = value;
		this.next = next;
	}

	Node(KeyType key, ValueType value) {
		this(key, value, null);
	}
}

public class Q5Main {

	public static void main(String[] args) {
		CustomMap<String, Integer> map = new CustomMap(10);

		// adding dummy data for testing
		for (int i = 0; i < 100; i++) {
			map.add("Key " + i, i);
			System.out.println("Added " + i);
		}

		// checking if the data has been added
		for (int i = 0; i < 100; i++) {
			System.out.println("Found " + map.find("Key " + i));
		}

		// checking if the data can be removed
		for (int i = 0; i < 100; i++) {
			System.out.println("Removed " + map.remove("Key " + i));
		}
	}

}
