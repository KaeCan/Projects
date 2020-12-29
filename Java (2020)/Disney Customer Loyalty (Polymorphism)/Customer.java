//Kyle Chan kxc180021
public class Customer {

	protected String firstName;
	protected String lastName;
	protected String guestID;
	protected float spent;
	
	public Customer() {
		firstName = "";
		lastName = "";
		guestID = "";
		spent = 0;
	}
	
	public Customer(String first, String last, String ID, float money) {
		firstName = first;
		lastName = last;
		guestID = ID;
		spent = money;
	}
	
	public String getFirstName() {
		return firstName;
	}
	
	public String getLastName() {
		return lastName;
	}
	
	public String getID() {
		return guestID;
	}
	
	public float getSpent() {
		return spent;
	}
	
	public void setSpent(float amount) {
		spent = amount;
	}
	
	public String getStatus() {
		return "regular";
	}
}
