package MyTankSnake;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

class Shot implements Runnable, KeyListener {
	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public int getDirect() {
		return direct;
	}

	public void setDirect(int direct) {
		this.direct = direct;
	}

	private int x;
	private int y;
	private int direct;
	int speed = 5;
	// 是否还活着
	private boolean isLive = true;

	public boolean isLive() {
		return isLive;
	}

	public void setLive(boolean isLive) {
		this.isLive = isLive;
	}

	public Shot(int x, int y, int direct) {
		this.x = x;
		this.y = y;
		this.direct = direct;
	}

	@Override
	public void run() {
		while (true) {

			if (start == 0) {
				continue;
			} else {
				try {
					Thread.sleep(100);
				} catch (Exception e) {

				}

				switch (direct) {
				case 1:
					y -= speed;
					break;
				case 2:
					x -= speed;
					break;
				case 3:
					y += speed;
					break;
				case 4:
					x += speed;
					break;
				}
				// System.out.println("子弹坐标"+x+y);
				// 子弹何时死亡?

				// 判断该子弹是否碰到边缘
				if (x > 410 || x < 10 || y > 340 || y < 40) {
					this.isLive = false;
					break;
				}
			}
		}

	}

	int start = 1;

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		if (e.getKeyCode() == KeyEvent.VK_Z) {
			start = 0;
		}
		if (e.getKeyCode() == KeyEvent.VK_X) {
			start = 1;
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub

	}

}
