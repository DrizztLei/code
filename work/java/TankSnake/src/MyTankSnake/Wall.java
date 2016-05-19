package MyTankSnake;

public class Wall {

	private int x;
	private int y;
	private boolean isLive = true;
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
	public boolean isLive() {
		return isLive;
	}
	public void setLive(boolean isLive) {
		this.isLive = isLive;
	}
	public Wall(int x,int y){
		this.x = x;
		this.y = y;
	}
	
}
