public class Smali {
    public static String check(String in){
        int k1 = 5; //寄存器v0;
        int k2 = 9;  //寄存器v1;
        int len = in.length(); //寄存器v2的值为方法返回值;
        String out = ""; //寄存器v3的值为"";

        char []b = new char[]{'a','A'};//char数组v4，array_0的内容由后面得到

        try{
            int d = 1/(len-9);  //v5 = v6/v5 = 1/(v2-9) = 1/(len-9)
            for(int i = 0;i<len;i++){
                int enc = in.toLowerCase().toCharArray()[i] - b[0];
                out = new StringBuilder().append(out).append(String.valueOf((char)((k1*enc+k2)%26+b[1]))).toString();
            }
        }catch (Exception e){
            char[]c = new char[]{'e','r','r'};
            return String.valueOf(c);
        }
        return out;
    }


    public static void main(String[]args){
        System.out.println(check("asdfghjk"));
    }
}
