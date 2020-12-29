//kxc180021 Kyle Chan

public class Node <Type extends Comparable<Type>> {

	protected Type payload;
	protected Node<Type> right;
	protected Node<Type> left;
	
	Node(){}
	
	Node(Type payload){
		this.payload = payload;
		this.right = null;
		this.left = null;
	}
	
	public void setRight (Node<Type> right) {
		this.right = right;
	}
	
	public void setLeft (Node<Type> left) {
		this.left = left;
	}
	
	public void setPayload (Type payload) {
		this.payload = payload;
	}
	
	public Node<Type> getRight() {
		return this.right;
	}
	
	public Node<Type> getLeft() {
		return this.left;
	}
	
	public Type getPayload() {
		return payload;
	}
}
