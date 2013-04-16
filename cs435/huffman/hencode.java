/* Marlon. Brillantes PA_3_4421 hencode.java */


import java.io.*;
import java.util.*;

public class hencode {

	static huffNode root;

static class huffNode {
	
	char c;
	int freq;
	huffNode left;	
	huffNode right;
	
	public huffNode(char c) {
		this.c = c;
		freq=0;
		left = null;
		right = null;
	}
	
	public String toString() {
		return "(" + c + ", " + freq + ", " +  "LEFT: " + left + ", " + "RIGHT: " + right + ")";
	}
}	
	
	
public static void checkTree(huffNode root)
{
if (root.left == null && root.right == null){
System.out.println(root);
return;
}
checkTree(root.left);
checkTree(root.right);

}
	
/*********************** BUILD THE TREE ****************/
public static void buildTree(ArrayList<huffNode> lst){
	
	int min;
	
	while (lst.size() != 1){
		//System.out.println("SIZE: " + lst.size());
		//get left min
		min=0;
		for (int i=1; i < lst.size(); i++ ){	
			if (lst.get(i).freq < lst.get(min).freq) {
				min = i;
			}		
		}
		huffNode ltemp=lst.remove(min);
		
		//get right min
		min=0;
		for (int i=1; i < lst.size(); i++ ){	
			if (lst.get(i).freq < lst.get(min).freq) {
				min = i;
				
			}		
		}
		huffNode rtemp = lst.remove(min);
		
		huffNode temp = new huffNode('z');
		temp.left = ltemp;
		temp.right= rtemp;
		//System.out.println("LEFT FREQ: " + ltemp.freq);
		//System.out.println("RIGHT FREQ: " + rtemp.freq);
		temp.freq = (ltemp.freq + rtemp.freq);
		//System.out.println(temp.freq);
		lst.add(temp);
	}
root = lst.remove(0);
//checkTree(root);
//System.out.println(root);
}


/*************** CREATE THE CODE ***************/
public static void createCode(huffNode root, ArrayList<String> codeArr, 
								ArrayList<Character> letterArr, String strCode)
{
	if (root.left == null && root.right == null){
		codeArr.add(strCode);
		letterArr.add(root.c);
		return;
	}
	createCode(root.left, codeArr, letterArr, strCode+0);
	createCode(root.right, codeArr, letterArr, strCode+1);
	
}

/************** OUTPUT TEXT FILE 
 * @throws IOException *********/
public static void encode(String textFile, ArrayList<String> codeArr, 
		ArrayList<Character> letterArr, ArrayList<huffNode> sendList) throws IOException {
	
	
	BufferedWriter codes = new BufferedWriter(new FileWriter(textFile + ".huf"));
	
	codes.write(Integer.toString(sendList.size()));
	codes.newLine();
	for(int j = 0; j < sendList.size(); j++) { 
		String tempFreq = Integer.toString(sendList.get(j).freq);
		codes.write(sendList.get(j).c + tempFreq);
		codes.newLine();
	}
	codes.close();
	
	
	FileInputStream fistream = new FileInputStream(textFile);
	DataInputStream datain = new DataInputStream(fistream);
	BufferedReader br = new BufferedReader(new InputStreamReader(datain));

	String sLine;
	String code;
	int index;
	//ArrayList<huffNode> hnList = new ArrayList<huffNode>();
	
	//get line, then read each character in line
	BufferedWriter out = new BufferedWriter(new FileWriter(textFile + ".huf", true));
	out.write('"');
	while ((sLine = br.readLine()) != null)   {
	  
		String s = sLine;
		for(int i = 0; i < s.length(); i++)
		{
		   
			char c = s.charAt(i);
			index = letterArr.indexOf(c);
			code = codeArr.get(index);
			
      out.write(code);
            
			
		}
	
	}
	out.close();
	
}


	
public static void main(String[] args) throws IOException{
	
	
	FileInputStream fstream = new FileInputStream(args[0]);
	// DataInputStream datain = new DataInputStream(fistream);
	// BufferedReader br = new BufferedReader(new InputStreamReader(datain));
	DataInputStream datain = new DataInputStream(fstream);
	BufferedReader br = new BufferedReader(new InputStreamReader(datain));

	String sLine;
	ArrayList<huffNode> hnList = new ArrayList<huffNode>();
	
	
	//get line, then read each character in line
	while ((sLine = br.readLine()) != null)   {
	  
		String s = sLine;
		for(int i = 0; i <= s.length(); i++)
		{
			char c = s.charAt(i);

			if(i == s.length()){
				huffNode newhn = new huffNode("\n");
			} else{
				huffNode newhn = new huffNode(c);
				newhn.freq++;
			}
				
			
					
			//add first node
			if (hnList.size() == 0){
				hnList.add(newhn);
				continue;
			}
			
			//check if letter is in array list and ++ freq if yes
			int addit=0;
			for(int x = 0; x < hnList.size(); x++) {  				
			    if (hnList.get(x).c == c) {
			    	hnList.get(x).freq++;
			    	addit++;
			    	break;
			    }
			}
			
			//if node not in the list, add it
			if (addit==0){
				hnList.add(newhn);
			}
			addit=0;
			
		}
		

	}
	datain.close();	
	
	
	/*********** write this list to file *********************/
	ArrayList<huffNode> sendList = new ArrayList<huffNode>(hnList.size());
	
	/*******CODE ARRAYS********/
	ArrayList<String> code = new ArrayList<String>(hnList.size());
	ArrayList<Character> letter = new ArrayList<Character>(hnList.size());
	/*******CODE ARRAYS********/
	
	//print and copy
	for(int j = 0; j < hnList.size(); j++) { 	   
		sendList.add(hnList.get(j));
		//System.out.println(hnList.get(j));
	}
	
	//build tree
	buildTree(hnList);
	
	//empty string to pass to create the code
	String str="";
	
	//create the code for each letter
	createCode(root, code, letter, str);
	
	//read the file again and output onto text file
	encode(args[0], code, letter, sendList);
	
	for(int j = 0; j < letter.size(); j++) { 	   
		//sendList.add(hnList.get(j));
		//System.out.println(letter.get(j) + " = " + code.get(j));
		
	}
	
	
	

}
}


