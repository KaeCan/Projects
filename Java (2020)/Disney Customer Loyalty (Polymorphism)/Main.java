//Kyle Chan kxc180021

import java.util.Scanner;
import java.util.Arrays;
import java.io.*;

public class Main {
	
	static Customer[] regCustArr = new Customer[0];
	static Customer[] prefCustArr = new Customer[0];
	
	static Scanner input = new Scanner(System.in);
	
	static class Cup {
		
		public float diameter, height, ounces, typeCost;
		
		Cup(){
			diameter = 0;
			height = 0;
			ounces = 0;
		}
		
		Cup(char size, String type){
			
			switch(size) {
			
				case 'S':
					diameter = 4;
					height = (float)4.5;
					ounces = 12;
					break;
				case 'M':
					diameter = (float)4.5;
					height = (float)5.75;
					ounces = 20;
					break;
				case 'L':
					diameter = (float)5.5;
					height = 7;
					ounces = 32;
					break;
				default:
					diameter = 0;
					height = 0;
					ounces = 0;
			}
			
			switch(type) {
			
				case "soda":
					typeCost = (float)0.2;
					break;
				case "tea":
					typeCost = (float)0.12;
					break;
				case "punch":
					typeCost = (float)0.15;
					break;
				default:
					typeCost = 0;
			
			}
		}
		
	}
	
	public static void prefCustToArray(String filename) throws IOException {
		
		//open file
		try {
		FileInputStream file = new FileInputStream(filename);
		Scanner fread = new Scanner(file);
		int i = 0;
		String firstName, lastName, guestID;
		float spent;
		String discOrBonus;
		String temp;
		float strToFloat;
		
		while(fread.hasNextLine()){
			
			if(fread.hasNext()) {
				//grow the array size every time there is a new customer to be read in
				//file contents are read line-by-line
				Customer[] destArray = Arrays.copyOf(prefCustArr, i+1);
				prefCustArr = destArray;
				
				guestID = fread.next();
				firstName = fread.next();
				lastName = fread.next();
				spent = fread.nextFloat();
				
				discOrBonus = fread.next();
				
				temp = "";
				for(int j = 0; j < discOrBonus.length(); j++) {
					if(Character.isDigit(discOrBonus.charAt(j))) {
						temp += discOrBonus.charAt(j); 
					}
				}
				
				strToFloat = Float.parseFloat(temp);
				
				if(discOrBonus.charAt(discOrBonus.length()-1) == '%') {
					prefCustArr[i] = new Gold(firstName, lastName, guestID, spent, strToFloat);

				}
				else {
					prefCustArr[i] = new Platinum(firstName, lastName, guestID, spent, 0, strToFloat); //plats have no discounts

				}
				
				i++;
			}
			else
				break;
			
			
			
		}
		
		fread.close();
		} catch (Exception e) {}
		
	}
	
	public static void regCustToArray(String filename) throws IOException {
		
		//open file
		Scanner fread = new Scanner(new FileInputStream(filename));
		
		//obtain file contents | read line-by-line
		int i = 0;
		String firstName, lastName, guestID;
		float spent;
		
		while(fread.hasNextLine()){
			if(fread.hasNext()) {
			
				//grow the array size every time there is a new customer to be read in
				Customer[] destArray = Arrays.copyOf(regCustArr, i+1);
				regCustArr = destArray;
				
				guestID = fread.next();
				firstName = fread.next();
				lastName = fread.next();
				spent = fread.nextFloat();
				
				regCustArr[i] = new Customer(firstName, lastName, guestID, spent);
				
				i++;
			}
			else
				break;
			
		}
		
		fread.close();
		
	}
	
	public static boolean validID (String id) {
		
		for(int i = 0; i < id.length(); i++) {
			if(!Character.isDigit(id.charAt(i)))
				return false;
		}
		
		for(int i = 0; i < regCustArr.length; i++) {
			if(id.equals(regCustArr[i].getID())) {
				return true;
			}
		}
		
		for(int i = 0; i < prefCustArr.length; i++) {
			if(id.equals(prefCustArr[i].getID())) {
				return true;
			}
		}
		
		
		return false;
	}
	
