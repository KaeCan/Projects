//Kyle Chan kxc180021

//"PREFERRED" CUSTOMERS
public class Platinum extends Gold {

	protected int bonusBucks;
	protected int bucksSpent;
	
	public Platinum(String first, String last, String ID, float spent, float discount ,float bonusBucks) {
		super(first, last, ID, spent, discount);
		this.bonusBucks = (int)bonusBucks;
		bucksSpent = 0;
	}

	public int getBucks() {
		return bonusBucks;
	}
	
	public void addBucks(int change) {
		bonusBucks += change;
	}
	
	public void resetBucks() {
		bonusBucks = 0;
	}
	
	public int getBucksSpent() {
		return bucksSpent;
	}
	
	public void addBucksSpent(int change) {
		bucksSpent += change;
	}
	
	public String getStatus() {
		return "plat";
	}
}
