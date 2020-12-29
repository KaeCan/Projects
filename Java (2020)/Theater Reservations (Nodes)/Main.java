//kxc180021 Kyle Chan

import java.util.*;
import java.io.*;

public class Main {

	static Scanner input = new Scanner(System.in);
	static int ROWS = 0;
	static int COLS = 0;
	
	public static Auditorium getAuditorium(String filename, Auditorium auditorium) throws IOException{
		
		Scanner fread = new Scanner(new FileInputStream(filename));
		String lineText[] = new String[20];
		
		
		while(fread.hasNextLine()) {
			if(fread.hasNext()) {
				lineText[ROWS] = fread.nextLine();
	        	ROWS++;											//obtain row count for auditorium
			}
		}
		
		COLS = lineText[0].length();							//obtain column count for auditorium
		
		//convert auditorium file into a 2D array, which will be tossed after it is used in the node grid creation
		char[][] audArray = new char[ROWS][COLS];
		for(int i = 0; i < ROWS; i++) {
			for(int j = 0; j < COLS; j++) {
				audArray[i][j] = lineText[i].charAt(j);
			}
		}
		
		//append seats from array
		auditorium.head = auditorium.appendSeats(audArray, ROWS, COLS, 0, 0, null);
		
		return auditorium;	

	}
	
	public static void displayAuditorium(Auditorium auditorium) {
		
		Node<Seat> curNode;
		
		Node<Seat> firstSeat = auditorium.head; //placeholder for beginning of each row
		
		System.out.print("   ");
		
		for(int i = 0; i < COLS; i++) {
			System.out.print((char)(i+65));
		}
		
		System.out.println("");
		
		int currRow = 1;
		
		while(firstSeat != null) {
			System.out.print(currRow + "| ");
			
			curNode = firstSeat;
			while(curNode != null) {
				if(auditorium.getSeatStatus(curNode) == '.')	
					System.out.print(".");
				else
					System.out.print("#");
				
				curNode = curNode.getRight();
			}
			System.out.println("");
			
			firstSeat = firstSeat.getDown();
			currRow++;
		}
		
	}
	
	public static boolean checkSeats(Auditorium auditorium, int startRow, char startSeat, int totalTickets) {
		
		int firstSeat = startSeat - 64;
		int endSeat = firstSeat + totalTickets - 1;
		Node<Seat> curNode = auditorium.head;
		
		//traverse to current row
		for(int i = 1; i < startRow; i++)
			curNode = curNode.getDown();
	
		//traverse seats in row
		for(int i = 1; i <= endSeat; i++) {
			//only start checking once first requested seat is hit
			if(i >= firstSeat) {
				if(curNode.getPayload().getTicket() != '.')
					return false;
			}
			curNode = curNode.getRight();
		}
		
		return true;
		
	}
	
	public static void reserveSeats(int startRow, char startSeat, int aTickets, int cTickets, int sTickets, int totalTickets, Auditorium auditorium, boolean altFlag) {
		char user = 'y';
		int firstSeat = startSeat - 64;
		int endSeat = firstSeat + totalTickets - 1;
		
		if(altFlag) {
			do{
				System.out.print("Would you like to reserve these seats? (Y|N|y|n) ");
				user = input.next().charAt(0);
			
				if(user == 'Y' || user == 'y' || user == 'N' || user == 'n')
					break;

			} while(true);
		}
		
		if(user == 'Y' || user == 'y') {
			Node<Seat> curNode = auditorium.head;
			
			for(int i = 1; i < startRow; i++) {
				curNode = curNode.getDown();
			}
			
			for(int i = 1; i <= endSeat; i++) {
				if(i >= firstSeat) {
					if(aTickets > 0) {
						curNode.getPayload().setTicket('A');
						aTickets--;
					}
					else if(cTickets > 0) {
						curNode.getPayload().setTicket('C');
						cTickets--;
					}
					else if(sTickets > 0) {
						curNode.getPayload().setTicket('S');
						sTickets--;
					}
				}
				curNode = curNode.getRight();
			}
			
			System.out.println("Successfully reserved seats.");
		}
	}
	
