//File: SierpinkskiTriangle.java
//Description: Chapter 9 Stuff
//Programmer: Jeffrey Glenn
//Date: 10/19/13
//Chapter 9 
//I decided to do one program that demonstrated several parts of the chapter.
//I took a sample program and drew a sierpinkski triangle in it.  You can
//control the divisions with the divide button and show my name and address with
//the other.  So this shows the use of a closing window handler buttons and
//button handlers.  I also use a frame and a JPanel extended in this class and
//draw into it.  So I am putting this program in all of the chapter 9 assignments
//as I feed that I have met all of those requirements with different parts of this
//program.

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.PathIterator;
import java.util.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class SierpinskiTriangle extends JPanel implements ActionListener{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public ArrayList<Node> nodes;
	
	public static SierpinskiTriangle tri;
	
	public boolean showName;
	
	public JButton name;
	public JButton divide;
	
	public String fullname = "Jeffrey Glenn";
	public String address = "123 Fake St";

	public static void main(String[] args) {
		tri = new SierpinskiTriangle();
		
		JFrame frame = new JFrame();
		frame.setSize(1020, 840);
		frame.setVisible(true);
		frame.addWindowListener(new WinHandler());
		
		frame.add(tri);
	}
	
	public SierpinskiTriangle() {
		super();
		
		setSize(1000, 800);
		setVisible(true);
		int[] xCoords = {this.getWidth() / 2, this.getWidth(), 0};
		int[] yCoords = {0, this.getHeight(), this.getHeight()};
		
		nodes = new ArrayList<Node>();
		nodes.add(new Node(xCoords, yCoords));
		
		name = new JButton("Display Name");
		add(name);
		name.setMnemonic('N');
		name.setToolTipText("Show the name and address of the programmer");
		name.setLocation(20, 100);
		name.addActionListener(this);
		
		divide = new JButton("Divide Triangle");
		add(divide);
		divide.setMnemonic('D');
		divide.setToolTipText("Divide the triangle");
		divide.setLocation(this.getWidth() - (divide.getWidth() + 10), 20);
		divide.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == name) {
			showName = !showName;
		}

		if (e.getSource() == divide) {
			divide();
		}
		
		this.repaint();
	}
	
	public void divide() {
		ArrayList<Node> array = new ArrayList<Node>();
		
		for (Node n : nodes) {
			array.addAll(n.divide());
		}
		
		nodes.clear();
		nodes.addAll(array);
		
		
	}
	
	public void paintComponent(Graphics g) {
		g.clearRect(0, 0, getWidth(), getHeight());
		if (showName) {
			g.drawString(fullname, 20, 20);
			g.drawString(address, 20, 40);
		}
		
		for (Node n : nodes) {
			n.draw(g);
		}
	}
	
	public void dealloc() {
		nodes.clear();
	}
	
	public static class WinHandler extends WindowAdapter {
		public void windowClosing(WindowEvent e) {
			tri.dealloc();
			System.exit(0);
		}
	}

	public class Node {
		public int[] xCoords;
		public int[] yCoords;
		
		int sides = 3;

		public Color color;
		
		public Node(int[] xCoords, int[] yCoords) {
			this.xCoords = new int[sides];
			this.yCoords = new int[sides];

			for (int i = 0; i < xCoords.length; i++) {
				this.xCoords[i] = xCoords[i];
				this.yCoords[i] = yCoords[i];
			}

			color = new Color((float) Math.random(), (float) Math.random(), (float) Math.random());
		}
		
		public void draw(Graphics g) {
			g.setColor(color);
			g.fillPolygon(xCoords, yCoords, sides);
		}
		
		public ArrayList<Node> divide() {
			ArrayList<Node> ret = new ArrayList<Node>();
			double[] xm = new double[sides];
			double[] ym = new double[sides];
			
			for (int i = 0; i < 3; i++) {
				xm[i] = (double) (xCoords[i] + xCoords[i == sides - 1 ? 0 : i + 1]) / 2.0; 
				ym[i] = (double) (yCoords[i] + yCoords[i == sides - 1 ? 0 : i + 1]) / 2.0; 
			}
			
			int[] tmpX = new int[sides];
			int[] tmpY = new int[sides];

			tmpX[0] = xCoords[0];
			tmpX[1] = (int) xm[0];
			tmpX[2] = (int) xm[2];
			tmpY[0] = yCoords[0];
			tmpY[1] = (int) ym[0];
			tmpY[2] = (int) ym[2];
			ret.add(new Node(tmpX, tmpY));

			tmpX[0] = xCoords[1];
			tmpX[1] = (int) xm[1];
			tmpX[2] = (int) xm[0];
			tmpY[0] = yCoords[1];
			tmpY[1] = (int) ym[1];
			tmpY[2] = (int) ym[0];
			ret.add(new Node(tmpX, tmpY));

			tmpX[0] = xCoords[2];
			tmpX[1] = (int) xm[2];
			tmpX[2] = (int) xm[1];
			tmpY[0] = yCoords[2];
			tmpY[1] = (int) ym[2];
			tmpY[2] = (int) ym[1];
			ret.add(new Node(tmpX, tmpY));

			return ret;
		}
	}
}
