//Kyle Chan kxc180021

//"PREFERRED" CUSTOMERS
public class Gold extends Customer {


	protected float discount;
	
	public Gold(String first, String last, String ID, float spent, float discount) {
		super(first, last, ID, spent);
		this.discount = discount/100;
	}
	
	public float getDiscount() {
		return discount;
	}
	
	public void promoteTier() {
		discount += 0.05;
		
	}
	
	public void setTier(float discount) {
		this.discount = discount;
	}
	
	public String getStatus() {
		return "gold";
	}
}
