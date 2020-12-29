//kxc180021 Kyle Chan

import java.util.*;
import java.io.*;

public class Main {
	
	static Scanner input = new Scanner(System.in);

	public static BSTree<DVD> getInventory(String filename, BSTree<DVD> invTree) throws IOException{
		
		Scanner fread = new Scanner(new FileInputStream(filename));
		String lineText;
		
		int quantityAvail;
		int quantityRented;
		
		String temp;

		
		while(fread.hasNextLine()) {
			if(fread.hasNext()) {
				
				//get line in file
				lineText = fread.nextLine();
				
				//split line entries
				String[] lineInv = lineText.split(",");
				temp = "";
				
				//remove "" around movie title
				for(int i = 0; i < lineInv[0].length(); i++) {
					if(lineInv[0].charAt(i) != '\"') {
						temp += lineInv[0].charAt(i);
					}
				}
				
				quantityAvail = Integer.parseInt(lineInv[1]);
				quantityRented = Integer.parseInt(lineInv[2]);
				
				//insert data from line into tree
				invTree.insert(new DVD(temp, quantityAvail, quantityRented));
				
			}
		}
		
		fread.close();
		return invTree;
	}
	
	public static void writeError(PrintWriter errLog,String operand, String restOfStuff) {
		errLog.write(operand + " ");
		errLog.flush();
		
		errLog.write(restOfStuff);
		errLog.flush();
		
		errLog.write("\n");
		errLog.flush();
	}
		
	
	public static boolean validAdd(String[] lineOrder) {
		
		boolean flag = true;
		//valid # of args (2)
		if(lineOrder.length == 2) {
			
			//second entry are only digits
			for(int i = 0; i < lineOrder[1].length(); i++) {
				if(!Character.isDigit(lineOrder[1].charAt(i))) {
					flag = false;
					break;
				}
			}
			
			//# to add < 0
			if(flag == true && Integer.parseInt(lineOrder[1]) <= 0)
				flag = false;
				
		}
		else
			flag = false;
		
		return flag;
	}
	
	public static boolean validRemove(String[] lineOrder, Node<DVD> curNode) {
		boolean flag = true;

		//valid # of args (2)
		if(lineOrder.length == 2) {
			
			//second entry are only digits
			for(int i = 0; i < lineOrder[1].length(); i++) {
				if(!Character.isDigit(lineOrder[1].charAt(i))) {
					flag = false;
					break;
				}
			}
			
			//# to remove <= 0 OR # to remove > # available to be removed  
			if(flag == true && (Integer.parseInt(lineOrder[1]) <= 0 || Integer.parseInt(lineOrder[1]) > curNode.getPayload().getAvail()))
				flag = false;		
		}
		
		else
			flag = false;

		return flag;
	}
	
	public static boolean validRent(String[] lineOrder, Node<DVD> curNode) {
		boolean flag = true;
		
		//valid # of args (1)
		if(lineOrder.length == 1) {

			//check if there are any available to rent out
			if(curNode.getPayload().getAvail() == 0)
				flag = false;
		}
		else
			flag = false;
		
		return flag;
	}
	
	public static boolean validReturn(String[] lineOrder, Node<DVD> curNode) {
		boolean flag = true;
		
		//valid # of args (1)
		if(lineOrder.length == 1) {
			
			//check if there are any available to return
			if(curNode.getPayload().getRented() == 0)
				flag = false;
		}
		else
			flag = false;
		
		return flag;
	}
	