	public static boolean validDrinkSize (String drinkSize) {
		
		switch(drinkSize) {
			
			case "S":
			case "M":
			case "L":
				return true;
		
			default:
				return false;
		}
		
	}
	
	public static boolean validDrinkType (String type) {
		
		switch(type) {
		
			case "punch":
			case "tea":
			case "soda":
				return true;
			
			default:
				return false;
		}
	}
	
	public static boolean validSqInP(String price) {
		
		for(int i = 0; i < price.length(); i++) {
		
			if(Character.isDigit(price.charAt(i)) || price.charAt(i) == '.')
				continue;
			else
				return false;
			}
		
		float cost = Float.parseFloat(price);
		
		if(cost >= 0)
			return true;
		else
			return false;
	}
	
	public static boolean validQuantity(String amount) {
		
		for(int i = 0; i < amount.length(); i++) {
			
			if(Character.isDigit(amount.charAt(i)))
				continue;
			else
				return false;
			}
		
		int count = Integer.parseInt(amount);
		
		if(count > 0)
			return true;
		else
			return false;
	}
	
	public static int findCustomer (String ID, String[] arrayType) {
		
		int i;
		
		//check regular customer file
		if(regCustArr.length != 0) {
			for(i = 0; i < regCustArr.length; i++) {
				if(ID.equals(regCustArr[i].getID())) {
					arrayType[0] = "regular";
					return i;
				}
			}
		}
		
		if(prefCustArr.length != 0) {
			for(i = 0; i < prefCustArr.length; i++) {
				if(ID.equals(prefCustArr[i].getID())) {
					arrayType[0] = "preferred";
					return i;
				}
			}
		}
		
		return -1; //IF my order validations are perfect, this should never be returned
	}
	
	public static float surfaceArea (Cup drink) {
		
		float squareInches;
		
		float radius = drink.diameter/2;
		float pi = (float)3.1415;
		
		//SA = 2(pi)rh //no base included
		squareInches = 2 * pi * radius * drink.height;		
		
		return squareInches;
	}
	
