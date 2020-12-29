//kxc180021 Kyle Chan

public class DVD implements Comparable<DVD>{

	protected String title;
	protected int available;
	protected int rented;
	
	DVD(){}
	
	DVD(String title, int available, int rented){
		this.title = title;
		this.available = available;
		this.rented = rented;
	}
	
	public void changeAvail(int change) {
		available += change;
	}
	
	public void changeRented(int change) {
		rented += change;
	}
	
	public String getTitle() {
		return title;
	}
	
	public int getAvail() {
		return available;
	}
	
	public int getRented() {
		return rented;
	}
	
	@Override
	public int compareTo(DVD key) {
		return this.title.compareTo(key.title);
	}
	
}
