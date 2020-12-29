//kxc180021 Kyle Chan

public class Seat {

	protected int row;
	protected char seat;
	protected char ticketType;
	
	Seat(){}
	
	Seat(int row, char seat, char ticketType){
		
		this.row = row;
		this.seat = seat;
		this.ticketType = ticketType;
		
	}
	
	
	
	public void setTicket(char ticketType) {
		this.ticketType = ticketType;
	}
	
	
	
	public char getTicket() {
		return ticketType;
	}
}