	public static void preferredOrders(String[] lineOrder, Cup drink) {
		
		float totalSpent, subtotal, subWithDiscountOrBB; //differentiate before and after discount/ bonus bucks
		String ID = lineOrder[0];
		float sqInCost = Float.parseFloat(lineOrder[3]);
		int quantity = Integer.parseInt(lineOrder[4]);
		
		String[] arrayType = new String[1];
		
		//sync customer with order line
		int currCustomer = findCustomer(ID, arrayType);
		
		if(currCustomer != -1) {
			subtotal = quantity * ((drink.typeCost) * (drink.ounces) + (sqInCost) * (surfaceArea(drink)));
			//check for Gold or Platinum status
			String prefType = prefCustArr[currCustomer].getStatus();
			int newBonusBucks = 0;
			
			if(prefType == "gold") {
			
				if(subtotal > 0) {
					
					subWithDiscountOrBB = (subtotal) * (1 - ((Gold)prefCustArr[currCustomer]).getDiscount());

					//if new discount/status threshold is reached
					if (subWithDiscountOrBB + prefCustArr[currCustomer].getSpent() >= 200 && ((Gold)prefCustArr[currCustomer]).getDiscount() >= 0.15) { //Platinum status is reached
						
						totalSpent = subWithDiscountOrBB + prefCustArr[currCustomer].getSpent();
						
						newBonusBucks = ((int)totalSpent - 200) / 5; //quotient will be rounded down
						
						//create new platinum customer
						prefCustArr[currCustomer] = new Platinum(prefCustArr[currCustomer].getFirstName(), prefCustArr[currCustomer].getLastName(), prefCustArr[currCustomer].getID(), totalSpent, 0, newBonusBucks);

					}
					
					else if(subWithDiscountOrBB + prefCustArr[currCustomer].getSpent() >= 150 && ((Gold)prefCustArr[currCustomer]).getDiscount() < 0.15) { //reached 15% mark
						
						((Gold)prefCustArr[currCustomer]).promoteTier(); //increase discount
						preferredOrders(lineOrder, drink); //rerun order with new discount
					
					}
					
					else if (subWithDiscountOrBB + prefCustArr[currCustomer].getSpent() >= 100 && ((Gold)prefCustArr[currCustomer]).getDiscount() < 0.1) {//reached 10% mark
						
						((Gold)prefCustArr[currCustomer]).promoteTier(); //increase discount
						preferredOrders(lineOrder, drink); //rerun order with new discount

					}
					else { //no upgrades or promotions available
						totalSpent = subWithDiscountOrBB + prefCustArr[currCustomer].getSpent();
						
						prefCustArr[currCustomer].setSpent(totalSpent);
					}

				}
			}
			
			else {
				
				if(subtotal > 0) {
					int usedBB = ((Platinum)prefCustArr[currCustomer]).getBucks();
					
					if(((Platinum)prefCustArr[currCustomer]).getBucks() > subtotal) { //if customer has more bonus bucks than order subtotal
						usedBB = (int)subtotal;
						
						subWithDiscountOrBB = (subtotal) - (usedBB);
						((Platinum)prefCustArr[currCustomer]).addBucks(-usedBB);
						((Platinum)prefCustArr[currCustomer]).addBucksSpent(usedBB);
						
						totalSpent = subWithDiscountOrBB + prefCustArr[currCustomer].getSpent();
						newBonusBucks = (((int)totalSpent - 200) / 5) - ((Platinum)prefCustArr[currCustomer]).getBucksSpent() - ((Platinum)prefCustArr[currCustomer]).getBucks();
						
						((Platinum)prefCustArr[currCustomer]).addBucks(newBonusBucks);
						prefCustArr[currCustomer].setSpent(totalSpent);
					}
					else {				
						subWithDiscountOrBB = (subtotal) - (usedBB); //use up bonus bucks
						((Platinum)prefCustArr[currCustomer]).resetBucks(); //remove bonus bucks
						((Platinum)prefCustArr[currCustomer]).addBucksSpent(usedBB);
						
						//calculate bonus bucks, starting from last known interval of 5
						totalSpent = subWithDiscountOrBB + (prefCustArr[currCustomer].getSpent() % 5);
						newBonusBucks = (((int)totalSpent) / 5);
						
						((Platinum)prefCustArr[currCustomer]).addBucks(newBonusBucks);
						prefCustArr[currCustomer].setSpent(subWithDiscountOrBB + prefCustArr[currCustomer].getSpent());
						 
					}
					
				}

			}
		}
		
	}
	public static void processOrders(String[] lineOrder) {
		
		float totalSpent, subtotal; //differentiate before and after discount/ bonus bucks
		
		String ID = lineOrder[0], drinkType = lineOrder[2];	//given dedicated variables for clarity
		char drinkSize = lineOrder[1].charAt(0);
		float sqInCost = Float.parseFloat(lineOrder[3]);
		int quantity = Integer.parseInt(lineOrder[4]);
		
		String[] arrayType = new String[1];
		
		//sync customer with order line
		int currCustomer = findCustomer(ID, arrayType);
		
		if(currCustomer != -1) {
			Cup drink = new Cup(drinkSize, drinkType);
			subtotal = quantity * ((drink.typeCost) * (drink.ounces) + (sqInCost) * (surfaceArea(drink)));
			
			if(arrayType[0] == "regular" ) { //FOR REGULAR CUSTOMERS
				
				//run order
				//three different outcomes: stay as a regular after transaction, moved up a tier in gold (or to gold), moved up to platinum (from gold)
				//run calculations and update customer total spent
				//update customer tier if needed
				
				//promotion sequence
				if(subtotal + regCustArr[currCustomer].getSpent() >= 50) { //customer hits Gold status threshold

					//transfer regular customer to preferred customer array
					Customer[] destArray = Arrays.copyOf(prefCustArr, prefCustArr.length + 1); //grow and make room in preferred customer array
					prefCustArr = destArray;
					
					//move customer over to preferred array
					prefCustArr[prefCustArr.length - 1] = new Gold(regCustArr[currCustomer].getFirstName(), regCustArr[currCustomer].getLastName(), regCustArr[currCustomer].getID(), regCustArr[currCustomer].getSpent(), 5);
					
					regCustArr[currCustomer] = new Customer(); //remove data from old location
					
					Customer[] tempArray = Arrays.copyOf(regCustArr, regCustArr.length - 1);
					
					for(int i = 0, j = 0; i < tempArray.length; i++, j++) { //move and shift over customer data to new, smaller array (maintain order)
						
						if(regCustArr[j].getID().isEmpty())	//do not move data from empty customer index
							i--;
						else {
							tempArray[i] = regCustArr[j];
						}
					}
					
					regCustArr = tempArray;
					
					preferredOrders(lineOrder, drink);
					
				}
				else { //proceed as normal
					totalSpent = subtotal + regCustArr[currCustomer].getSpent();
					
					regCustArr[currCustomer].setSpent(totalSpent);
					
				}

			}
			
			else if(arrayType[0] == "preferred") //FOR PREFERRED CUSTOMERS
				preferredOrders(lineOrder, drink);
			
		}
		
			
	}
	
