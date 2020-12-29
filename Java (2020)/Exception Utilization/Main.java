//Kyle Chan kxc180021

import java.util.*;
import java.lang.Math;

public class Main {

	public static int bin2Dec(String binary) throws BinaryFormatException {
		int decimal = -1;
		
		try {

			if(!binary.isEmpty()) {
				int temp;
				
				for(int i = 0; i < binary.length(); i++) {	
					
					temp = Character.getNumericValue(binary.charAt(i));
					
					if(temp == 0 || temp == 1)
						continue;
					else
						throw new Exception();
				}
				
				decimal = 0;
				int digit;
				double exp;
				int j = 0;
				
				for(int i = binary.length()-1; i >= 0; i--) {
					
					digit = Character.getNumericValue(binary.charAt(i));
					
					if(i == binary.length()-1) {
						exp = 1;
						decimal += digit * exp;
					}
						
					else {
						exp = Math.pow(2, j);
						decimal += digit * exp;
					}
					
					j++;
					
				}
			}
			else
				return decimal;
				
			
		}
		catch (Exception err) {
			throw new BinaryFormatException("Not a valid binary!");
		}
		return decimal;
	}
	
	public static void main(String[] args) throws BinaryFormatException{
		
		Scanner input = new Scanner(System.in);
		String binInput;
		int dec;
		
		System.out.print("Enter a binary: ");
		binInput = input.nextLine();
		
		dec = bin2Dec(binInput);
		if(dec != -1)
			System.out.println("Converted to decimal: " + dec);
		else
			System.out.println("No string was given..");
		
		ArrayList<Integer> ints = new ArrayList<Integer>();
		ints.add(4);
		ints.add(3);
		ints.add(2);
		GenericList<Integer> intList = new GenericList<>(ints);
		
		ArrayList<String> strs = new ArrayList<String>();
		strs.add("lmfao");
		strs.add("applez");
		strs.add("zeze");
		GenericList<String> strList = new GenericList<>(strs);
		
		ArrayList<Double> dubs = new ArrayList<>();
		dubs.add(12.3);
		dubs.add(9.5);
		dubs.add(34.0);
		GenericList<Double> doubleList = new GenericList<>(dubs);
		
//		System.out.println("\nBefore:");
		
		intList.getList();
		strList.getList();
		doubleList.getList();
		
//		System.out.println("\nAfter:");
		
		intList.InsertionSort();
		strList.InsertionSort();
		doubleList.InsertionSort();
		
		intList.getList();
		strList.getList();
		doubleList.getList();
		
		//searching for certain values in each object
		intList.BinarySearch(3);
		intList.BinarySearch(5);
		
		strList.BinarySearch("lmfao");
		strList.BinarySearch("bruh");
		
		doubleList.BinarySearch((double)34);
		doubleList.BinarySearch((double)12.7);
		
		
		
		input.close();
	}

}
