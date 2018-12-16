import java.util.*;
import java.lang.*;
import java.io.*;

public class Main {
    public void solve(PrintWriter out) {
        // your code goes here
        int x = in.nextInt();
        out.println(x);
    }

	public static void main (String[] args) throws java.lang.Exception {
        PrintWriter out = new PrintWriter(System.out);
        solve(out);
        out.close();
	}

    // Fast IO
    static class in {
        static BufferedReader buff = new BufferedReader(new InputStream(System.in));
        static StringTokenizer tokenizer = new StringTokenizer("");
		
        static String next() throws IOException {
            while (!tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(buff.readLine());
            }
            return tokenizer.nextToken();
        }
        static int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
        static long nextLong() throws IOException {
            return Long.parseLong(next());
        }
        static double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }
    }
}
