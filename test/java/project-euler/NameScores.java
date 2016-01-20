import java.io.IOException;
import java.util.Arrays;

public class NameScores {
    public static void main(String[] args) throws IOException {
        byte[] bytes = new byte[System.in.available()];
        System.in.read(bytes);
        String str = new String(bytes);

        String[] strs = str.split(",");
        for (int i = 0; i < strs.length; i++)
            strs[i] = strs[i].substring(1, strs[i].length() - 1);

        Arrays.sort(strs);
        int[] scores = new int[strs.length];
        long total = 0;
        for (int i = 0; i < strs.length; i++) {
            long curr = 0;
            for (int j = 0; j < strs[i].length(); j++)
                curr += strs[i].charAt(j) - 'A' + 1;

            curr *= i + 1;
            total += curr;
        }

        System.out.println("Total of name scores = " + total);
    }
}
