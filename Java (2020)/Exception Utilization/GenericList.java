//Kyle Chan kxc180021

import java.util.ArrayList;
//import java.util.Collections;

public class GenericList <Type extends Comparable<Type>> {

	protected ArrayList<Type> array;
	
	GenericList(){
		this.array = new ArrayList<Type>();
	}
	
	GenericList(ArrayList<Type> array){
		this.array = new ArrayList<>(array);
	}
	
	public void setList(Type item){
		array.add(item);
	}
	
	public ArrayList<Type> getList() {
		System.out.print("Array Contents: ");
		
		for (int i = 0; i < array.size(); i++) {
			System.out.print(array.get(i) + ", ");
		}
		System.out.println("");
		
		return array;
	}
	
	public void InsertionSort() {
		
		int j = 0;
		
		for(int i = 1; i < array.size(); i++) {
			j = i - 1;
			Type temp = array.get(i);
			
			while(j > -1 && array.get(j).compareTo(temp) > 0) {
				array.set(j+1, array.get(j));
				j--;
				
			}

			array.set(j+1, temp);

		}
	}
	
	public boolean BinarySearch(Type item) {
		int left = 0, right = array.size()-1;
		int middle;
		
		while(left <= right) {
			middle = (left + right)/2;
			
			if(array.get(middle).compareTo(item) == 0) {
				System.out.println("true");
				return true;
			}
			
			if(array.get(middle).compareTo(item) < 0)
				left = middle + 1;
			if(array.get(middle).compareTo(item) > 0)
				right = middle - 1;
		}
		
		System.out.println("false");
		return false;
	}
}
	