	public static Node<Seat> bestAlternative(int startRow, int totalSeats, Auditorium auditorium) {
		double distance = 100.0;
		double formula = 0.0;
		int smallestRow = ROWS;
		int smallestCol = COLS;
		
		Node<Seat> bestSeats = null;
		Node<Seat> firstSeat = auditorium.head; //placeholder for first seat of each row
		Node<Seat> seatStart = auditorium.head; //placeholder for starting seat 
		Node<Seat> curNode = auditorium.head; //current seat that's being evaluated
		
		//FOR EACH ROW
		for(int i = 0; i < ROWS; i++) {
			
			seatStart = firstSeat; //starting seat returns to beginning of each row
			
			//FOR EACH COLUMN
			for(int j = 0; j < COLS - totalSeats + 1; j++) {
				
				curNode = seatStart; //current seat returns to beginning of selected seats
				
				//FOR EACH SEAT (in arrangement)
				for(int k = 1; k <= totalSeats; k++) {
					
					if(curNode.getPayload().getTicket() != '.')
						break;
					
					//all seats are open
					if(k == totalSeats) {
						
						//find "sides" of a right triangle to get hypotenuse/distance to center
						
						//side 1 -> [seatOffset + centerOfSeats - centerOfAuditoriumCols] (width)
						//side 2 -> [rowOffset  - centerOfAuditoriumRows] (height)
						
						int halfRows = (int)(ROWS/2 + 0.5);
						int halfCols = (int)(COLS/2 + 0.5);

						double side1sq = Math.pow(((double)j + (totalSeats+1)/2) - halfCols,2);
						double side2sq = Math.pow((i - halfRows), 2);
						
						formula = Math.sqrt(side1sq + side2sq);
						
						//if there is a tie/smaller, newer distance
						if(formula <= distance) {
							
							//there is a tie for distance
							if(formula == distance) {
								
								//there is a tie for/new row closest to center
								if(Math.abs(i - halfRows) <= Math.abs(smallestRow -  halfRows)) {
									
									//new row is closer
									if(Math.abs(i - halfRows) < Math.abs(smallestRow -  halfRows)) {
										bestSeats = seatStart;
										smallestRow = i;
										smallestCol = j;

									}
									//rows are equally distant
									else {
										//keep arrangement with smaller seat
										if(smallestRow > i) {
											bestSeats = seatStart;
											smallestRow = i;
											smallestCol = j;

										}
									}
									
								}
								
							}
							//no tie; new distance is smaller
							else {
								bestSeats = seatStart;
								smallestRow = i;
								smallestCol = j;
								distance = formula;
							}
							
//							System.out.println("smallest row/col: " + smallestRow + ", " + smallestCol);
						}
					}
						curNode = curNode.getRight(); //traverse to next seat
				}
				
				seatStart = seatStart.getRight(); //traverse to next starting seat
			}
			
			firstSeat = firstSeat.getDown(); //traverse to next row
		}
		
		return bestSeats;
		
	}
	
	public static void requestSeats(Auditorium auditorium) throws InputMismatchException{
		int totalSeats = 0, aTickets, cTickets, sTickets;
		int startRow;
		char startSeat;
		
		//get seating arrangement with input validation
		do {
			try {
				System.out.print("Type your starting row: ");
				startRow = input.nextInt();
				
				if(startRow >= 1 && startRow <= ROWS)
					break;
				else
					throw new InputMismatchException();
				
			}
			catch (InputMismatchException err) {
				System.out.println("Invalid entry, please try again.");
				if(input.hasNextLine()) //clear scanner buffer
					input.nextLine();
			}
		}while(true);
		
		do {
			try {
				System.out.print("Type your start seat: ");
				startSeat = Character.toUpperCase(input.next().charAt(0));
				
				if(startSeat >= 65 && startSeat <= COLS+64)
					break;
				else
					throw new InputMismatchException();
			}
			catch (InputMismatchException err) {
				System.out.println("Invalid entry, please try again.");
				if(input.hasNextLine()) //clear scanner buffer
					input.nextLine();
			}
		}while(true);
		
		do {
			try {
				System.out.print("Adult tickets: ");
				aTickets = input.nextInt();
				
				if(aTickets >= 0) {
					totalSeats += aTickets;
					break;
				}
				else
					throw new InputMismatchException();
			}
			catch (InputMismatchException err) {
				System.out.println("Invalid entry, please try again.");
				if(input.hasNextLine()) //clear scanner buffer
					input.nextLine();
			}
		}while(true);
		
		do {
			try {
				System.out.print("Child tickets: ");
				cTickets = input.nextInt();
				
				if(cTickets >= 0) {
					totalSeats += cTickets;
					break;
				}
				else
					throw new InputMismatchException();
			}
			catch (InputMismatchException err) {
				System.out.println("Invalid entry, please try again.");
				if(input.hasNextLine()) //clear scanner buffer
					input.nextLine();
			}
		}while(true);
		
		do {
			try {
				System.out.print("Senior tickets: ");
				sTickets = input.nextInt();
				
				if(sTickets >= 0) {
					totalSeats += sTickets;
					break;
				}
				else
					throw new InputMismatchException();
			}
			catch (InputMismatchException err) {
				System.out.println("Invalid entry, please try again.");
				if(input.hasNextLine()) //clear scanner buffer
					input.nextLine();
			}
		}while(true);
		
		//calculate start-end seats
		String selectBeg = Integer.toString(startRow) + Character.toString(startSeat);
		String selectEnd = Integer.toString(startRow) + (char)(selectBeg.charAt(1) + totalSeats - 1);
		
		//print out start-end seats
		System.out.println("Seat(s) requested: " + selectBeg + " - " + selectEnd);
		
		//check for availability
		if(checkSeats(auditorium, startRow, startSeat, totalSeats)) {
			reserveSeats(startRow, startSeat, aTickets, cTickets, sTickets, totalSeats, auditorium, false);
		}	
		//no availability -> best alternative seats
		else {
			//check for alternative seating
			Node<Seat> bestSeats = bestAlternative(startRow, totalSeats, auditorium);
			if(bestSeats != null) {
				
				//calculate new start-end seats
				selectBeg = Integer.toString(bestSeats.getPayload().row) + Character.toString(bestSeats.getPayload().seat);
				selectEnd = Integer.toString(bestSeats.getPayload().row) + (char)(selectBeg.charAt(1) + totalSeats - 1);
				
				//print out new start-end seats
				System.out.println("seats not available");
				System.out.println("Alternative seat(s) have been found: " + selectBeg + " - " + selectEnd);
				
				//go to reserve seats, alternative seating flag is raised
				reserveSeats(bestSeats.getPayload().row, bestSeats.getPayload().seat, aTickets, cTickets, sTickets, totalSeats, auditorium, true);
			}
			//no alternative seats - > return to main menu
			else {
				System.out.println("No other seating alternatives can be found in this auditorium.");
			}
		}
		
		
	}
	
