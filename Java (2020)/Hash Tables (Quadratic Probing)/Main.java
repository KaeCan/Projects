//kxc180021 Kyle Chan

import java.util.*;

public class Main {

	static class hashTable{
		public int[] array;
		public int size, curSize;
		public double load;
		
		public hashTable(int size, double loadFactor) {
			this.size = size;
			this.curSize = 0;
			array = new int[size];
			load = loadFactor * size;
		}
		
 	}
	
	public static int quadraticProbe(hashTable table, int key) {
		
		int hash;
		int i = 0;		
		
		do{
			hash = (key + (i*i)) % table.size;
			i++;

		}while(table.array[hash] != 0);
		
		
		return hash;
	}
	
	public static int findNextPrime(int num) {
		
		int temp = num + 1;
		
		for(int i = 2; i < temp; i++) {
			
			//if number is divisible by i, repeat cycle for next number
			if(temp % i == 0) {
				temp++;
				i=2;
			}
		}
		
		return temp;
	}
	
	public static hashTable resize(hashTable table) {
		int[] tempTable = table.array;
		
		int nextPrime = findNextPrime(tempTable.length * 2);
		
		table = new hashTable(nextPrime, 0.5);
		
		for(int i = 0; i < tempTable.length; i++) {
			if(tempTable[i] != 0) {
				table = hashInsert(table, tempTable[i]);
			}
		}
				
		return table;
	}
	
	public static hashTable hashInsert(hashTable table, int key) {
		
		int hash = key % table.size;
		
		//probe for bucket
		hash = quadraticProbe(table, hash);
		
		table.array[hash] = key;
		table.curSize++;
		
		//resize if at or exceeds load
		if(table.curSize >= table.load) {
			table = resize(table);
		}
		return table;
	}
	
	public static void printTable(hashTable table) {
		for(int i = 0; i < table.size; i++) {
			if(table.array[i] == 0) 
				System.out.print("_");
			else
				System.out.print(table.array[i]);
			
			System.out.print(" ");
		}
		System.out.println("");
	}
	
	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		
		//create hashTable (size 11 initally)
		hashTable table = new hashTable(11, 0.5);
		
		System.out.println("how many numbers are you putting in? ");
		
		int entries = input.nextInt();
		
		System.out.println("enter all numbers");
		
		input.nextLine();
		int user;
		
		for(int i = 0; i < entries; i++) {
			user = input.nextInt();
			System.out.println(user);
			table = hashInsert(table, user);
		}
		
		
		printTable(table);
		
		input.close();
	}

}
