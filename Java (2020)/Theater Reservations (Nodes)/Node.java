//kxc180021 Kyle Chan

public class Node <Type> {

	protected Type payload;
	protected Node<Type> right; //next
	protected Node<Type> left;	//prev
	protected Node<Type> up;
	protected Node<Type> down;
	
	Node(){}
	
	Node(Type payload){
		
		this.payload = payload;
		this.right = null;
		this.left = null;
		this.up = null;
		this.down = null;
		
	}
	
	
	
	public void setRight (Node<Type> right){
		this.right = right;
	}
	
	public void setLeft (Node<Type> left) {
		this.left = left;
	}
	
	public void setUp (Node<Type> up) {
		this.up = up;
	}
	
	public void setDown (Node<Type> down) {
		this.down = down;
	}
	
	
	
	public Node<Type> getRight(){
		return this.right;
	}
	
	public Node<Type> getLeft(){
		return this.left;
	}
	
	public Node<Type> getUp(){
		return this.up;
	}
	
	public Node<Type> getDown(){
		return this.down;
	}

	public Type getPayload() {
		return payload;
	}
}