	public static void report(Auditorium auditorium) throws IOException {
		
		int totalSeats = ROWS * COLS, totalTickets = 0, aTickets = 0, cTickets = 0, sTickets = 0;
		double totalSales = 0.0;
		
		char status;
		
		File txt = new File("A1.txt");
		FileOutputStream filestream = new FileOutputStream(txt);
		PrintWriter A1 = new PrintWriter(filestream);
		
		Node<Seat> curNode;
		
		Node<Seat> firstSeat = auditorium.head; //placeholder for beginning of each row
		
		//write new auditorium node grid into output file
		while(firstSeat != null) {
			
			curNode = firstSeat;

			while(curNode != null) {
				
				status = curNode.getPayload().getTicket();
				
				switch(status) {
					case '.':
						A1.print(".");
						A1.flush();
						break;
					case 'A':
						A1.print("A");
						A1.flush();
						aTickets++;
						totalTickets++;
						break;
					case 'C':
						A1.print("C");
						A1.flush();
						cTickets++;
						totalTickets++;
						break;
					case 'S':
						A1.print("S");
						A1.flush();
						sTickets++;
						totalTickets++;
						break;
				}
				
				curNode = curNode.getRight();
			}
			A1.print("\n");
			A1.flush();
			firstSeat = firstSeat.getDown();
			
		}
		
		//write sales to console
		totalSales = (aTickets * 10) + (cTickets * 5) + ((double)sTickets * 7.5);
		
		System.out.println("Total Seats: " + totalSeats);
		System.out.println("Total Tickets: " + totalTickets);
		System.out.println("Adult Tickets: " + aTickets);
		System.out.println("Child Tickets: " + cTickets);
		System.out.println("Senior Tickets: " + sTickets);
		System.out.print("Total Sales: $");
		System.out.println(String.format("%.2f", totalSales));
		
		A1.close();
	}
	
	public static void main(String[] args) throws IOException, InputMismatchException {
		
		Auditorium auditorium = new Auditorium();
		boolean exit = false;
		//get auditorium file			
		String audFile;
		boolean valid;

		do {
			try {
				System.out.print("Please give a valid auditorium file: ");
				audFile = input.nextLine();
				auditorium = getAuditorium(audFile, auditorium);

				valid = true;
			}
			catch(IOException err) {
				System.out.println("Error: not a valid file input.");
				valid = false;
			}
		}while(!valid);
		
		//main menu
		int user;
		do{
			try {
				displayAuditorium(auditorium);
				
				System.out.print("Main Menu: \n1. Reserve Seats\n2. Exit\n");
				user = input.nextInt();
				
				if(user == 1)
					requestSeats(auditorium);
				
				else if (user == 2)
					exit = true;
				else
					throw new InputMismatchException();
			}
			catch (InputMismatchException err) {
				System.out.println("Invalid entry, please try again.");
				if(input.hasNextLine()) //clear scanner buffer
					input.nextLine();
			}
			
		}while(!exit);
		
		report(auditorium);
		
		input.close();
	}

}
