//kxc180021 Kyle Chan

public class Auditorium {
	
	protected Node<Seat> head;

	Auditorium(){
		head = null;
	}
	
	//recursively appends a new seat node to a 2d grid (doubly linked)
	public Node<Seat> appendSeats(char[][] array, int rows, int cols, int currRow, int currCol, Node<Seat> curNode) {

		if(currRow >= rows || currCol >= cols)
			return null;
		
		int seatRow = currRow + 1;
		char seatCol = (char)(currCol + 65);
		Seat newSeat = new Seat(seatRow, seatCol, array[currRow][currCol]);
		
		Node<Seat> newNode = new Node<Seat>(newSeat);
		
		newNode.setLeft(curNode);
		newNode.setUp(curNode);
		
		newNode.setRight(appendSeats(array, rows, cols, currRow, currCol+1, newNode));
		
		newNode.setDown(appendSeats(array, rows, cols, currRow+1, currCol, newNode));
		
		return newNode;		
	}
	
	public void setSeat(Node<Seat> node, char ticketType) {
		node.getPayload().setTicket(ticketType);
	}
	
	
	
	public char getSeatStatus(Node<Seat> node) {
		return node.getPayload().getTicket();
	}
	
	
}
