package MyTankSnake;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.ImageObserver;
import java.util.*;

public class SnakeWin extends JPanel implements ActionListener, KeyListener,
		Runnable {

	JButton newGame, stopGame;
	int score, speed = 1;
	boolean isStarted = false;

	int rx = 0, ry = 0;
	Random r = new Random();
	Random r1 = new Random();
	Random r2 = new Random();
	int wx, wy;
	ArrayList<SnakeAct> list = new ArrayList<SnakeAct>();
	Thread nThread = new Thread(this);
	int direct = 1, tempeat = 0, tempeat2 = 0;
	JDialog dialog = new JDialog();
	JLabel label = new JLabel("GOOD GAME,YOUR SCORE IS" + score);
	JButton ok = new JButton("再来一局");
	Vector<Shot> ss = new Vector<Shot>();
	Vector<Wall> w = new Vector<Wall>();
	Shot s = null;
	Wall ww = null;
	Graphics g1;
	double coldTime = 0;
	int[][] hasWall = new int[40][30];
	private static Toolkit tk = Toolkit.getDefaultToolkit();
	ImageObserver o;
	int rLife = 10;
	private static Image[] images = null;
	static {
		images = new Image[] {
				tk.getImage(SnakeWin.class.getResource("image/pink1.png")),
				tk.getImage(SnakeWin.class.getResource("image/pink2.png")),
				tk.getImage(SnakeWin.class.getResource("image/pink3.png")),
				tk.getImage(SnakeWin.class.getResource("image/pink4.png")),
				tk.getImage(SnakeWin.class.getResource("image/q.png")),
				tk.getImage(SnakeWin.class.getResource("image/q2.png")),
				tk.getImage(SnakeWin.class.getResource("image/q3.png")) };
		// tk.getImage(Image.class.getResource("images/AMtank/LD.gif")),
		// tk.getImage(Image.class.getResource("images/AMtank/RU.gif")),
		// tk.getImage(Image.class.getResource("images/AMtank/RD.gif")),
		// tk.getImage(Image.class.getResource("images/AMtank/initam.gif"))
	};

	public void shotEnemy() {
		switch (this.direct) {
		case 1:
			// 创建一颗子弹
			s = new Shot(list.get(0).getX() * 10 + 10,
					list.get(0).getY() * 10 + 10, 1);
			// 把子弹加入向量
			ss.add(s);
			break;
		case 2:
			s = new Shot(list.get(0).getX() * 10 + 10,
					list.get(0).getY() * 10 + 10, 2);
			ss.add(s);
			break;
		case 3:
			s = new Shot(list.get(0).getX() * 10 + 10,
					list.get(0).getY() * 10 + 10, 3);
			ss.add(s);
			break;
		case 4:
			s = new Shot(list.get(0).getX() * 10 + 10,
					list.get(0).getY() * 10 + 10, 4);
			ss.add(s);
			break;
		}

		// 启动子弹线程
		Thread t = new Thread(s);
		t.start();
	}

	public SnakeWin() {
		newGame = new JButton("开始");
		stopGame = new JButton("退出");
		this.setLayout(new FlowLayout(FlowLayout.LEFT));
		newGame.addActionListener(this);
		stopGame.addActionListener(this);
		this.addKeyListener(this);
		this.add(newGame);
		this.add(stopGame);
		ok.addActionListener(this);
		dialog.setLayout(new GridLayout(2, 1));
		dialog.add(label);
		dialog.add(ok);
		dialog.setSize(200, 200);
		dialog.setLocation(100, 100);
		dialog.setVisible(false);
	}

	public void paintComponent(Graphics g) {

		super.paintComponent(g);

		g.drawRect(10, 40, 400, 300);
		g.drawString("分数" + score, 150, 20);
		g.drawString("速度" + speed, 150, 35);
		g.drawString("子弹冷却时间", 190, 25);

		g.drawRect(265, 20, 20, 5);
		g.fillRect(265, 20, (int) (4 * coldTime), 5);
		g.setColor(new Color(0, 255, 0));

		if (isStarted) {

			if (rLife > 8 && rLife <= 10) {
				g.drawImage(images[1], 10 + rx * 10, 40 + ry * 10, o);
			} else if (rLife > 6 && rLife <= 8) {
				g.drawImage(images[0], 10 + rx * 10, 40 + ry * 10, o);
			} else if (rLife > 4 && rLife <= 6) {
				g.drawImage(images[1], 10 + rx * 10, 40 + ry * 10, o);
			} else if (rLife > 2 && rLife <= 4) {
				g.drawImage(images[2], 10 + rx * 10, 40 + ry * 10, o);
			} else if (rLife > 0 && rLife <= 2) {
				g.drawImage(images[3], 10 + rx * 10, 30 + ry * 10, o);
			}
			rLife--;
			if (rLife == 0) {
				rLife = 10;
			}

			// g.fillRect(10 + rx * 10, 40 + ry * 10, 10, 10);
			g.setColor(Color.RED);
			for (int i = 0; i < list.size(); i++) {
				g.fillRect(10 + list.get(i).getX() * 10, 10 + list.get(i)
						.getY() * 10, 10, 10);

			}
			for (int i = 0; i < this.ss.size(); i++) {

				Shot myShot = ss.get(i);
				// 画子弹，画出一颗子弹
				if (myShot != null && myShot.isLive() == true) {

					g.fill3DRect(myShot.getX(), myShot.getY(), 10, 10, false);

				}

				if (myShot.isLive() == false) {
					// 从ss中删除该子弹
					ss.remove(myShot);
				}
			}

			for (int i = 0; i < 30; i++) {
				if (w.get(i).isLive())
					g.drawImage(images[5], 10 + w.get(i).getX() * 10, 40 + w
							.get(i).getY() * 10, o);
				// g.fill3DRect(10 + w.get(i).getX() * 10, 40 + w.get(i)
				// .getY() * 10, 10, 10, false);
			}
		}

	}

	// 吃食物
	public void eat() {

		if (rx == list.get(0).getX() && ry == list.get(0).getY() - 3) {

			rx = r.nextInt(40);
			ry = r.nextInt(30);
			isOverlapped(rx, ry);

			SnakeAct tempAct = new SnakeAct();
			tempAct.setX(list.get(list.size() - 1).getX());
			tempAct.setY(list.get(list.size() - 1).getY());

			list.add(tempAct);
			score += speed;
			tempeat++;
			if (tempeat - tempeat2 >= 10) {
				tempeat2 = tempeat;
				if (speed <= 5) {
					speed++;
				}
			}
		}
	}

	public void otherMove() {

		SnakeAct tempAct = new SnakeAct();
		for (int i = 0; i < list.size(); i++) {
			if (i == 1) {
				list.get(i).setX(list.get(0).getX());
				list.get(i).setY(list.get(0).getY());
			} else if (i > 1) {
				tempAct = list.get(i - 1);
				list.set(i - 1, list.get(i));
				list.set(i, tempAct);

			}
		}
	}

	public void move(int x, int y) {
		if (minYes(x, y)) {
			otherMove();
			list.get(0).setX(list.get(0).getX() + x);
			list.get(0).setY(list.get(0).getY() + y);
			eat();

			repaint();
		} else {
			isStarted = false;
			nThread = null;
			label.setText("GOOD GAME,YOUR SCORE IS" + score);
			dialog.setVisible(true);
		}
	}

	public boolean minYes(int x, int y) {
		if (!maxYes(list.get(0).getX() + x, list.get(0).getY() + y)) {
			return false;
		}

		return true;
	}

	public boolean maxYes(int x, int y) {
		if (x < 0 || x >= 40 || y < 3 || y >= 33) {
			return false;
		}
		for (int i = 3; i < list.size(); i++) {
			if (i > 0 && list.get(0).getX() == list.get(i).getX()
					&& list.get(i).getY() == list.get(0).getY()) {
				return false;
			}
		}
		for (int i = 0; i < 30; i++) {
			if (list.get(0).getX() == w.get(i).getX()
					&& list.get(0).getY() == (w.get(i).getY() + 3)
					&& w.get(i).isLive()) {
				return false;
			}
		}
		return true;
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		if (isStarted) {
			switch (e.getKeyCode()) {
			case KeyEvent.VK_UP:
				if (direct != 3) {
					move(0, -1);
					direct = 1;
				}
				break;
			case KeyEvent.VK_LEFT:
				if (direct != 4) {
					move(-1, 0);
					direct = 2;
				}
				break;
			case KeyEvent.VK_DOWN:
				if (direct != 1) {
					move(0, 1);
					direct = 3;
				}
				break;
			case KeyEvent.VK_RIGHT:
				if (direct != 2) {
					move(1, 0);
					direct = 4;
				}
				break;
			case KeyEvent.VK_SPACE:
				if (coldTime == 0) {
					shotEnemy();
					coldTime = 5;
				}
				break;
			}
		}

	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if (e.getSource() == newGame) {
			newGame.setEnabled(false);
			isStarted = true;

			SnakeAct tempAct = new SnakeAct();
			tempAct.setX(20);
			tempAct.setY(20);
			list.add(tempAct);
			requestFocus(true);

			
			for (int i = 0; i < 10; i++) {
				wx = r1.nextInt(34);
				wy = r2.nextInt(24);
				int temp = r.nextInt(2);
				while (hasWallOrNot(wx, wy, temp)) {
					wx = r1.nextInt(34);
					wy = r2.nextInt(24);
				}
				if (temp == 0) {
					for (int j = 0; j < 3; j++) {
						ww = new Wall(wx + j, wy);
						w.add(ww);
						hasWall[wx + j][wy] = 1;
					}
				} else if (temp == 1) {
					for (int j = 0; j < 3; j++) {
						ww = new Wall(wx, wy + j);
						w.add(ww);
						hasWall[wx][wy + j] = 1;
					}
				}
			}
			for(int i = 0 ;i<30;i++){
				w.get(i).setLive(true);
			}
			rx = r.nextInt(40);
			ry = r.nextInt(30);
			isOverlapped(rx, ry);
			score = 0;
			speed = 1;
			nThread = new Thread(this);
			nThread.start();
			repaint();

		}
		if (e.getSource() == stopGame) {
			System.exit(0);
		}
		if (e.getSource() == ok) {
			list.clear();

			isStarted = false;
			newGame.setEnabled(true);
			dialog.setVisible(false);

			repaint();
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		while (isStarted) {
			switch (direct) {
			case 1:
				move(0, -1);
				break;
			case 2:
				move(-1, 0);
				break;
			case 3:
				move(0, 1);
				break;
			case 4:
				move(1, 0);
				break;
			}
			if (ss.size() != 0) {
				for (int i = 0; i < ss.size(); i++) {
					for (int j = 0; j < w.size(); j++) {
						if (hitTank(ss.get(i), w.get(j))) {
							break;
						}
					}
				}
			}
			repaint();
			if (coldTime > 0) {
				coldTime -= 0.5;
			}
			try {
				Thread.sleep(500 - speed * 50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}
	}

	public void isOverlapped(int x, int y) {
		for (int i = 0; i < 30; i++) {
			if (x == w.get(i).getX() && y == w.get(i).getY()) {
				x = r.nextInt(40);
				y = r.nextInt(30);
				isOverlapped(x, y);
			}
		}
	}

	public boolean hasWallOrNot(int x, int y, int temp) {

		if (temp == 0) {
			for (int i = 0; i < 3; i++) {
				if (hasWall[wx + i][wy] == 0) {
					continue;
				} else {
					return true;
				}
			}
		} else if (temp == 1) {
			for (int i = 0; i < 3; i++) {
				if (hasWall[wx][wy + i] == 0) {
					continue;
				} else {
					return true;
				}
			}
		}
		return false;
	}

	public boolean hitTank(Shot s, Wall ww) {

		boolean b = false;
		// 击中
		switch (s.getDirect()) {
		case 1:
			if ((s.getX() == ww.getX() * 10 + 10 && s.getY() == ww.getY() * 10 + 40)
					|| (s.getX() == ww.getX() * 10 + 10 && s.getY() - 5 == ww
							.getY() * 10 + 40)) {
				// 子弹死亡
				ww.setLive(false);
				s.setLive(false);
				b = true;
			}
			break;
		case 2:
			if ((s.getX() == ww.getX() * 10 + 10 && s.getY() == ww.getY() * 10 + 40)
					|| (s.getX() - 5 == ww.getX() * 10 + 10 && s.getY() == ww
							.getY() * 10 + 40)) {
				// 子弹死亡
				ww.setLive(false);
				s.setLive(false);
				b = true;
			}
			break;
		case 3:
			if ((s.getX() == ww.getX() * 10 + 10 && s.getY() == ww.getY() * 10 + 40)
					|| (s.getX() == ww.getX() * 10 + 10 && s.getY() + 5 == ww
					.getY() * 10 + 40)) {
				// 子弹死亡
				ww.setLive(false);
				s.setLive(false);
				b = true;
			}
			break;
		case 4:
			if ((s.getX() == ww.getX() * 10 + 10 && s.getY() == ww.getY() * 10 + 40)
					|| (s.getX() + 5 == ww.getX() * 10 + 10 && s.getY() == ww
							.getY() * 10 + 40)) {
				// 子弹死亡
				ww.setLive(false);
				s.setLive(false);
				b = true;
			}
			break;
		}
		return b;
	}
}