	public static void transactions(String filename, BSTree<DVD> invTree) throws IOException {
		
		Scanner fread = new Scanner(new FileInputStream(filename));
		String lineText;
		
		String operand;
		String title;
		
		PrintWriter errLog = new PrintWriter(new FileOutputStream(new File("error.log")));
				
		while(fread.hasNextLine()) {
			if(fread.hasNext()) {
				
				operand = fread.next(); 
				lineText = fread.nextLine();
				String[] lineOrder = lineText.split(",");
				
				title = "";
				
				for(int i = 1; i < lineOrder[0].length()-1; i++) {
					if(lineOrder[0].charAt(i) != '\"') {
						title += lineOrder[0].charAt(i);
					}
				}
									
				
				//process transaction log
				DVD temp = new DVD(title, 0, 0);
				
				Node<DVD> curNode = new Node<DVD>(); //search for and return pointer to title in inventory

				
				switch(operand) {
				
					case "add":
						
						//check for valid transaction (order length, digits only, above zero)
						if(validAdd(lineOrder)) {
						
							curNode = invTree.search(temp); //search for and return pointer to title in inventory
							
							if(curNode != null) //there is an existing node with the movie title
								curNode.getPayload().changeAvail(Integer.parseInt(lineOrder[1])); //increment existing titles available
							
							else //title needs new node				
								invTree.insert(new DVD(title, Integer.parseInt(lineOrder[1]), 0)); //create new node with # available
						}
						else
							writeError(errLog, operand, lineText);
						
						break;
						
					case "remove":					
						
						curNode = invTree.search(temp);
						
						if(curNode != null) {
						
							//checks for order length, digits only, above zero, removal # < available #
							if(validRemove(lineOrder, curNode)) {
							
								curNode.getPayload().changeAvail(-(Integer.parseInt(lineOrder[1])));
									
								//if there is no more available or rented out of a movie, delete from tree
								if(curNode.getPayload().getAvail() == 0 && curNode.getPayload().getRented() == 0)
									invTree.remove(curNode.getPayload());
										
							}
							else
								writeError(errLog, operand, lineText);
						}
						else
							writeError(errLog, operand, lineText);

						break;					
						
					case "rent":
											
						curNode = invTree.search(temp); //search for and return pointer to title in inventory
						
						if(curNode != null) {
							
							//checks for order length, available # > 0
							if(validRent(lineOrder, curNode)) {
								curNode.getPayload().changeAvail(-1); //decrement quantity available
								curNode.getPayload().changeRented(1); //increment quantity rented
							}
							else
								writeError(errLog, operand, lineText);
						}
						else
							writeError(errLog, operand, lineText);
	
						break;
						
					case "return":
											
						curNode = invTree.search(temp); //search for and return pointer to title in inventory
						
						if(curNode != null) {
							
							//checks for order length, rented out # > 0
							if(validReturn(lineOrder, curNode)) {
								curNode.getPayload().changeAvail(1); //increment quantity available
								curNode.getPayload().changeRented(-1); //decrement quantity rented
							}
							else
								writeError(errLog, operand, lineText);
						}
						else
							writeError(errLog, operand, lineText);
	
						break;
						
					default: //write invalid transaction to error.log
						writeError(errLog, operand, lineText);
			
				}
				
			}
		}
		
		errLog.close();
	}
	
	public static void report(Node<DVD> root) {
		
		if(root != null) {
			report(root.getLeft()); 
			
			//print title
			System.out.print(root.getPayload().getTitle());
		
			//allocate space for data columns
			int tabAmt = 4 - (root.getPayload().getTitle().length() / 8);
			
			for(int i = tabAmt; i > 0; i--) {
				System.out.print("\t");
			}
			
			//print available and rented into columns
			System.out.println(root.getPayload().getAvail() + "\t" + root.getPayload().getRented());		
			
			report(root.getRight());
		
		}
		
	}
	
	public static void main(String[] args) throws IOException{
		
		BSTree<DVD> invTree = new BSTree<DVD>();
		
		String invFile;
		String transFile;
		
		//prompt user for files
		do {
			try {
				//get inventory file and binary tree
				System.out.print("Enter valid inventory data: ");
				invFile = input.nextLine();
				invTree = getInventory(invFile, invTree);
				break;
			}
			catch(IOException err) {
				System.out.println("Error: not a valid file input.");
			}
		}while(true);
		
		do {
			try {
				//get transaction log file
				System.out.print("Enter a valid transaction log: ");
				transFile = input.nextLine();
				transactions(transFile, invTree);
				break;
			}
			catch(IOException err) {
				System.out.println("Error: not a valid file input.");
			}
		}while(true);

		//display movie titles alphabetically
		report(invTree.getRoot());
	}

}
