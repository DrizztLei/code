package MyTankSnake;

import javax.swing.*;

public class SnakeMain extends JFrame {

	public SnakeMain() {
		SnakeWin win = new SnakeWin();
		add(win);
		setTitle("贪吃蛇");
		setSize(435, 390);
		setLocation(200, 200);
		setVisible(true);

	}

	public static void main(String[] args) {

		new SnakeMain();

	}

}