	public static void readOrders(String filename) throws IOException {
		
		Scanner fread = new Scanner(new FileInputStream(filename));
		
		String lineText;
		
		//process/loop thru file line-by-line
		while(fread.hasNextLine()) {
			
			if(fread.hasNext()) {
				
				lineText = fread.nextLine();
				String[] lineOrder = lineText.split(" ");
				
				//validate all entries
				
				//if the line has anything less or greater than 5
				if(lineOrder.length != 5)
					continue;
				
				//valid ID (string)
				if(!validID(lineOrder[0]))
					continue;
					
				//valid drink size (char)
				if(!validDrinkSize(lineOrder[1]))
					continue;
					
				//valid drink type (string)
				if(!validDrinkType(lineOrder[2]))
					continue;
					
				//valid square in price (float)
				if(!validSqInP(lineOrder[3]))
					continue;
					
				//valid quantity (int)
				if(!validQuantity(lineOrder[4]))
					continue;
					
				//if all entries on line are valid, proceed to processing and calculations
				
				processOrders(lineOrder);
			}
			else
				break;
			
		}

		
	}
	
	public static void report() throws IOException {
		
		//regular customer file
		File txt = new File("customer.dat");
		FileOutputStream filestream = new FileOutputStream(txt);
		PrintWriter fwrite = new PrintWriter(filestream);
		
		for(int i = 0; i < regCustArr.length; i++) {
			//write customer data line-by-line
			fwrite.print(regCustArr[i].getID() + " " + regCustArr[i].getFirstName() + " " + regCustArr[i].getLastName() + " " + String.format("%.2f", regCustArr[i].getSpent()) + "\n");
			fwrite.flush();
		}
		
		fwrite.close();
		
		//preferred customer file
		File txt2 = new File("preferred.dat");
		FileOutputStream fstream2 = new FileOutputStream(txt2);
		PrintWriter fwrite2 = new PrintWriter(fstream2);
		
		for(int i = 0; i < prefCustArr.length; i++) {

			if (prefCustArr[i].getStatus() == "plat") {
				fwrite2.print(prefCustArr[i].getID() + " " + prefCustArr[i].getFirstName() + " " + prefCustArr[i].getLastName() + " " + String.format("%.2f", prefCustArr[i].getSpent()) + " " + ((Platinum)prefCustArr[i]).getBucks() + "\n");
				fwrite2.flush();
			}
			else {
				fwrite2.print(prefCustArr[i].getID() + " " + prefCustArr[i].getFirstName() + " " + prefCustArr[i].getLastName() + " " + String.format("%.2f", prefCustArr[i].getSpent()) + " " + (int)(100 * ((Gold)prefCustArr[i]).getDiscount()) + "%\n");
				fwrite2.flush();
			}
		}
		
		fwrite2.close();
	}

	
	public static void main(String[] args) throws IOException {
		
		String regCustFile, prefCustFile, ordersFile;
			
		//prompt user for regular/preferred customer and orders files (preferred may or may not exist)	
		System.out.print("Please give the regular customer file: ");
		regCustFile = input.nextLine();
		regCustToArray(regCustFile);
		
		
		System.out.print("Please give the preferred customer file (hit enter if none): ");
		prefCustFile = input.nextLine();
		prefCustToArray(prefCustFile);
	
		System.out.print("Please give the orders file: ");
		ordersFile = input.nextLine();
		
		//process orders file and update customer information
		readOrders(ordersFile);

		//update customer data back into files
		report();
		
		input.close();
	}

}
