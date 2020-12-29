//kxc180021 Kyle Chan


public class BSTree <Type extends Comparable<Type>> {

	protected Node<Type> root;
	
	BSTree(){}
	
	BSTree(Node<Type> node){
		root = node;
	}
	
	public void changeRoot(Node<Type> node) {
		root = node;
	}
	
	public Node<Type> getRoot(){
		return root;
	}
	
	//driver for tree insert
	public void insert(Type key) {
		this.root = insertNode(this.root, key);
	}
	
	public Node<Type> insertNode(Node<Type> root, Type key) {
		
		if(root == null) {
			root = new Node<Type>(key);
			return root;
		}
		
		int compare = root.getPayload().compareTo(key);
		
		if(compare > 0) {
			root.setLeft(insertNode(root.getLeft(), key));
		}
		else if (compare < 0) {
			root.setRight(insertNode(root.getRight(), key));
		}
		
		return root;
	}
	
	//driver for tree search
	public Node<Type> search(Type key){

		if(root != null) {
			return searchNode(root, key);
		}
		else
			return null;
	}
	
	public Node<Type> searchNode(Node<Type> root, Type key){ //key will be type DVD in this case
		
		if(root == null || root.getPayload().compareTo(key) == 0) { //compareTo overridden to return result of string comparisons
			return root;
		}
		
		else if(root.getPayload().compareTo(key) > 0)
			return searchNode(root.getLeft(), key);
		else
			return searchNode(root.getRight(), key);
		
	}
	
	//driver for tree deletion
	public void remove(Type key) {
		root = removeNode(root, key);
	}
	
	//helper
	public Node<Type> smallestPayload(Node<Type> root) {
		
		if(root.getLeft() == null) {
			return root;
		}
		else {
			return smallestPayload(root.getLeft());
		}
	
	}
	
	public Node<Type> removeNode(Node<Type> root, Type key){
		
		if (root == null)
			return null;
		
		int compare = root.getPayload().compareTo(key);
		
		if (compare > 0) {
			root.setLeft(removeNode(root.getLeft(), key));
		}
		else if (compare < 0) {
			root.setRight(removeNode(root.getRight(), key));
		}
		
		else { //if titles are equal
			
			//there is only one leaf
			if (root.getLeft() == null) {
				return root.getRight();
			}
			
			else if (root.getRight() == null) {
				return root.getLeft();
			}
			
			//two leaves
			Node<Type> temp = root;
			temp = smallestPayload(temp.getRight());
			root.setPayload(temp.getPayload());
			
			//replace with successor node
			root.setRight(removeNode(root.getRight(), temp.getPayload()));
			
		}
		
		return root;
	}

}
