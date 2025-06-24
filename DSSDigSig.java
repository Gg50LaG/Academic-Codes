import java.util.Scanner;
public class SimpleDSS {
public static int modExp(int base, int exp, int mod) {
int result = 1;
base = base % mod;
while (exp > 0) {
if (exp % 2 == 1)
result = (result * base) % mod;
base = (base * base) % mod;
exp /= 2;
}
return result;
}
public static int modInverse(int a, int m) {
for (int i = 1; i < m; i++) {
if ((a * i) % m == 1)
return i;
}
return -1;
}
public static int gcd(int a, int b) {
if (b == 0) return a;
return gcd(b, a % b);
}
public static void main(String[] args) {
Scanner sc = new Scanner(System.in);
System.out.print("Enter prime p: ");
int p = sc.nextInt();
System.out.print("Enter prime q (divides p-1): ");
int q = sc.nextInt();
System.out.print("Enter prime h: ");
int h = sc.nextInt();
int g = modExp(h, (p - 1) / q, p);
System.out.println("Calculated generator g: " + g);
System.out.print("Enter private key x: ");
int x = sc.nextInt();
int y = modExp(g, x, p);
System.out.println("Public key y = " + y);
System.out.print("Enter message hash H: ");
int H = sc.nextInt();
System.out.print("Enter random k: ");
int k = sc.nextInt();
if (gcd(k, q) != 1) {
System.out.println("Invalid k. GCD(k,q) must be 1.");
return;
}
System.out.println("Public key y = " + y);
int r = modExp(g, k, p) % q;
int kInv = modInverse(k, q);
int s = (kInv * (H + x * r)) % q;
System.out.println("Signature: r = " + r + ", s = " + s);
int w = modInverse(s, q);
int u1 = (H * w) % q;
int u2 = (r * w) % q;
int v = ((modExp(g, u1, p) * modExp(y, u2, p)) % p) % q;
System.out.println("Verification v = " + v);
System.out.println(v == r ? "Signature is VALID" : "Signature is INVALID");
sc.close();
}
}
