/* Marlon. Brillantes PA_3_4421 hdecode.java */


import java.io.*;
import java.util.*;

public class hdecode {

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
		ArrayList<Character> letterArr) throws IOException {
	
	
	BufferedWriter codes = new BufferedWriter(new FileWriter(textFile));
	
	codes.write(Integer.toString(codeArr.size()));
	codes.newLine();
	for(int j = 0; j < codeArr.size(); j++) { 	   
		codes.write(letterArr.get(j) + ":" + codeArr.get(j));
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
	while ((sLine = br.readLine()) != null)   {
	  
		String s = sLine;
		for(int i = 0; i < s.length(); i++)
		{
		   
			char c = s.charAt(i);
			index = letterArr.indexOf(c);
			code = codeArr.get(index);
			BufferedWriter out = new BufferedWriter(new FileWriter(textFile, true));
            
			

                out.write(code);
                out.close();
            
			
		}
	
	}
	
}


	
public static void main(String[] args) throws IOException{
	
	//String compressed = "C:/Users/marl/Desktop/workspace/435hw/filetest.txt.huf";
	//String uncompressed = compressed.substring(0,compressed.length()-4);
	//System.out.println(uncompressed);
	String fileName = args[0];
	File f1 = new File(fileName);
	File f2 = new File(fileName.substring(0, fileName.length()-4));
	boolean changed = f1.renameTo(f2);
	if (changed){
	
		FileInputStream fistream = new FileInputStream(fileName.substring(0, fileName.length()-4));
		DataInputStream datain = new DataInputStream(fistream);
		BufferedReader br = new BufferedReader(new InputStreamReader(datain));
	
		String sLine;
		ArrayList<huffNode> hnList = new ArrayList<huffNode>();
		
		//read first line - number of nodes
		int nodeCount = Integer.parseInt(br.readLine());
		
		//create the nodes and add them to huffNode array_list
		for (int z=0; z < nodeCount ; z++) {
			sLine = br.readLine();
			//System.out.println(sLine);
			//String delims = "[:]";
			//String[] tokens = sLine.split(delims);
			String sub = sLine.substring(0,1);
			char nodeChar = sub.charAt(0);
			int nodeFreq = Integer.parseInt(sLine.substring(1));
			//System.out.println(nodeChar + " " + nodeFreq);
			huffNode hnode = new huffNode(nodeChar);
			hnode.freq = nodeFreq;
			//System.out.println(hnode);
			hnList.add(hnode);
		}
			
		buildTree(hnList);
			
		//get line, then read each character in line
		huffNode pointer = root;
		
		char ch1='0';
		char ch2='1';
		char c;//g=0;
		BufferedWriter decode = new BufferedWriter(new FileWriter(fileName.substring(0, fileName.length()-4)));
		while ((sLine = br.readLine()) != null)   {
		  
			String s = sLine;
			//System.out.println(s);
			
			for(int i = 0; i < s.length(); i++)
			{
				
				c = s.charAt(i);
				//System.out.println();
				//System.out.print(c);
				if (pointer.left != null) {
					
					if (c == ch1) { //0 - left
						//System.out.println(c + " here");
						pointer = pointer.left;
						//System.out.println(pointer);
					
					} else if (c == ch2) { //1 - right
						//System.out.println(c + " there");
						pointer = pointer.right;
					}
				
				} else {
					
					//System.out.print(pointer.c);// + " " + pointer.freq);
					decode.write(pointer.c);
					
					pointer = root;
					i--;
				}
				
			}
			decode.write("\n");
		}decode.close();
	
	
	
	
	}
		
		

}//end main

}
