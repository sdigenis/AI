package bfs;

import java.io.File;
import java.util.*;
public class bfs {
	
	static int width;
	static int height;
	int total = width * height;
	static int [][]lab;
	static int [][]visited;
	
	static int []xMoves = { 0, 1, 0,-1};
	static int []yMoves = {-1, 0, 1, 0};
	static Queue <Integer>fx = new LinkedList<>();
	static Queue <Integer>fy = new LinkedList<>();
	//static List <Object> final_res = new LinkedList<>();	
	
	static int counter = 2, nodes_left = 1, nodes_next = 0; 
	static boolean end = false;
	static int initialX;
	static int initialY;
	static int wave = 1;
	static int close = 1;
	static int cnt = 2;
	static int l = 2;
	
	public static void explore_neightbours(int x, int y) {
		int nextX, nextY;
		System.out.println("\tClose CLOSE=" + close + ", X=" + (y+1) + ", Y=" + (x+1) +".");
		close++;
		for(int i = 0; i < 4; i++) {
			nextX = x + xMoves[i];
			nextY = y + yMoves[i];
			
			if(i == 0) {
				System.out.print("\t\tR1. ");
			}
			if(i == 1) {
				System.out.print("\t\tR2. ");
			}
			if(i == 2) {
				System.out.print("\t\tR3. ");
			}
			if(i == 3) {
				System.out.print("\t\tR4. ");
			}
			
			if(visited[nextX][nextY] == 1) {
				if(i == 3) {
					System.out.println("X=" + (nextY+1) + ", Y=" + (nextX+1) + ". Wall.\n");
				}
				else {
					System.out.println("X=" + (nextY+1) + ", Y=" + (nextX+1) + ". Wall.");
				}
				
				continue;
			}
			if(visited[nextX][nextY] >= 2) {
				if(i == 3) {
					System.out.println("X=" + (nextY+1) + ", Y=" + (nextX+1) + ". CLOSED or OPEN.\n");
				}
				else {
					System.out.println("X=" + (nextY+1) + ", Y=" + (nextX+1) + ". CLOSED or OPEN.");
				}
				continue;
			}
			
			if(i == 3) {
				System.out.println("X=" + (nextY+1) + ", Y=" + (nextX+1) + ". Free. NEWN=" + cnt+".\n");
			}
			else {
				System.out.println("X=" + (nextY+1) + ", Y=" + (nextX+1) + ". Free. NEWN=" + cnt+".");
			}
			cnt++;
			fx.add(nextX);
			fy.add(nextY);
			
			visited[nextX][nextY] = counter;
			lab[nextY][nextX] = counter;	
			nodes_next++;
		}
		//close = 1;
	}
	
	
	public static void solve(int x, int y) throws InterruptedException {
		
		int nextX = 0, nextY = 0;
		System.out.println("PART 2. Trace");
		System.out.println("");
		
		System.out.println("WAVE 0, label L=\"2\". Initial position X= "+ (initialY+1)+ ", Y=" +(initialX +1) + ", NEWN=1\n");
		fx.add(x);
		fy.add(y);
		
		counter++;
		l++;
		while(fx.size() > 0) {
			nextX = fx.remove();
			nextY = fy.remove();
			if(fx.isEmpty()) {
				System.out.println("WAVE " + wave + " label L=\"" + l + "\"" );
				wave++;
			}
			
			if(nextX == 0 || nextY == 0 || nextX == width -1 || nextY == height -1) {
				end = true;
				break;
			}
			
			explore_neightbours(nextX, nextY);
			nodes_left--;
			if(nodes_left == 0) {
				nodes_left = nodes_next;
				nodes_next = 0;
				System.out.println("WAVE " + wave + " label L=\"" + l + "\"" );
				l++;
				wave++;
				
				counter++;
			}
			if(end) {
				//final_res.add();
				return;
			}
		}
		
	}
	
	
	public static void main(String[] args) throws Exception {
		
		File file = new File("maze.txt");
		try (Scanner scanner = new Scanner(file)) {
			width = scanner.nextInt();
			height = scanner.nextInt();
			lab = new int [width][height];
			visited = new int [width][height];
			System.out.println(width + height);
			for (int i = 0 ; i < width; i++) {
				for(int j =  0; j < height ; j++) {
					lab[i][j] = scanner.nextInt();
					visited[i][j] = lab [i][j];
					if (lab[i][j] != 0 && lab[i][j] != 1 && lab[i][j] != 2) {
						System.out.println("Invalid value on the text file.");
						throw new Exception();
					}
					if (lab[i][j] == 2) {
						initialX = i;
						initialY = j;
					}
				}
			}
		}
		System.out.println("PART 1. Data");
		System.out.println("\t1.1. Labyrinth");
		System.out.println("\t  Y, V");
		
		for(int i = 0; i < width; i++){
			System.out.print("\t" +  (width-i) + " |");
			for(int j = 0; j < height; j++){
				System.out.print("\t" + visited[i][j]);
			}
			System.out.println("");		
		}
		System.out.print("\t");
		for(int i = 0; i < width * width + 10; i++) {
			System.out.print("-");
		}
		System.out.println("> X, U");
		System.out.print("\t");
		for(int i = 0; i < height; i++) {
			System.out.print("\t" + (i+1));
		}
		System.out.println("");
		
		System.out.println("\t" + "1.2. Initial position X=" + (initialY+1) + ", Y=" + (initialX+1) +". L=2.");
		
		solve(initialX, initialY);
		
		if(end) {
			System.out.println("PART 3. Results\n");
			System.out.println("\t3.1. Path is found.\n");
			System.out.println("\t3.3. Path graphically\n");
			System.out.println("LABCOPY");	
			System.out.println("\t  Y, V");
			
			for(int i = 0; i < width; i++){
				System.out.print("\t" + (width - i) + " |");	
				for(int j = 0; j < height; j++){
					System.out.print("\t"+visited[i][j]);
				}
				System.out.println("");		
			}
			System.out.print("\t  ");
			for(int i = 0; i < width * width + 10; i++) {
				System.out.print("-");
			}
			System.out.println("> X, U");
			//System.out.println("\t3.3. Rules: ");
		}
		else {
			System.out.println("PART 3. Results\n");
			System.out.println("\t3.1. Path is not found.\n");
		}
		
	}

}
