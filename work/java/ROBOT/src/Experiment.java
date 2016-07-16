
public class Experiment {
	public static void main(String[] args){
		//String str1 = "123";
		String str1 = "123";
		//String str2 =  "123";
		String str2 =  new String("123");		
		String str3 = str2.substring(1);
		System.out.println(str3);
		System.out.println(str1.hashCode() == str2.hashCode());
		System.out.println(str3 == str2);
		//System.out.println(x);
	}
}
