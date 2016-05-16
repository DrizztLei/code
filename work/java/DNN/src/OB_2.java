
public class OB_2 {

	public static void swap(OB ob1 , OB ob2){
		OB temp = new OB();
		temp = ob1;
		ob1 = ob2;
		ob2 = temp;
	}
	
public static void main(String[] argv){
		OB ob_1 = new OB(1);
		OB ob_2 = new OB(2);
		swap(ob_1, ob_2);
		System.out.println(ob_1.x);
	}
}
